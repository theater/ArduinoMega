/*
 * MasterBedroom.cpp
 *
 *  Created on: 27.06.2016 �.
 *      Author: theater
 */

#include "MasterBedroom.h"


MasterBedroom::MasterBedroom() : Room(id){
		if(DEBUG) {
			MqttUtil::publish("DEBUG","Corridor::Corridor");
		}

		// initialize and create Output controllers
		radiatorOne = new OutputControl(MASTER_BEDROOM_RAD, OFF, RAD_MASTER_BEDROOM_CB);
		setHasHeatingControl(true);
		// initialize and create sensors
		Sensor* tempSensor = createSensor(TEMPERATURE, SENSOR_MASTER_BEDROOM_01, true);
		setTempSensor((TemperatureSensor*)tempSensor);

		// Set MQTT topics to listen to...
		setMqttTopics(topics);
		setLen(length);

		subscribeMqttTopics();
}

MasterBedroom::~MasterBedroom() {
	delete radiatorOne;
	delete getTempSensor();
}

// Virtual functions - defined here the outputs associated with specific services (heat, chill, humidity)
void MasterBedroom::heatOutputs(bool state) {
	radiatorOne->setPin(state);
}

void MasterBedroom::mqttReceive(const char* topic, const char* payload) {
	String strTopic = String(topic);
	String strPayload = String(payload);
	if (strTopic.equals(MODE_MASTER_BEDROOM)) {
		updateMode(payload);
	} else if (strTopic.equals(DESIRED_TEMP_MASTER_BEDROOM_01)) {
		updateDesiredTemperature(atof(payload));
	} else if (strTopic.equals(RAD_MASTER_BEDROOM)) {
		mqttUpdateOutputControl(radiatorOne, payload);
	} else {
		MqttUtil::publish("DEBUG", "No matching rules found");
	}
}
