#include<QDebug>

#include "bearcat.h"


Bearcat::Bearcat(std::string portName)
{
    serial.setPortName("COM4");

    timer = new QTimer(this);
    timer->setInterval(REFRESH_RATE);
    timer->setSingleShot(false);

    //    connect(timer, &QTimer::timeout, this, &MainWindow::poll_device);
}

Bearcat::~Bearcat()
{
    close();
}

void Bearcat::open()
{
    if (! serial.isOpen())
    {
        qDebug() << "opening connection";
        serial.open(QIODevice::ReadWrite);

        serial.setBaudRate(QSerialPort::Baud9600);
        serial.setStopBits(QSerialPort::OneStop);
        serial.setDataBits(QSerialPort::Data8);
        serial.setParity(QSerialPort::NoParity);
        serial.setFlowControl(QSerialPort::NoFlowControl);


        timer->start();
    }
}


bool Bearcat::isOpen()
{
    return serial.isOpen();
}


void Bearcat::close()
{
    if (serial.isOpen()) {
        qDebug() << "closing connection";
        serial.close();
    }
}


void Bearcat::updateStatus()
{
    Status status;

    serial.write("STS\r");
    QByteArray buf = serial.readLine();
    QList<QByteArray> tokens = buf.split(',');

    // on first run, we get an empty string
    if (tokens.size() < 2)
        return;

    // Hold?
    if (tokens.at(2).contains("\x8d\x8e\x8f\x90") ) {
        status.hold = true;
    } else {
        status.hold = false;
    }

    // Alpha Tag
    status.alpha = tokens.at(4).trimmed();

    // Channel
    status.channel = tokens.at(6).mid(2, 3);

    // frequency
    status.frequency = tokens.at(6).mid(7, 8);


    qDebug() << status;
    qDebug() << tokens;
}


void Bearcat::pressKey()
{
}


void Bearcat::getVolume()
{
    serial.write("VOL\r");
    QByteArray buffer = serial.readLine();
    qDebug() << buffer;

//    return 0;

}

QDebug operator<<(QDebug dbg, const Status &status)
{
    dbg.nospace();

    dbg << "hold: " << status.hold << "\n";
    dbg << "signal: " << status.signal << "\n";
    dbg << "alpha: " << status.alpha << "\n";
    dbg << "channel: " << status.channel << "\n";
    dbg << "frequency: " << status.frequency << "\n";
    dbg << "modulation" << status.modulation << "\n";
    dbg << "bank" << status.bank;

    return dbg;
}
