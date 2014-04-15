#include<QDebug>

#include "bearcat.h"


Bearcat::Bearcat(std::string portName)
{
    serial.setPortName("COM4");
}

Bearcat::~Bearcat()
{

}

void Bearcat::open()
{
    serial.open(QIODevice::ReadWrite);

    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setFlowControl(QSerialPort::NoFlowControl);
}


void Bearcat::close()
{
    serial.close();
}

bool Bearcat::isOpen()
{
    return serial.isOpen();
}


void Bearcat::press_key()
{
}

void Bearcat::getVolume()
{
    serial.write("VOL\r");
    QByteArray buffer = serial.readLine();
    qDebug() << buffer;

//    return 0;

}
