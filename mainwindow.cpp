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
    // TODO scroll buttons

    qDebug() << button->objectName();

    if (button == ui->buttonScrollNext) {
        scanner->pressKey(Keys::SCROLL_UP);
    } else if (button == ui->buttonScrollPrev) {
        scanner->pressKey(Keys::SCROLL_DOWN);
    } else if (button == ui->buttonScrollClick) {
        scanner->pressKey(Keys::SCROLL_CLICK);
    } else if (button == ui->buttonHold) {
        scanner->pressKey(Keys::HOLD);
    } else if (button == ui->buttonScan) {
        scanner->pressKey(Keys::SCAN);
    } else if (button == ui->buttonSearch) {
        scanner->pressKey(Keys::SEARCH);
    } else if (button == ui->buttonLock) {
        scanner->pressKey(Keys::LOCK);
    } else if (button == ui->buttonPower) {
        scanner->pressKey(Keys::POWER);
    } else if (button == ui->buttonEnter) {
        scanner->pressKey(Keys::ENTER);
    } else if (button == ui->buttonFunc) {
        scanner->pressKey(Keys::FUNCTION);
    } else if (button == ui->buttonDecimal) {
        scanner->pressKey(Keys::DECIMAL);
    } else if (button == ui->button0) {
        scanner->pressKey(Keys::_0);
    } else if (button == ui->button1) {
        scanner->pressKey(Keys::_1);
    } else if (button == ui->button2) {
        scanner->pressKey(Keys::_2);
    } else if (button == ui->button3) {
        scanner->pressKey(Keys::_3);
    } else if (button == ui->button4) {
        scanner->pressKey(Keys::_4);
    } else if (button == ui->button5) {
        scanner->pressKey(Keys::_5);
    } else if (button == ui->button6) {
        scanner->pressKey(Keys::_6);
    } else if (button == ui->button7) {
        scanner->pressKey(Keys::_7);
    } else if (button == ui->button8) {
        scanner->pressKey(Keys::_8);
    } else if (button == ui->button9) {
        scanner->pressKey(Keys::_9);
    }
}
