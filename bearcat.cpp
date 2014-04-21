#include <assert.h>

#include<QDebug>

#include "bearcat.h"


Bearcat::Bearcat(std::string portName)
{
    serial.setPortName("COM4");

//    timer = new QTimer(this);
//    timer->setInterval(REFRESH_RATE);
//    timer->setSingleShot(false);

//    connect(timer, &QTimer::timeout, this, &Bearcat::updateStatus);
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
//        serial.setFlowControl(QSerialPort::NoFlowControl);

        serial.setTextModeEnabled(false);   // to interpret \r
//        timer->start();
        startTimer(REFRESH_RATE);
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


void Bearcat::timerEvent ( QTimerEvent * event )
{
    qDebug() << "timerEvent()";
    updateStatus();
}


QString Bearcat::getResponse(QString cmd)
{
    assert( cmd.endsWith("\r") );

    serial.write(cmd.toStdString().c_str());
    QString response;
    char c = 0;

    while(c != '\r') {

        serial.waitForReadyRead(1);

        if (serial.bytesAvailable() > 0) {
            serial.getChar(&c);
            response.append(c);
        } else {
            continue;
        }
    }

    return response;
}


void Bearcat::updateStatus()
{
//    Status status;

    // The problem is that readLine() returns before the entire
    // response has been written.
    QString response = getResponse("STS\r");
    qDebug() << "updateStatus() " << response;

    qDebug() << "updateStatus() " << QString().setNum(response[0].toLatin1(), 16);
    qDebug() << "updateStatus() " << QString().setNum(response[1].toLatin1(), 16);

//    qDebug() << serial.readLine();
//    QList<QByteArray> tokens = response.split(',');

//    // on first run, we get an empty string
//    if (tokens.size() < 2)
//        return;

//    // Hold?
//    if (tokens.at(2).contains("\x8d\x8e\x8f\x90") ) {
//        status.hold = true;
//    } else {
//        status.hold = false;
//    }

//    // Alpha Tag
//    status.alpha = tokens.at(4).trimmed();

//    // Channel
//    status.channel = tokens.at(6).mid(2, 3);

//    // frequency
//    status.frequency = tokens.at(6).mid(7, 8);


//    qDebug() << status;
//    qDebug() << "updateStatus() " << tokens;
}


void Bearcat::pressKey(Keys key)
{
    // TODO
    // make sure there is nothing left to read before writing
    // make sure theres nothing left after reading response


    QByteArray cmd = "KEY,,P\r";
    cmd.insert(4, (char) key);
    QString response = getResponse(cmd);

    qDebug() << "pressKey(): " << response;
//    qDebug() << response.endsWith("\r");
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
