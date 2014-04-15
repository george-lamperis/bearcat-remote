#include <iostream>

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scanner = new Bearcat("COM4");
    scanner->open();

    timer = new QTimer(this);
    timer->setInterval(500);
    timer->setSingleShot(false);

    connect(timer, &QTimer::timeout, this, &MainWindow::poll_device);
    timer->start();
}


MainWindow::~MainWindow()
{
    delete scanner;
    delete ui;
}


void MainWindow::poll_device()
{
    qDebug() << "timeout";
    qDebug() << ui->slider_volume->value();
    ui->slider_volume->setValue(0);
//    bearcat->getVolume();
}
