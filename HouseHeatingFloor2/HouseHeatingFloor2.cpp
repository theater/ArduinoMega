// Do not remove the include below

#include "HouseHeatingFloor2.h"

#include <Arduino.h>
#include <DallasTemperature.h>
#include <DHT.h>
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

//EMON
//EnergyMonitor energyMon;

//DS18B20
OneWire oneWire(ONE_WIRE_PIN_01);
DallasTemperature owSensors(&oneWire);
//
//// DHT22

DHT humBigBath(DHT_BIG_BATH, DHT22);
DHT humBedroomBath(DHT_BEDROOM_BATH, DHT22);

// Initialize manager
RoomManager* RoomManager::manager = NULL;
RoomManager* roomManager = RoomManager::getInstance(mqttClient);


Timer trigger;
void sensorsUpdate() {
	owSensors.requestTemperatures();
//	float bedroomBathTemp = humBedroomBath.readTemperature();
//	float bedroomBathHum = humBedroomBath.readHumidity();
//
//	float bigBathTemp = humBigBath.readTemperature();
//	float bigBathHum = humBigBath.readHumidity();

	short tempSensorKids = random(15, 35);
	roomManager->sensorUpdate(SENSOR_KIDS_01, tempSensorKids);

	short tempSensorCorridor = random(15, 35);
	roomManager->sensorUpdate(SENSOR_CORRIDOR_01, tempSensorCorridor);

	short tempSensorBigBath = random(15, 35);
	roomManager->sensorUpdate(SENSOR_BIGBATH_01, tempSensorBigBath);
	short humSensorBigBath = random(45, 100);
	roomManager->sensorUpdate(SENSOR_BIGBATH_02, humSensorBigBath);

//	short tempSensorMasterBedroom = random(15, 35);
	float tempSensorMasterBedroom = owSensors.getTempCByIndex(0);
	if(tempSensorMasterBedroom > -20) {
		roomManager->sensorUpdate(SENSOR_MASTER_BEDROOM_01, tempSensorMasterBedroom);
	}

//	short tempSensorWardrobe = random(15, 35);
	float tempSensorWardrobe = owSensors.getTempCByIndex(1);
	if(tempSensorWardrobe > -20) {
		roomManager->sensorUpdate(SENSOR_WARDROBE_01, tempSensorWardrobe);
	}

	short tempSensorBedroomBath = random(15, 35);
	roomManager->sensorUpdate(SENSOR_BEDROOM_BATH_01, tempSensorBedroomBath);
	short humSensorBedroomBath = random(45, 100);
	roomManager->sensorUpdate(SENSOR_BEDROOM_BATH_02, humSensorBedroomBath);
}

//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(115200);
	Ethernet.begin(macAddress, ipAddress);

	MqttUtil::mqttConnect(mqttClient, roomManager);

	roomManager->createRoom(KIDS_BEDROOM);
	roomManager->createRoom(CORRIDOR);
	roomManager->createRoom(BIG_BATHROOM);
	roomManager->createRoom(MASTER_BEDROOM);
	roomManager->createRoom(WARDROBE);
	roomManager->createRoom(BEDROOM_BATH);

	roomManager->mqttSubscribe();

	owSensors.begin();
	humBedroomBath.begin();
	humBigBath.begin();


	trigger.every(REOCCURRENCE,&sensorsUpdate);
	sensorsUpdate();
}

// The loop function is called in an endless loop
void loop()
{
	if (MqttUtil::mqttConnect(mqttClient, roomManager)) {
		mqttClient->loop();
	}
	trigger.update();
}
