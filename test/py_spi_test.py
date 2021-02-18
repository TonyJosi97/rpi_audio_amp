import spidev

def main():

    spi = spidev.SpiDev()
    spi.open(0, 0)

    spi.max_speed_hz = 5000
    spi.mode = 0b00             # try 01
    spi.no_cs = True

    while(True):
        data = spi.readbytes(1000)
        print(data)

if __name__ == "__main__":
    main()