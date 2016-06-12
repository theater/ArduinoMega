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

BedRoomKids::BedRoomKids(PubSubClient* mqttClient) : Room(mqttClient){
	// initialize Output controllers
	setHasTemperatureControl(true);
	kidsRadiatorOne = new OutputControl(KIDS_BEDROOM_RAD_ONE, 0);
	kidsRadiatorTwo = new OutputControl(KIDS_BEDROOM_RAD_TWO, 0);
	// Set MQTT topics to listen to

	// subscribe to these topics
	mqttSubscribe(mqttTopics,2);
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
//	Serial.println(mqttTopics[0]);
//	Serial.println(mqttTopics[1]);
}

void BedRoomKids::mqttSubscribe(const String* topics, int len) {
	PubSubClient* mqttClient = getMqttClient();
	for (int i = 0; i < len; i++) {
//		char toCharArray[]; = topics[i].toCharArray();
//		mqttClient->subscribe(toCharArray);
	}
}

void BedRoomKids::mqttParse(char* topic, char* payload) {
	String strTopic = String(topic);
	String strPayload = String(payload);
	if (strTopic == SENSOR_KIDS_01) {
		setDesiredTemperature(atoi(payload));
		return;
	}
	if (strTopic == SENSOR_BEDROOM_BATH_02) {
		setDesiredHumidity(atoi(payload));
		return;
	}
}
