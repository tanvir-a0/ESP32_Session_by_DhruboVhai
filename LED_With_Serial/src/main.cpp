#include <Arduino.h>
void ledStatusControl(char x);

char serial_char = 'a';

void setup() {

  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);

}

void loop() {
  if(Serial.available())
  {
    ledStatusControl(Serial.read());
  }
}

void ledStatusControl(char x)
{
  if (x == 'a')
  {
    digitalWrite(BUILTIN_LED, HIGH);
  }
  if (x == 's')
  {
    digitalWrite(BUILTIN_LED, LOW);
  }
}