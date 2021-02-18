import spidev

def main():

    spi = spidev.SpiDev()

    spi.open(0, 0)

    #spi.cshigh = True
    spi.bits_per_word = 8
    spi.max_speed_hz = 1000000
    spi.mode = 0b00             # try 01
    spi.no_cs = True    

    count = 0
    while(True):
        data = spi.readbytes(4000)
        print(data)
	print("--------------------- " + str(count))
        count += 1

if __name__ == "__main__":
    main()