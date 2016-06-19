// Do not remove the include below

#include "HouseHeating.h"

#include <Arduino.h>
#include <dht.h>
#include <DallasTemperature.h>
#include <ethernet_comp.h>
#include <EmonLib.h>
#include <HardwareSerial.h>
#include <IPAddress.h>
#include <OneWire.h>
#include <PubSubClient.h>
#include <Timer.h>
#include <UIPClient.h>
#include <UIPEthernet.h>

#include "Config/Config.h"
#include "Model/HeatingAdapter.h"
#include "Model/Util.h"
#include "Util/mqtt.h"

// Ethernet client
uint8_t macAddress[6] = MAC_ADDRESS;
IPAddress ipAddress(IP_ADDRESS);
EthernetClient ethClient;

//MQTT
byte mqttServerAddress[] = MQTT_SERVER;
PubSubClient *mqttClient = new PubSubClient(mqttServerAddress, 1883, mqttCallback, ethClient);

//	HeatingAdapter -> all logic and model is inside this
HeatingAdapter* heatingAdapter;

//EMON
//EnergyMonitor energyMon;

//DS18B20
//OneWire oneWire(ONE_WIRE_PIN_01);
//DallasTemperature sensors(&oneWire);
//
//// DHT22
//dht DHT22;



Timer trigger;
void triggerFunc(){
//	short desTemperature = random(20,25);	 	//simulation values
//	heatingAdapter->updateRoomDesiredValue(KIDS_BEDROOM, TEMPERATURE, desTemperature);

	short tempSensorReal = random(15,35);  		//simulation values
	heatingAdapter->sensorUpdate(SENSOR_KIDS_01,tempSensorReal);
}

//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(115200);
	Ethernet.begin(macAddress, ipAddress);
	mqttConnect(mqttClient, heatingAdapter);
	heatingAdapter = new HeatingAdapter(mqttClient, false);

	trigger.every(REOCCURRENCE,&triggerFunc);
	triggerFunc();
}

// The loop function is called in an endless loop
void loop()
{
	if (mqttConnect(mqttClient, heatingAdapter)) {
		mqttClient->loop();
	}
	trigger.update();
}
