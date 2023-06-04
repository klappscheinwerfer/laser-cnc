#include <AccelStepper.h>

#define motorInterfaceType 1

// X axis
const int xDirPin = 8;
const int xStepPin = 9;
AccelStepper xStepper(motorInterfaceType, xStepPin, xDirPin);
const float xMultiplier = 0.25;

// Y axis
const int yDirPin = 2;
const int yStepPin = 3;
AccelStepper yStepper(motorInterfaceType, yStepPin, yDirPin);
const float yMultiplier = 0.25;

// Laser
const int laserPin = 0;

void setup() {
	// Set speed
	xStepper.setAcceleration(200 * 100);
	yStepper.setAcceleration(200 * 100);

	xStepper.moveTo(200 * xMultiplier);
	yStepper.moveTo(200 * yMultiplier);
}

void loop() {

	// Move the motors one step
	xStepper.runSpeedToPosition();
	yStepper.runSpeedToPosition();
}