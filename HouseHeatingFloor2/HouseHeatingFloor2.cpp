// Do not remove the include below

#include "HouseHeatingFloor2.h"

#include <Arduino.h>
#include <ethernet_comp.h>
#include <HardwareSerial.h>
#include <IPAddress.h>
#include "MqttUtil.h"
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
RoomManager* roomManager = RoomManager::getInstance();

Timer mqttReconnectTimer;
int8_t mqttReconnectTimerEventId;
bool mqttDisconnectFound = false;
Timer sensorsUpdateTrigger;

void sensorsUpdate() {
	owSensors.requestTemperatures();
//	float bedroomBathTemp = humBedroomBath.readTemperature();
//	float bedroomBathHum = humBedroomBath.readHumidity();
//
//	float bigBathTemp = humBigBath.readTemperature();
//	float bigBathHum = humBigBath.readHumidity();

	short tempSensorKids = random(15, 35);
	roomManager->mqttUpdate(SENSOR_KIDS_01, tempSensorKids);

	short tempSensorCorridor = random(15, 35);
	roomManager->mqttUpdate(SENSOR_CORRIDOR_01, tempSensorCorridor);

	short tempSensorBigBath = random(15, 35);
	roomManager->mqttUpdate(SENSOR_BIGBATH_01, tempSensorBigBath);
	short humSensorBigBath = random(45, 100);
	roomManager->mqttUpdate(SENSOR_BIGBATH_02, humSensorBigBath);
//
//	short tempSensorMasterBedroom = random(15, 35);
//	float tempSensorMasterBedroom = owSensors.getTempCByIndex(0);
//	if(tempSensorMasterBedroom > -20) {
//		roomManager->sensorUpdate(SENSOR_MASTER_BEDROOM_01, tempSensorMasterBedroom);
//	}

//	short tempSensorWardrobe = random(15, 35);
//	float tempSensorWardrobe = owSensors.getTempCByIndex(1);
//	if(tempSensorWardrobe > -20) {
//		roomManager->sensorUpdate(SENSOR_WARDROBE_01, tempSensorWardrobe);
//	}

	short tempSensorBedroomBath = random(15, 35);
	roomManager->mqttUpdate(SENSOR_BEDROOM_BATH_01, tempSensorBedroomBath);
	short humSensorBedroomBath = random(45, 100);
	roomManager->mqttUpdate(SENSOR_BEDROOM_BATH_02, humSensorBedroomBath);
}

void mqttCallback(const char* topic, uint8_t* payload, unsigned int length) {

}

//The setup function is called once at startup of the sketch
void setup() {
	Serial.begin(BAUD_RATE);
	logDebug("Beginning setup()...");

	logDebug("Ethernet.begin...");
	Ethernet.begin(macAddress, ipAddress);

	logDebug("Initializing MQTT...");
	IPAddress mqttServerAddress(MQTT_SERVER);
	MqttUtil::initializeMqttUtil(new PubSubClient(mqttServerAddress, 1883, roomManager->mqttCallback, ethClient));


	logDebug("Create rooms...");

	roomManager->createRooms();
	roomManager->mqttSubscribe();

//	logDebug("One wire begin...");
//	owSensors.begin();
//
//	logDebug("DHT sensors begin...");
//	humBedroomBath.begin();
//	humBigBath.begin();

	logDebug("Create timer for sensor reoccurrence...");
	sensorsUpdateTrigger.every(REOCCURRENCE,&sensorsUpdate);

	logDebug("Update sensors...");
	sensorsUpdate();

	logInfo("Finishing setup()...");
}

// The loop function is called in an endless loop
void loop() {
	if (MqttUtil::isConnected()) {
		MqttUtil::loop();
	} else if (!mqttDisconnectFound) {
		mqttDisconnectFound = true;
		logError("MQTT Not connected. Another attempt in a while...");
		mqttReconnectTimerEventId = mqttReconnectTimer.every(REOCCURRENCE, &reconnect);
	}
	mqttReconnectTimer.update();
	sensorsUpdateTrigger.update();
}

void reconnect() {
	MqttUtil::connect();
	if (MqttUtil::isConnected()) {
		logInfo("MQTT connected successfully.");
		mqttDisconnectFound = false;
		mqttReconnectTimer.stop(mqttReconnectTimerEventId);
		logInfo("Room manager subscribing to topics.");
		roomManager->mqttSubscribe();
	}
}
