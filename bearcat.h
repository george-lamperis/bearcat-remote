#ifndef BEARCAT_H
#define BEARCAT_H

#include <QObject>
#include <QSerialPort>


// TODO we need a way to sync settings with GUI
// some settings can be applied immediately:
//  - Squelch
//  - Volume
//
// Others are dependent on the mode of the scanner
//  - search/service/scan banks

// TODO signal/slot access levels

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

    void getMode();
    void getStatus();
//    void setMode();

    void scan();
    void search();
    void service();
    void lockout();

    void setBacklight();


    void press_key();

private:
    enum class Keys { KEY_0 = '0', KEY_1 = '1', KEY_2 = '2', KEY_3 = '3',
        KEY_4 = '4', KEY_5 = '5', KEY_6 = '6', KEY_7 = '7', KEY_8 = '8',
        KEY_9 = '9', KEY_DECIMAL = '.', KEY_HOLD = 'H', KEY_SCAN = 'S',
        KEY_SEARCH = 'R', KEY_LOCK = 'L', KEY_POWER = 'P', KEY_FUNCTION = 'F'
    };

    enum class Action { HOLD = 'H', PRESS = 'P' };
    enum class Mode { SCAN, SEARCH, SERVICE, HOLD };

    QSerialPort serial; // TODO pointer instead?

};

#endif // BEARCAT_H