import serial

class BearCat:
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
                    buf = buf + c.decode()
                    # print(binascii.hexlify(c))

        except serial.SerialTimeoutException:
            print('device timed out!')
            return ''
        except Exception as e:
            print('unexpected exception!')
            raise e

    def readbytes(self):
        """ Similar to above, but returns a bytestring instead. """
        pass

def probe(bearcat):
    """ probes the scanner for possible commands. """
    pass
