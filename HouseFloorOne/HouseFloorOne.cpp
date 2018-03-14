// Do not remove the include below

#include "HouseFloorOne.h"

#include <Config.h>
#include <DallasTemperature.h>
#include <Enc28J60Network.h>
#include <Manager.h>
#include <Sensor.h>
#include <Timer.h>
#include <WString.h>

#include "Model/LivingRoom.h"

// Ethernet client
uint8_t macAddress[6] = MAC_ADDRESS;
IPAddress ipAddress(IP_ADDRESS);
EthernetClient ethClient;

//EMON
//EnergyMonitor energyMon;

//DS18B20
OneWire oneWire(ONE_WIRE_PIN_01);
DallasTemperature owSensors(&oneWire);
Manager* manager = new Manager();

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

	logDebug("Waiting 5000 ms...");
	delay(5000);

	logDebug("Initializing MQTT...");
	IPAddress mqttServerAddress(MQTT_SERVER);
	MqttUtil::initializeMqttUtil(new PubSubClient(mqttServerAddress, 1883, mqttCallback, ethClient));

	logDebug("Create timer for sensor reoccurrence...");
	sensorsUpdateTrigger.every(REOCCURRENCE, &sensorsUpdate);

	Room* livingRoom = manager->addRoom(new Room(LIVING_ROOM));
	livingRoom01 = livingRoom->addSensor(new Sensor(TEMPERATURE, SENSOR_LR_01, true));

	owSensors.begin();
	printOneWireAddresses(&owSensors);

	logDebug("Update sensors...");
	sensorsUpdate();
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
	int count = owSensors.getDeviceCount();
	owSensors.requestTemperatures();
	for (int i = 0; i < (sizeof(oneWireSensors) / sizeof(oneWireSensors[0])); i++) {
		float tempSensor = owSensors.getTempC(oneWireSensors[i].address);
		char strValue[10];
		sprintf(strValue, "%f", tempSensor);
		manager->updateReceived(oneWireSensors[i].mqttTopic, strValue);
		logDebug("DS18B20 Sensor " + String(i) + " temperature: " + String(tempSensor) + "C");
	}
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
