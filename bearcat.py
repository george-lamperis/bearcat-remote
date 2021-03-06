import serial
import string

class Bearcat:
    """ This class communicates with a Uniden BC125AT scanner via serial port."""

    def __init__(self, port):
        self.ser = serial.Serial(port=port, baudrate=9600, timeout=2)

    def write(self, cmd):
        """ Sends a command to the device and returns a response. """
        cmdstr = bytes('{}\r'.format(cmd), 'utf-8')
        self.ser.write(cmdstr)

        return self.readline()

    def readline(self):
        """ Reads character by character until '\r' is recieved. """

        try:
            buf = ''
            while True:
                c = self.ser.read()

                if c == b'\r':
                    return buf
                if c == b'' and buf == '':
                    return ''
                else:
                    buf = buf + chr(ord(c))

        except serial.SerialTimeoutException:
            print('device timed out!')
            return ''
        except Exception as e:
            print('unexpected exception!')
            raise e

def trykeys(bearcat):
    excluded = list(string.digits)
    excluded += ['H', 'S', 'R',  'L',  'P',  'E',  'F', '.']

    for i in range(0x20, 0xE0):
        if chr(i) not in excluded:
            response =  bearcat.write('KEY,{},P'.format(chr(i)))
            if response != 'KEY,ERR':
                print(chr(i))
                print(response + '\n')

