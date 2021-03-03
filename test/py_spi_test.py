import spidev
import time

def main():

    spi = spidev.SpiDev()

    spi.open(0, 1)

    spi.cshigh = True
    spi.bits_per_word = 8
    spi.max_speed_hz = 50000
    spi.mode = 0b00             # try 01
    #spi.no_cs = True    

    count = 0
    while(True):
        data = spi.readbytes(2500)
        print(data)
	print("--------------------- " + str(count))
        count += 1
        time.sleep(0.100)

if __name__ == "__main__":
    main()