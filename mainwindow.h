#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include "bearcat.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onButtonClicked(QAbstractButton *button);

private:
    Ui::MainWindow *ui;
    Bearcat *scanner;

};

#endif // MAINWINDOW_H
