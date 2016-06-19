/*
 * BedRoomKids.cpp
 *
 *  Created on: 11.06.2016 �.
 *      Author: theater
 */

#include "BedRoomKids.h"

#include <PubSubClient.h>
#include <stdbool.h>
#include <WString.h>

BedRoomKids::BedRoomKids(PubSubClient* mqttClient, bool DEBUG) : Room(mqttClient){
	setDebug(DEBUG);
	if(Debug()) {
//		Serial.println("Calling BedRoomKids constructor");
		mqttClient->publish("DEBUG","BedRoomKids::BedRoomKids");
	}

	// initialize and create Output controllers
	kidsRadiatorOne = new OutputControl(KIDS_BEDROOM_RAD_ONE, OFF, RAD_KIDS_01_CB, mqttClient);
	kidsRadiatorTwo = new OutputControl(KIDS_BEDROOM_RAD_TWO, OFF, RAD_KIDS_02_CB, mqttClient);
	setHasHeatingControl(true);
	chiller = new OutputControl(CHILLER_PIN, OFF, CHILLER_CB, mqttClient);
	setHasCoolingControl(true);
	// initialize and create sensors
	Sensor* tempSensor = createSensor(TEMPERATURE, mqttClient, SENSOR_KIDS_01);
	setTempSensor((TemperatureSensor*)tempSensor);

	// Set MQTT topics to listen to...
	subscribeMqttTopics(mqttClient);
}

BedRoomKids::~BedRoomKids() {
	delete kidsRadiatorOne;
	delete kidsRadiatorTwo;
	delete chiller;
}

void BedRoomKids::updateOutputControllers() {
	//Heating
	if (getHasHeatingControl() && getDecisionHeat()) {
		kidsRadiatorOne->setPin(ON);
		kidsRadiatorTwo->setPin(ON);
	} else {
		kidsRadiatorOne->setPin(OFF);
		kidsRadiatorTwo->setPin(OFF);
	}
	if(getHasCoolingControl() && getDecisionCool()) { //
		chiller->setPin(ON);
	} else {
		chiller->setPin(OFF);
		return;
	}
}


void BedRoomKids::mqttReceive(const char* topic, const char* payload) {
	String strTopic = String(topic);
	String strPayload = String(payload);
	if (strTopic.equals(DESIRED_KIDS_01)) {
		updateDesiredTemperature(atof(payload));
		return;
	} else if (strTopic.equals(RAD_KIDS_01)) {
		handleMqttCommandOC(kidsRadiatorOne, payload);
	} else if (strTopic.equals(RAD_KIDS_02)) {
		handleMqttCommandOC(kidsRadiatorTwo, payload);
	} else if (strTopic.equals(CHILLER)) {
		handleMqttCommandOC(chiller, payload);
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

void BedRoomKids::subscribeMqttTopics(PubSubClient* mqttClient) {
	mqttSubscribe(mqttTopics, len, mqttClient);
}

void BedRoomKids::mqttSubscribe(const char* const* topics, int len, PubSubClient* const mqttClient) {
	for (int i = 0; i < len; i++) {
		mqttClient->subscribe(topics[i]);
		mqttClient->publish("DEBUG",topics[i]);
	}
}

void BedRoomKids::handleMqttCommandOC(OutputControl* outputControl, const char* payload) {
	if (!strcmp(payload, "ON")) {
		outputControl->setPin(ON);
	} else {
		outputControl->setPin(OFF);
	}
}
