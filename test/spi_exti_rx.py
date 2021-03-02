import RPi.GPIO as GPIO
import time
import spidev

GPIO_EXTI = 11


def setup():

    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(GPIO_EXTI, GPIO.OUT)

def run():



    while True:




if __name__ == "__main__":

    setup()
    run()
