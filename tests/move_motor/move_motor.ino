// This program moves the laser on one axis forwards and backwards

const int dirPin = 8;
const int stepPin = 9;
const int stepsPerRevolution = 200;

void setup() {
	pinMode(stepPin, OUTPUT);
	pinMode(dirPin, OUTPUT);
}

void loop() {
	digitalWrite(dirPin, HIGH);

	for(int x = 0; x < stepsPerRevolution; x++) {
		digitalWrite(stepPin, HIGH);
		delayMicroseconds(2000);
		digitalWrite(stepPin, LOW);
		delayMicroseconds(2000);
	}
	delay(1000);

	digitalWrite(dirPin, LOW);

	for(int x = 0; x < stepsPerRevolution; x++)
	{
		digitalWrite(stepPin, HIGH);
		delayMicroseconds(1000);
		digitalWrite(stepPin, LOW);
		delayMicroseconds(1000);
	}
	delay(1000);
}