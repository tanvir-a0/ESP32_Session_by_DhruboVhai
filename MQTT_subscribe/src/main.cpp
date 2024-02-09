#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <string.h>

#define WIFI_SSID                 	"Tanvir Ahmed"
#define WIFI_PASS                 	"Volvo Polestar2"
#define BROKER                    	"broker.hivemq.com"
#define PORT                      	1883
#define CLIENT_ID					"tanvir1"
#define TOPIC 						"Tanvir/IoT/Pub"

int led_status = 1;


WiFiClient espClient;
PubSubClient client(espClient);

void ledStatus(char *status)
{
	Serial.print("Status: ");
	Serial.println(status);
	Serial.print(strcmp(status, "on"));
	if (strcmp(status, "on") == 0)
	{
		led_status = 1;
	}
	if (strcmp(status, "off") == 0)
	{
		led_status = 0;
	}
	digitalWrite(BUILTIN_LED, led_status);
}

void reconnect()
{
	while (!client.connected())
	{
		Serial.println("Attempting MQTT connection...");

		if (client.connect(CLIENT_ID))
		{
			Serial.println("Connected to MQTT broker");
			client.subscribe(TOPIC);
		}
		else
		{
			Serial.print("Failed, rc=");
			Serial.print(client.state());
			Serial.println(" Retrying in 5 seconds...");
			delay(5000);
		}
	}
}

void callback(char *topic, byte *payload, unsigned int length)
{
	Serial.print("Message received on topic: ");
	Serial.println(topic);

	Serial.print("Payload (data received from the topic): ");
	char str_payload[20] = "";
	for (int i = 0; i < length; i++)
	{
		Serial.print((char)payload[i]);
		str_payload[i] = (char)payload[i];
	}
	// for (int i = 0; i < 20; i++)
	// {
	// 	Serial.print(i);
	// 	Serial.print(" ");
	// 	Serial.println(str_payload[i]);
	// }
	str_payload[length] = '\0';
	ledStatus(str_payload);
	Serial.println();
}

void setup()
{
	Serial.begin(115200);

	pinMode(LED_BUILTIN, OUTPUT);

	WiFi.begin(WIFI_SSID, WIFI_PASS);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(1000);
		Serial.println("Connecting to WiFi...");
	}
	Serial.println("Connected to WiFi");

	client.setServer(BROKER, PORT);
	client.setCallback(callback);
	client.subscribe(TOPIC);
}

void loop()
{
	if (!client.connected())
	{
		reconnect();
	}
	client.loop();
}
