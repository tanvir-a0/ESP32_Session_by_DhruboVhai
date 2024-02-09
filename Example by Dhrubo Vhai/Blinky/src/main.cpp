#include <Arduino.h>

#define LED_PIN						LED_BUILTIN			// On board LED
#define LED_BLINK_DELAY				1000				//ms


void setup()
{
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, LOW);
}

void loop()
{
	int led_state = digitalRead(LED_PIN);	// Read pin state. HIGH = 1, LOW = 0
	digitalWrite(LED_PIN, !led_state);		// Toggle pin state
	delay(LED_BLINK_DELAY);					// Block the code for 'LED_BLINK_DELAY' ms
}
