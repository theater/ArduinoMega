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

BedRoomKids::BedRoomKids(PubSubClient* mqttClient) : Room(id, mqttClient){
	if(DEBUG) {
		mqttClient->publish("DEBUG","BedRoomKids::BedRoomKids");
	}

	// initialize and create Output controllers
	radiatorOne = new OutputControl(KIDS_BEDROOM_RAD_ONE, OFF, RAD_KIDS_01_CB, mqttClient);
	radiatorTwo = new OutputControl(KIDS_BEDROOM_RAD_TWO, OFF, RAD_KIDS_02_CB, mqttClient);
	setHasHeatingControl(true);

	// initialize and create sensors
	Sensor* tempSensor = createSensor(TEMPERATURE, mqttClient, SENSOR_KIDS_01, true);
	setTempSensor((TemperatureSensor*)tempSensor);

	// Set MQTT topics to listen to...
	setMqttTopics(topics);
	setLen(length);

	subscribeMqttTopics(mqttClient);
}

BedRoomKids::~BedRoomKids() {
	delete radiatorOne;
	delete radiatorTwo;
	delete getTempSensor();
}

// Virtual functions - defined here the outputs associated with specific services (heat, chill, humidity)
void BedRoomKids::heatOutputs(bool state) {
	radiatorOne->setPin(state);
	radiatorTwo->setPin(state);
}

void BedRoomKids::mqttReceive(const char* topic, const char* payload) {
	String strTopic = String(topic);
	String strPayload = String(payload);
	if (strTopic.equals(MODE_KIDS)) {
		updateMode(payload);
	} else if (strTopic.equals(DESIRED_TEMP_KIDS_01)) {
		updateDesiredTemperature(atof(payload));
	} else if (strTopic.equals(RAD_KIDS_01)) {
		mqttUpdateOutputControl(radiatorOne, payload);
	} else if (strTopic.equals(RAD_KIDS_02)) {
		mqttUpdateOutputControl(radiatorTwo, payload);
	} else {
		getMqttClient()->publish("DEBUG", "No matching rules found");
	}
}
