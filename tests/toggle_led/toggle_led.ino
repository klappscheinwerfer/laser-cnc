// This program moves toggles the built-in LED according to the signal it receives trough the USB port

int ledState = 0;

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(9600);
}

void loop() {
	if (Serial.available() > 0) ledState = Serial.read();
	if (ledState) digitalWrite(LED_BUILTIN, HIGH);
	else digitalWrite(LED_BUILTIN, LOW);
}