import cv2
import picamera
import picamera.array
import time
from time import sleep
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
pul=21
dir=20
TRIGGER = 23
ECHO = 24
GPIO.setup(pul,GPIO.OUT)
GPIO.setup(dir,GPIO.OUT)
GPIO.setup(TRIGGER, GPIO.OUT)
GPIO.setup(ECHO, GPIO.IN)


def distance1():
    GPIO.output(TRIGGER, True)
    time.sleep(0.00001)
    GPIO.output(TRIGGER, False)
    StartTime = time.time()
    StopTime = time.time()
    try:
        while GPIO.input(ECHO) == 0:
            StartTime = time.time()
        except:
        StartTime = 0
    try:
        while GPIO.input(ECHO) == 1:
            StopTime = time.time()
    except:
        StopTime = 0
    try:
        start = StartTime
        stop = StopTime
    except:
        start = 0
        stop = 0
    TimeElapsed = stop - start
    ##    print(TimeElapsed)
    distance = (TimeElapsed * 17150)
    distance = round(distance, 2)
    if distance >= 1
        print('distance in cm, %.2f' % (distance))
        GPIO.cleanup()


def clockwise(a):
    GPIO.output(dir,1)
    for i in range(a*138):
        GPIO.output(pul,GPIO.HIGH)
        sleep(0.0004)
        GPIO.output(pul,GPIO.LOW)
        sleep(0.0004)
def counter_cw(b):
    GPIO.output(dir,0)
    for i in range(b*138):
        GPIO.output(pul,GPIO.HIGH)
        sleep(0.0005)
        GPIO.output(pul,GPIO.LOW)
        sleep(0.0005)

l=[1,1]

face_cascade = cv2.CascadeClassifier('MY_haarcascade.xml')
with picamera.PiCamera() as camera:
    with picamera.array.PiRGBArray(camera) as stream:
        camera.resolution = (480, 240)
        while True:
            camera.capture(stream, 'bgr', use_video_port=True)
            img = stream.array
            img = cv2.flip(img, -1)
            faces = face_cascade.detectMultiScale(img, scaleFactor=1.1, minNeig)
            ##            start1 = time.time()
            for (x, y, w, h) in faces:
                cv2.rectangle(img, (x, y), (x + w, y + h), (255, 0, 0), 2)
                time.sleep(0.01)
                if x + w in range(0, 40):
                    l[-1] = 1
                if x + w in range(40, 80):
                    l[-1] = 2
                if x + w in range(80, 120):
                    l[-1] = 3
                if x + w in range(120, 160):
                    l[-1] = 4
                if x + w in range(160, 200):
                    l[-1] = 5
                if x + w in range(200, 240):
                    l[-1] = 6
                if x + w in range(240, 280):
                    l[-1] = 7
                if x + w in range(280, 320):
                    l[-1] = 8
                if x + w in range(320, 360):
                    l[-1] = 9
                if x + w in range(360, 400):
                    l[-1] = 10
                if x + w in range(400, 440):
                    l[-1] = 11
                if x + w in range(440, 480):
                    l[-1] = 12

                if l[-1] != l[-2] and l[-1] < l[-2]:
                    j = l[-2] - l[-1]
                    counter_cw(j)
                if l[-1] != l[-2] and l[-1] > l[-2]:
                    i = l[-1] - l[-2]
                    clockwise(i)

                distance1()
                l[-2] = l[-1]

            cv2.imshow('frame', img)
            if cv2.waitKey(1) & 0xFF == ord('q'):
                if l[-1] != 1:
                   counter_cw(l[-1] - 1)
            print('callibrating stepper to zero')
            break
            stream.seek(0)
            stream.truncate()

        cv2.destroyAllWindows()




