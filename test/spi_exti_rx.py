import RPi.GPIO as GPIO
import time
import spidev

GPIO_EXTI = 11
SPI_TX_SIZE = 2500


def setup():

    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(GPIO_EXTI, GPIO.OUT)


def run():

    spi = spidev.SpiDev()

    spi.open(0, 0)
    #spi.cshigh = True
    spi.bits_per_word = 4
    spi.max_speed_hz = 1000000
    #spi.mode = 0b00             # try 01
    #spi.no_cs = True    

    for _ in range(100):
        GPIO.output(GPIO_EXTI, GPIO.HIGH)
        data = spi.readbytes(SPI_TX_SIZE)
        print(data)
        time.sleep(0.1)
        GPIO.output(GPIO_EXTI, GPIO.LOW)
        time.sleep(0.005)


def clean_up():
    GPIO.cleanup()


if __name__ == "__main__":

    setup()
    run()
    clean_up()
