// Do not remove the include below

#include "HouseFloorOne.h"

#include <Config.h>
#include <DallasTemperature.h>
#include <Enc28J60Network.h>
#include <Sensor.h>
#include <Timer.h>

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
RoomManager* manager = RoomManager::getInstance();

// Sensors update trigger timer
Timer sensorsUpdateTrigger;
Sensor* livingRoom01;

// MQTT Reconnect Timer
Timer mqttReconnectTimer;
int8_t mqttReconnectTimerEventId;
bool mqttDisconnectFound = false;
int8_t reconnectAttempts = 0;

//The setup function is called once at startup of the sketch
void setup() {
	Serial.begin(BAUD_RATE);
	logDebug("Beginning setup()...");

	logDebug("Ethernet.begin...");
	Ethernet.begin(macAddress, ipAddress);


	logDebug("Create timer for sensor reoccurrence...");
	sensorsUpdateTrigger.every(REOCCURRENCE, &sensorsUpdate);

	livingRoom01 = new Sensor(TEMPERATURE, SENSOR_LR_01, true);

	owSensors.begin();
	printOneWireAddresses(&owSensors);

	logDebug("Update sensors...");
	sensorsUpdate();

	logDebug("Initializing MQTT...");
	IPAddress mqttServerAddress(MQTT_SERVER);
	MqttUtil::initializeMqttUtil(new PubSubClient(mqttServerAddress, 1883, mqttCallback, ethClient));
}

// The loop function is called in an endless loop
void loop() {
	sensorsUpdateTrigger.update();

	if (MqttUtil::isConnected()) {
		MqttUtil::loop();
	} else if (!mqttDisconnectFound) {
		mqttDisconnectFound = true;
		logError("MQTT Not connected. Another attempt in a while...");
		mqttReconnectTimerEventId = mqttReconnectTimer.every(REOCCURRENCE, &reconnect);
	}
	if(mqttDisconnectFound) {
		mqttReconnectTimer.update();
	}
}

void mqttCallback(const char* topic, uint8_t* payload, unsigned int length) {

}

void sensorsUpdate() {
	owSensors.requestTemperatures();
	//	float bedroomBathTemp = humBedroomBath.readTemperature();
	//	float bedroomBathHum = humBedroomBath.readHumidity();
	//
	//	float bigBathTemp = humBigBath.readTemperature();
	//	float bigBathHum = humBigBath.readHumidity();

//		short tempSensorKids = random(15, 35);
//		roomManager->mqttUpdate(SENSOR_KIDS_01, tempSensorKids);
//
//		short tempSensorCorridor = random(15, 35);
//		roomManager->mqttUpdate(SENSOR_CORRIDOR_01, tempSensorCorridor);
//
//		short tempSensorBigBath = random(15, 35);
//		roomManager->mqttUpdate(SENSOR_BIGBATH_01, tempSensorBigBath);
//		short humSensorBigBath = random(45, 100);
//		roomManager->mqttUpdate(SENSOR_BIGBATH_02, humSensorBigBath);
	//
	//	short tempSensorMasterBedroom = random(15, 35);
	float tempSensor0 = owSensors.getTempC(oneWireSensors[0].address);
	if(DEBUG) {
		Serial.print("Sensor temperature: ");
		Serial.print(tempSensor0);
		Serial.println("C");
	}

	livingRoom01->setValue(oneWireSensors[0].mqttTopic, tempSensor0);
	//	if(tempSensorMasterBedroom > -20) {
	//		roomManager->sensorUpdate(SENSOR_MASTER_BEDROOM_01, tempSensorMasterBedroom);
	//	}

	//	short tempSensorWardrobe = random(15, 35);
	//	float tempSensorWardrobe = owSensors.getTempCByIndex(1);
	//	if(tempSensorWardrobe > -20) {
	//		roomManager->sensorUpdate(SENSOR_WARDROBE_01, tempSensorWardrobe);
	//	}
}

void reconnect() {
	logInfo("MQTT reconnect function executed.");
	MqttUtil::connect();
	if (MqttUtil::isConnected()) {
		logInfo("MQTT connected successfully.");
		mqttDisconnectFound = false;
		mqttReconnectTimer.stop(mqttReconnectTimerEventId);
		reconnectAttempts = 0;
	} else {
		reconnectAttempts++;
		logInfo("Reconnect not possible. Attempt:" + String(reconnectAttempts));
		if(reconnectAttempts > 5) {
			logInfo("Attempting restart of ethernet.");
			Enc28J60.init(macAddress);
		}
	}
}
