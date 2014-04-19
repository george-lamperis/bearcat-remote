#include <iostream>

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QPushButton>
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


    // TODO move timer
    timer = new QTimer(this);
    timer->setInterval(500);
    timer->setSingleShot(false);

//    connect(timer, &QTimer::timeout, this, &MainWindow::poll_device);
//    timer->start();

    connect(ui->buttonGroup, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(onButtonClicked(QAbstractButton*)) );
}


MainWindow::~MainWindow()
{
    delete scanner;
    delete ui;
}



void MainWindow::onButtonClicked(QAbstractButton *button)
{
    qDebug() << button->objectName();
}
