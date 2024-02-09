#include <Arduino.h>

#include <WiFi.h>
#include <PubSubClient.h>


#define WIFI_SSID                 	""
#define WIFI_PASS                 	""
#define BROKER                    	"broker.hivemq.com"
#define PORT                      	1883
#define CLIENT_ID					"abknfoiwhefioewq"



WiFiClient espClient;
PubSubClient client(espClient);

void reconnect()
{
	// Loop until we're reconnected
	while (!client.connected())
	{
		Serial.println("Attempting MQTT connection...");

		// Attempt to connect
		if (client.connect(CLIENT_ID))
		{
			Serial.println("Connected to MQTT broker");
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

	Serial.print("Payload: ");
	for (int i = 0; i < length; i++)
	{
		Serial.print((char)payload[i]);
	}
	Serial.println();
}

void setup()
{
	Serial.begin(115200);
	// Connect to Wi-Fi
	WiFi.begin(WIFI_SSID, WIFI_PASS);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(1000);
		Serial.println("Connecting to WiFi...");
	}
	Serial.println("Connected to WiFi");

	// Set up MQTT
	client.setServer(BROKER, PORT);
}

void loop()
{
	if (!client.connected())
	{
		reconnect();
	}

	// Your custom data to be sent
	char payload[] = "Hello, MQTT!";

	// Publish data to a specific topic
	client.publish("RME/IoT/Pub", payload);

	// Wait for a few seconds before publishing again
	delay(5000);
}
