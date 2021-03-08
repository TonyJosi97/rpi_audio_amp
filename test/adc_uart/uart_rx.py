import serial
import sys
import datetime
import time

SERIAL_PORT = 'COM14'
BAUD_RATE = 921600
ENABLE_LOG = False


def _Log__(msg_type, msg):
    if(ENABLE_LOG):
        print(">>> {} {}: {}".format(datetime.datetime.now().strftime(
            '%Y-%m-%d %H:%M:%S.%f')[:-3], msg_type, msg))

class UART_RX_Base:

    def __init__(self):
        pass

    def connect(self):
        try:
            self.uart_txrx_obj = serial.Serial(
                SERIAL_PORT, BAUD_RATE, timeout=1)
        except Exception:
            _Log__("ERR", "Error connecting to device.")
            sys.exit()
        _Log__("INFO", "Connected to " + SERIAL_PORT + \
               " baud: " + str(BAUD_RATE))

    def get_Data(self):
        try:
            data = self.uart_txrx_obj.readline()
        except Exception as e:
            _Log__("ERR", str(e))
            return -1
        return data

    def read_Until(self, str_seq = '\n'):
        seq_len = len(str_seq)
        data_buffer = []
        seq_bytar_list = []
        for i in str_seq:
            seq_bytar_list.append(i.encode('ascii'))
        
        while True:
            try: 
                _byte = self.uart_txrx_obj.read(1)
            except Exception as e:
                _Log__("ERR", str(e))
                return -1
            data_buffer.append(_byte)

            if(len(data_buffer) > seq_len):
                if(seq_bytar_list == data_buffer[-seq_len:]):
                    break

        return data_buffer

    def convert_to_Uint16(self, data):
        uint16_arr = []
        i = 0
        print(b''.join((data[0 : 0 + 2])))
        while(i < (len(data) - 4)):
            byt_ar = b''.join((data[i : i + 2]))
            num = int.from_bytes(byt_ar, byteorder='little', signed=False)
            uint16_arr.append(num)
            i += 2
        return uint16_arr

    def convert_to_Uint8(self, data):
        uint8_arr = []
        i = 0
        while(i < (len(data) - 4)):
            uint8_arr.append(int.from_bytes(data[i], "big"))
            i += 2
        return uint8_arr


if __name__ == "__main__":
    uart_rx = UART_RX_Base()
    uart_rx.connect()

    pckt_cntr = 0
    prev_time = time.time()
    while(True):
        _data = uart_rx.read_Until('\n\r')
        uint16_arr = uart_rx.convert_to_Uint8(_data)
        # print(str(len(_data)) + " ID: " + str(pckt_cntr) + " TIME DIFF: " + str(time.time() - prev_time) + " VAL: " + str(uint16_arr[100]))
        print(', '.join(map(str, uint16_arr)), end='')
        print(',', end='')
        prev_time = time.time()
        pckt_cntr += 1
