#include <Stepper.h>

const int stepsPerRevolution = 200;

// X axis
const int xDirPin = 8;
const int xStepPin = 9;
Stepper xStepper(stepsPerRevolution, xDirPin, xStepPin);

const float xMultiplier = 0.25;

// Y axis
const int yDirPin = 2;
const int yStepPin = 3;
Stepper yStepper(stepsPerRevolution, yDirPin, yStepPin);
const float yMultiplier = 0.25;

// Laser
const int laserPin = 5;

// Buffer
#define BUFFER_SIZE 64
char buffer[BUFFER_SIZE];
int bufferPos;

// Commands
int line;

float parseAttribute(char code, float def) {
	char *last = buffer;
	while ((long)last > 1 && (*last) && (long)last < (long)buffer + bufferPos) {
		if (*last == code) {
			return atof(last + 1);
		}
		last = strchr(last, ' ') + 1;
	}
	return def;
}

void processCommand() {
	// Debug: print received command
	// Serial.print("d:");
	// Serial.print(buffer);

	int recognized = 2;

	// Interpret G command
	int cmd = parseAttribute('G', -1);
	switch (cmd) {
		case 1:
			moveTo(parseAttribute('X', 0), parseAttribute('Y', 0));
			break;
		default:
			recognized--;
			break;
	}

	// Interpret M command
	cmd = parseAttribute('M', -1);
	switch(cmd) {
		case 2: // End of program
			line = 0;
			return;
		case 3: // Laser ON
			Serial.print("ON\n");
			digitalWrite(laserPin, HIGH);
			break;
		case 5: // Laser OFF
			Serial.print("OFF\n");
			digitalWrite(laserPin, LOW);
			break;
		default:
			recognized--;
			break;
	}

	// Check if command recognized
	if (!recognized) {
		Serial.print(F("e:cmd_not_recognized\n"));
	}
	
	Serial.print("l:");
	Serial.print(line++);
	Serial.print('\n');
}

void ready() {
	bufferPos = 0;
	buffer[0] = '\0';
	Serial.print(F("ready\n"));
}

void moveTo(int dx, int dy) {
	int dirx = dx > 0 ? 1 : -1;
	int diry = dy > 0 ? 1 : -1;

	dx = abs(dx);
	dy = abs(dy);

	long i, over = 0;

	if (dx > dy) {
		over = dx / 2;
		for (i = 0; i < dx; ++i) {
			xStepper.step(dirx);
			over += dy;
			if (over >= dx) {
				over -= dx;
				yStepper.step(diry);
			}
			delayMicroseconds(2000);
		}
	} else {
		over = dy / 2;
		for (i = 0; i < dy; ++i) {
			yStepper.step(diry);
			over += dx;
			if (over >= dy) {
				over -= dy;
				xStepper.step(dirx);
			}
			delayMicroseconds(2000);
		}
	}
}

void setup() {
	Serial.begin(9600);
	ready();
	line = 0;
}

void loop() {
	// Listen for commands
	if (Serial.available() > 0) {
		char c = Serial.read();
		if (bufferPos < BUFFER_SIZE) buffer[bufferPos++] = c;
		if (c == '\n') {
			processCommand();
			ready();
		}
	}
}