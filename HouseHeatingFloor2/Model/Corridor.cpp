/*
 * Corridor.cpp
 *
 *  Created on: 26.06.2016 ã.
 *      Author: theater
 */

#include "Corridor.h"

Corridor::Corridor(PubSubClient* mqttClient) : Room(id, mqttClient){
		if(DEBUG) {
			mqttClient->publish("DEBUG","Corridor::Corridor");
		}

		// initialize and create Output controllers
		radiatorOne = new OutputControl(CORRIDOR_RAD_ONE, OFF, RAD_CORRIDOR_01_CB, mqttClient);
		radiatorTwo = new OutputControl(CORRIDOR_RAD_TWO, OFF, RAD_CORRIDOR_02_CB, mqttClient);
		setHasHeatingControl(true);
		// initialize and create sensors
		Sensor* tempSensor = createSensor(TEMPERATURE, mqttClient, SENSOR_CORRIDOR_01, true);
		setTempSensor((TemperatureSensor*)tempSensor);

		// Set MQTT topics to listen to...
		setMqttTopics(topics);
		setLen(length);

		subscribeMqttTopics(mqttClient);
}

Corridor::~Corridor() {
	delete radiatorOne;
	delete radiatorTwo;
	delete getTempSensor();
}

// Virtual functions - defined here the outputs associated with specific services (heat, chill, humidity)
void Corridor::heatOutputs(bool state) {
	radiatorOne->setPin(state);
	radiatorTwo->setPin(state);
}

void Corridor::mqttReceive(const char* topic, const char* payload) {
	String strTopic = String(topic);
	String strPayload = String(payload);
	if (strTopic.equals(MODE_CORRIDOR)) {
		updateMode(payload);
	} else if (strTopic.equals(DESIRED_TEMP_CORRIDOR_01)) {
		updateDesiredTemperature(atof(payload));
	} else if (strTopic.equals(RAD_CORRIDOR_01)) {
		mqttUpdateOutputControl(radiatorOne, payload);
	} else if (strTopic.equals(RAD_CORRIDOR_02)) {
		mqttUpdateOutputControl(radiatorTwo, payload);
	} else {
		getMqttClient()->publish("DEBUG", "No matching rules found");
	}
}
