// Do not remove the include below

#include "HouseHeatingFloor2.h"

#include <Adapter.h>
#include <Arduino.h>
#include <dht.h>
#include <DallasTemperature.h>
#include <ethernet_comp.h>
#include <HardwareSerial.h>
#include <IPAddress.h>
#include <MqttUtil.h>
#include <OneWire.h>
#include <PubSubClient.h>
#include <stddef.h>
#include <stdint.h>
#include <Timer.h>
#include <UIPClient.h>
#include <UIPEthernet.h>
#include <Util.h>

#include "Config/Config.h"
#include "Model/RoomManager.h"

// Ethernet client
uint8_t macAddress[6] = MAC_ADDRESS;
IPAddress ipAddress(IP_ADDRESS);
EthernetClient ethClient;

//MQTT
byte mqttServerAddress[] = MQTT_SERVER;
PubSubClient *mqttClient = new PubSubClient(mqttServerAddress, 1883, MqttUtil::mqttCallback, ethClient);

//	HeatingAdapter -> all logic and model is inside this
Adapter* heatingAdapter;

//EMON
//EnergyMonitor energyMon;

//DS18B20
OneWire oneWire(ONE_WIRE_PIN_01);
DallasTemperature sensors(&oneWire);
//
//// DHT22
dht DHT22;

// Initialize manager
RoomManager* RoomManager::manager = NULL;
RoomManager* roomManager = RoomManager::getInstance(mqttClient);


Timer trigger;
void triggerFunc(){
	//simulation value for temperature sensor for testing purposes
	short tempSensorKids = random(15,35);
	heatingAdapter->sensorUpdate(SENSOR_KIDS_01,tempSensorKids);

	short tempSensorCorridor = random(15,35);
	heatingAdapter->sensorUpdate(SENSOR_CORRIDOR_01,tempSensorCorridor);

	short tempSensorBigBath = random(15,35);
	heatingAdapter->sensorUpdate(SENSOR_BIGBATH_01,tempSensorBigBath);
	short humSensorBigBath = random(45,100);
	heatingAdapter->sensorUpdate(SENSOR_BIGBATH_02,humSensorBigBath);
}

//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(115200);
	Ethernet.begin(macAddress, ipAddress);


	MqttUtil::mqttConnect(mqttClient, heatingAdapter);
	heatingAdapter = new Adapter(roomManager, mqttClient, DEBUG);

	roomManager->createRoom(KIDS_BEDROOM);
	roomManager->createRoom(CORRIDOR);
	roomManager->createRoom(BIG_BATHROOM);

	heatingAdapter->mqttSubscribe();

	trigger.every(REOCCURRENCE,&triggerFunc);
	triggerFunc();
}

// The loop function is called in an endless loop
void loop()
{
	if (MqttUtil::mqttConnect(mqttClient, heatingAdapter)) {
		mqttClient->loop();
	}
	trigger.update();
}
