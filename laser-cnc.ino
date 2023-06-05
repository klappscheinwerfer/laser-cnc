#include <Stepper.h>

const int stepsPerRevolution = 200;

// Motors - X axis
const int xDirPin = 8;
const int xStepPin = 9;
Stepper xStepper(stepsPerRevolution, xDirPin, xStepPin);
const float xMultiplier = 0.25;

// Motors - Y axis
const int yDirPin = 2;
const int yStepPin = 3;
Stepper yStepper(stepsPerRevolution, yDirPin, yStepPin);
const float yMultiplier = 0.25;

// Motors - Feedrate
#define MIN_FEEDRATE 0.1
#define MAX_FEEDRATE 3000
float feedrate = 0;
long stepDelay; // microseconds

// Laser
const int laserPin = 5;

// Serial communication
#define BAUD 9600
#define BUFFER_SIZE 64
char buffer[BUFFER_SIZE];
int bufferPos;

// Commands
int line;

void pause(long ms) {
	delay(ms / 1000);
	delayMicroseconds(ms % 1000);
}

void setFeedrate(float f) {
	if (feedrate == f) return;

	if (f < MIN_FEEDRATE || f > MAX_FEEDRATE) {
		Serial.print(F("e:feedrate_too_"));
		Serial.print(f < MIN_FEEDRATE ? F("low\n") : F("high\n"));
		return;
	}
	stepDelay = 1000000.0 / f;
	feedrate = f;
}

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

int emergencyStopCheck() {
	if (Serial.available() == 0) return false;
	// If any character is received, perform emergency stop
	digitalWrite(laserPin, LOW);
	return true;
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
			setFeedrate(parseAttribute('F', feedrate));
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
	
	// Print line number
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
			if (emergencyStopCheck()) return;
			pause(stepDelay);
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
			if (emergencyStopCheck()) return;
			pause(stepDelay);
		}
	}
}

void setup() {
	Serial.begin(BAUD);
	setFeedrate((MIN_FEEDRATE + MAX_FEEDRATE) / 2);

	// Debug: print feedrate
	Serial.print("d:feedrate_");
	Serial.print(feedrate);
	Serial.print('\n');

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
		} else if (c == '\e') {
			emergencyStopCheck();
		}
	}
}