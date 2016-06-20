/*
 * MotionSensor.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include "MotionSensor.h"

MotionSensor::MotionSensor(ControlType type, PubSubClient* mqttClient, char* topic) : Sensor(MOTION, mqttClient, topic) {

}

MotionSensor::~MotionSensor() {
}

void MotionSensor::sensorToMqttData(PubSubClient* mqttClient) {
	bool sensorValue = this->getValue();
	char* topic = this->getTopic();
	if (sensorValue) {
		mqttClient->publish(topic, "CLOSED");
	} else {
		mqttClient->publish(topic, "OPEN");
	}
	if (Debug()) {
		mqttClient->publish("DEBUG", "void MotionSensor::sensorToMqttData");
	}
}
