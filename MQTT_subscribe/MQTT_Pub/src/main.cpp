#include <WiFi.h>
#include <string.h>
#include <PubSubClient.h>
#include <Arduino.h>

#define WIFI_SSID                 	"Tanvir Ahmed"
#define WIFI_PASS                 	"Volvo Polestar2"
#define BROKER                    	"broker.hivemq.com"
#define PORT                      	1883
#define CLIENT_ID					"tanvir1"
#define TOPIC 						"Tanvir/IoT/Pub"

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect()
{
	while (!client.connected())
	{
		Serial.println("Attempting MQTT connection...");

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
	WiFi.begin(WIFI_SSID, WIFI_PASS);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(1000);
		Serial.println("Connecting to WiFi...");
	}
	Serial.println("Connected to WiFi");
	client.setServer(BROKER, PORT);
}

int data_count = 0;

void loop()
{
	data_count++;
	if (!client.connected())
	{
		reconnect();
	}
	

	char result[10]; 
    sprintf(result, "%d", data_count);
	char payload[] = "Hi, ";
	strcat(payload, result);


	client.publish(TOPIC, payload);
	Serial.print("Sent the data.");
	delay(5000);
}
