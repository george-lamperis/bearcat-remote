#ifndef BEARCAT_H
#define BEARCAT_H

#include <iostream>

#include <QObject>
#include <QSerialPort>
#include <QTimer>

// TODO we need a way to sync settings with GUI
// some settings can be applied immediately:
//  - Squelch
//  - Volume
//
// Others are dependent on the mode of the scanner
//  - search/service/scan banks

// TODO signal/slot access levels


struct Status {
    bool hold;
    int signal;

    QString alpha;
    QString channel;
    QString frequency;
    QString modulation;

    QString direction;      // direction of tuner
    QString bank;
};

QDebug operator<<(QDebug dbg, const Status &status);


enum class Keys { _0 = '0', _1 = '1', _2 = '2', _3 = '3', _4 = '4', _5 = '5',
    _6 = '6', _7 = '7', _8 = '8', _9 = '9', DECIMAL = '.', HOLD = 'H',
    SCAN = 'S', SEARCH = 'R', LOCK = 'L', POWER = 'P', ENTER = 'E',
    FUNCTION = 'F', SCROLL_UP = '>', SCROLL_DOWN = '<', SCROLL_CLICK = '^'
};


class Bearcat : public QObject
{
    Q_OBJECT

public:
    // Scan, search, service

    static const char KEY_HOLD = 'H';
    static const char KEY_PRESS = 'P';

    Bearcat(std::string portName);
    virtual ~Bearcat();

    void open();
    bool isOpen();
    void close();

    void getVolume();
    void setVolume();
    void getSquelch();
    void setSquelch();

    void setBacklight();

    void pressKey(Keys key);

    void Bearcat::timerEvent ( QTimerEvent * event );

signals:
    void statusChanged();

private slots:
    void updateStatus();

private:
    static const int REFRESH_RATE = 500;    // milliseconds

    QTimer *timer;

    QSerialPort serial;
    Status status;      // status consists of info on scanner screen
    int volume;
    int squelch;

    QString getResponse(QString cmd);
};

#endif // BEARCAT_H
