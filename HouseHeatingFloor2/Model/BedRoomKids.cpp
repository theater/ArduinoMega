/*
 * BedRoomKids.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include "BedRoomKids.h"

#include <PubSubClient.h>
#include <stdbool.h>
#include <WString.h>

BedRoomKids::BedRoomKids(PubSubClient* mqttClient, bool DEBUG) : Room(mqttClient){
	setDebug(DEBUG);
	if(Debug()) {
		mqttClient->publish("DEBUG","BedRoomKids::BedRoomKids");
	}

	// initialize and create Output controllers
	kidsRadiatorOne = new OutputControl(KIDS_BEDROOM_RAD_ONE, OFF, RAD_KIDS_01_CB, mqttClient);
	kidsRadiatorTwo = new OutputControl(KIDS_BEDROOM_RAD_TWO, OFF, RAD_KIDS_02_CB, mqttClient);
	setHasHeatingControl(true);

	kidsChiller = new OutputControl(CHILLER_PIN, OFF, CHILLER_CB, mqttClient);
	setHasCoolingControl(true);

	kidsFan = new OutputControl(FAN_PIN, OFF, FAN_KIDS_01_CB, mqttClient);
	setHasVentControl(true);

	// initialize and create sensors
	Sensor* tempSensor = createSensor(TEMPERATURE, mqttClient, SENSOR_KIDS_01);
	setTempSensor((TemperatureSensor*)tempSensor);
	Sensor* humSensor = createSensor(HUMIDITY, mqttClient, SENSOR_KIDS_02);
	setHumSensor((HumiditySensor*)humSensor);

	// Set MQTT topics to listen to...
	setMqttTopics(topics);
	setLen(length);

	subscribeMqttTopics(mqttClient);
}

BedRoomKids::~BedRoomKids() {
	delete kidsRadiatorOne;
	delete kidsRadiatorTwo;
	delete kidsChiller;
}

// Virtual functions - defined here the outputs associated with specific services (heat, chill, humidity)
void BedRoomKids::heatOutputs(bool state) {
	kidsRadiatorOne->setPin(state);
	kidsRadiatorTwo->setPin(state);
}

void BedRoomKids::chillOutputs(bool state) {
	kidsChiller->setPin(state);
}

void BedRoomKids::humidityOutputs(bool state) {
	kidsFan->setPin(state);
}

void BedRoomKids::mqttReceive(const char* topic, const char* payload) {
	String strTopic = String(topic);
	String strPayload = String(payload);
	if (strTopic.equals(MODE_KIDS)) {
		updateMode(payload);
	} else if (strTopic.equals(DESIRED_TEMP_KIDS_01)) {
		updateDesiredTemperature(atof(payload));
	} else if (strTopic.equals(RAD_KIDS_01)) {
		handleMqttCommandOC(kidsRadiatorOne, payload);
	} else if (strTopic.equals(RAD_KIDS_02)) {
		handleMqttCommandOC(kidsRadiatorTwo, payload);
	} else if (strTopic.equals(CHILLER)) {
		handleMqttCommandOC(kidsChiller, payload);
	} else if(strTopic.equals(FAN_KIDS_01)){
		handleMqttCommandOC(kidsFan, payload);
	} else if(strTopic.equals(DESIRED_HUM_KIDS_01)) {
		updateDesiredHumidity(atoi(payload));
	} else {
		getMqttClient()->publish("DEBUG", "No matching rules found");
	}
}
