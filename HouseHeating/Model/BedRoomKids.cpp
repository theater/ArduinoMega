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
	// initialize Output controllers
	setDebug(DEBUG);
	if(Debug()) {
//		Serial.println("Calling BedRoomKids constructor");
		mqttClient->publish("DEBUG","BedRoomKids::BedRoomKids");
	}
	setHasTemperatureControl(true);
	kidsRadiatorOne = new OutputControl(KIDS_BEDROOM_RAD_ONE, 0, RAD_KIDS_01_CB, mqttClient);
	kidsRadiatorTwo = new OutputControl(KIDS_BEDROOM_RAD_TWO, 0, RAD_KIDS_02_CB, mqttClient);
	Sensor* tempSensor = createSensor(TEMPERATURE, mqttClient, SENSOR_KIDS_01);
	setTempSensor((TemperatureSensor*)tempSensor);

	// Set MQTT topics to listen to
	// subscribe to these topics
	mqttSubscribe(mqttTopics, len, mqttClient);
}

BedRoomKids::~BedRoomKids() {
	delete kidsRadiatorOne;
	delete kidsRadiatorTwo;
}

void BedRoomKids::updateOutputControllers() {
	//Heating
	if (getHasTemperatureControl() && getDecisionHeating()) {
		kidsRadiatorOne->setPin(ON);
		kidsRadiatorTwo->setPin(ON);
	} else {
		kidsRadiatorOne->setPin(OFF);
		kidsRadiatorTwo->setPin(OFF);
	}
}

void BedRoomKids::mqttSubscribe(const char* const* topics, int len, PubSubClient* const mqttClient) {
	for (int i = 0; i < len; i++) {
		mqttClient->subscribe(topics[i]);
		mqttClient->publish("DEBUG",topics[i]);
	}
}

void BedRoomKids::mqttReceive(const char* topic, const char* payload) {
	String strTopic = String(topic);
	String strPayload = String(payload);
	if (strTopic.equals(DESIRED_KIDS_01)) {
		updateDesiredTemperature(atof(payload));
		return;
	} else if (strTopic.equals(RAD_KIDS_01)) {
		if (!strcmp(payload, "ON")) {
			kidsRadiatorOne->setPin(ON);
		} else {
			kidsRadiatorOne->setPin(OFF);
		}
	} else if (strTopic.equals(RAD_KIDS_02)) {
		if (!strcmp(payload, "ON")) {
			kidsRadiatorTwo->setPin(ON);
		} else {
			kidsRadiatorTwo->setPin(OFF);
		}
	} else {
		getMqttClient()->publish("DEBUG", "No matching rules found");
	}
//	updateOutputControllers();
}

bool BedRoomKids::containsTopic(const char * topic) {
	for(int i=0;i<len;i++) {
		if(!strcmp(mqttTopics[i], topic)) {
			return true;
		}
	}
	return false;
}

const char** BedRoomKids::getMqttTopics() {
	return mqttTopics;
}
