/*
 * BedRoomKids.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include "KidsBedroom.h"

#include <PubSubClient.h>
#include <stdbool.h>
#include <WString.h>

KidsBedroom::KidsBedroom(PubSubClient* mqttClient, bool DEBUG) : Room(id, mqttClient){
	setDebug(DEBUG);
	if(Debug()) {
		mqttClient->publish("DEBUG","BedRoomKids::BedRoomKids");
	}

	// initialize and create Output controllers
	kidsRadiatorOne = new OutputControl(KIDS_BEDROOM_RAD_ONE, OFF, RAD_KIDS_01_CB, mqttClient);
	kidsRadiatorTwo = new OutputControl(KIDS_BEDROOM_RAD_TWO, OFF, RAD_KIDS_02_CB, mqttClient);
	setHasHeatingControl(true);
	// initialize and create sensors
	Sensor* tempSensor = createSensor(TEMPERATURE, mqttClient, SENSOR_KIDS_01);
	setTempSensor((TemperatureSensor*)tempSensor);

	// Set MQTT topics to listen to...
	setMqttTopics(topics);
	setLen(length);

	subscribeMqttTopics(mqttClient);
}

KidsBedroom::~KidsBedroom() {
	delete kidsRadiatorOne;
	delete kidsRadiatorTwo;
}

// Virtual functions - defined here the outputs associated with specific services (heat, chill, humidity)
void KidsBedroom::heatOutputs(bool state) {
	kidsRadiatorOne->setPin(state);
	kidsRadiatorTwo->setPin(state);
}

void KidsBedroom::mqttReceive(const char* topic, const char* payload) {
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
	} else {
		getMqttClient()->publish("DEBUG", "No matching rules found");
	}
}
