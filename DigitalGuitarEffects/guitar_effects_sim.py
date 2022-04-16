import math as m
import matplotlib.pyplot as plt
import numpy as np

samples = 1024
resolution = 1024
sineTab = []
processedSignalTab = []

def Sine():
    for i in range(0, samples, 1):
        sineTab.append((((m.sin(((2*m.pi) / samples) * i)) * resolution) / 2))    # negative range - +
        # sineTab.append((((1 + m.sin(((2*m.pi) / samples) * i))*1023.0) / 2))  # positive range _> 1 + ...


def equation(x):
    return  (1 + (x/abs(x)) * (1-m.exp((-1*pow(x,2))/abs(x)))) # positive range
    # return (x/abs(x)) * (1-m.exp((-1*pow(x,2))/abs(x)))   # negative range

def HardDistortion():
    # sineTab - works with negative range, returns positive
    for i in sineTab:
        # y = equation(i+1)
        # if i > 0:
        #     y = 1 - m.exp(-i)
        # else:
        #     y = -1 + m.exp(i)
        if i > 0:
            y = ((1+(1 - m.pow(2.71, -i))) * resolution) / 2
        else:
            y = ((1+(-1 + m.pow(2.71, i))) * resolution) / 2
        processedSignalTab.append(y)


    # sineTab - works with negative range, returns positive
def Overdrive():
    for i in sineTab:
        y = ((pow(i, 2)) / (resolution*0.25))
        if y > 823: y = 823
        processedSignalTab.append(y)

def Assymetrical():
    for i in sineTab:
        y = ((pow(i, 2)) / (resolution*0.25))
        processedSignalTab.append(y)


# sineTab - works with negative range, returns pos
def Distortion1():
    for i in sineTab:
        y = ((i/(1+abs(i)))*(resolution/2)) + 512
        processedSignalTab.append(y)

Sine()
plt.plot(sineTab)
plt.show()

# HardDistortion()
Overdrive()
# Assymetrical()
# Distortion1()
plt.plot(processedSignalTab)
plt.show()

