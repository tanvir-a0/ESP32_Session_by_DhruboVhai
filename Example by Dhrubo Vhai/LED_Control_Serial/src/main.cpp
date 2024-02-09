#include <Arduino.h>

#define LED_PIN						LED_BUILTIN			// On board LED


void setup()
{
	Serial.begin(115200);
	pinMode(LED_PIN, OUTPUT);
}

void loop()
{
	char c = ' ';
	if (Serial.available())
	{
		c = Serial.read();
	}

	if (c == 'a')
	{
		digitalWrite(LED_PIN, HIGH);
	}
	else if (c == 'b')
	{
		digitalWrite(LED_PIN, LOW);
	}
}
