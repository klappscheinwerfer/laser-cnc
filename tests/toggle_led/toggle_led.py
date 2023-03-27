# This program sends 0 or 1 to the serial port
# Requirements: pyserial

import serial

arduino = serial.Serial(port="/dev/ttyACM0", baudrate=9600, timeout=.1)

while True:
	input("Press ENTER to switch the LED on")
	arduino.write("\x01".encode())
	input("Press ENTER to switch the LED off")
	arduino.write("\x00".encode())