import serial
import time

# XBee setting
serdev = '/dev/ttyUSB0'
s = serial.Serial(serdev, 9600)

# send to remote
while 1:
    line = s.read(16)   #Read 16 char a time
    print(line)

s.close()