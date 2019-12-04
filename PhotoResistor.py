import numpy
import matplotlib.pyplot as plt 
from drawnow import * 
import serial
import time

lightValue = []
arduinoAnalog = serial.Serial('/dev/cu.usbmodem143201 (Arduino/Genuino Mega or Mega3560)',9600)
plt.ion()

def makeFigure():
    plt.ylim(50,850)
    plt.plot(lightValue, 'ro-')
    plt.title('Photoresistor Reading')
    plt.ylabel('lumens')
    plt.xlabel('time')


while True:
    while(arduinoAnalog.inWaiting()==0):
        pass
    arduinoAnalog.inputFlush()
    time.sleep(0.01) 
    arduinoString = arduinoData.readline()

    try:
        conversion = int(arduinoString.decode('utf-8')) #data is stored at unicode transformation format 
    except:
        pass 
    lightValue.append(conversion)
    plt.pause(0.00001)

