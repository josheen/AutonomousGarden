import numpy
import matplotlib.pyplot as plt 
from drawnow import * 
import serial

lightValue = []
arduinoAnalog = serial.Serial('/dev/cu.usbmodem143201 (Arduino/Genuino Mega or Mega3560)',9600)
plt.ion()

def makeFigure():
    plt.plot(lightValue, 'ro-')


while True:
    while(arduinoAnalog.inWaiting()==0):
        pass
    arduinoString = arduinoData.readline()
    try:
        conversion = float(arduinoString)
    except:
        pass 
    lightValue.append(conversion)
    plt.pause(0.00001)