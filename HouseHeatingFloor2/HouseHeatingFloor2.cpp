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
Adapter* mainAdapter;

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
void triggerFunc() {
	//	Simulation values for sensors for testing purposes.
	//	In main program these will be triggered by real sensors updates
	short tempSensorKids = random(15, 35);
	mainAdapter->sensorUpdate(SENSOR_KIDS_01, tempSensorKids);

	short tempSensorCorridor = random(15, 35);
	mainAdapter->sensorUpdate(SENSOR_CORRIDOR_01, tempSensorCorridor);

	short tempSensorBigBath = random(15, 35);
	mainAdapter->sensorUpdate(SENSOR_BIGBATH_01, tempSensorBigBath);
	short humSensorBigBath = random(45, 100);
	mainAdapter->sensorUpdate(SENSOR_BIGBATH_02, humSensorBigBath);

	short tempSensorMasterBedroom = random(15, 35);
	mainAdapter->sensorUpdate(SENSOR_MASTER_BEDROOM_01, tempSensorMasterBedroom);

	short tempSensorWardrobe = random(15, 35);
	mainAdapter->sensorUpdate(SENSOR_WARDROBE_01, tempSensorWardrobe);

	short tempSensorBedroomBath = random(15, 35);
	mainAdapter->sensorUpdate(SENSOR_BEDROOM_BATH_01, tempSensorBedroomBath);
	short humSensorBedroomBath = random(45, 100);
	mainAdapter->sensorUpdate(SENSOR_BEDROOM_BATH_02, humSensorBedroomBath);
}

//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(115200);
	Ethernet.begin(macAddress, ipAddress);


	MqttUtil::mqttConnect(mqttClient, mainAdapter);
	mainAdapter = new Adapter(roomManager, mqttClient, DEBUG);

	roomManager->createRoom(KIDS_BEDROOM);
	roomManager->createRoom(CORRIDOR);
	roomManager->createRoom(BIG_BATHROOM);
	roomManager->createRoom(MASTER_BEDROOM);
	roomManager->createRoom(WARDROBE);
	roomManager->createRoom(BEDROOM_BATH);

	mainAdapter->mqttSubscribe();

	trigger.every(REOCCURRENCE,&triggerFunc);
	triggerFunc();
}

// The loop function is called in an endless loop
void loop()
{
	if (MqttUtil::mqttConnect(mqttClient, mainAdapter)) {
		mqttClient->loop();
	}
	trigger.update();
}
