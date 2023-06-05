// This program moves toggles the laser according to the signal it receives trough the USB port

const int laserPin = 5;
int ledState = 0;

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(9600);
}

void loop() {
	if (Serial.available() > 0) ledState = Serial.read();
	if (ledState) digitalWrite(laserPin, HIGH);
	else digitalWrite(laserPin, HIGH);
}