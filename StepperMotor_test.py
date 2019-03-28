import RPi.GPIO as GPIO
from time import sleep
pul=21
dir=20
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(pul,GPIO.OUT)
GPIO.setup(dir,GPIO.OUT)


GPIO.output(dir,1)

for i in range(828):
    GPIO.output(pul,GPIO.HIGH)
    sleep(0.0005)
    GPIO.output(pul,GPIO.LOW)
    sleep(0.0005)