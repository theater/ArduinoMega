/*
 * TemperatureSensor.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(ControlType type, PubSubClient* mqttClient, char* topic) : Sensor(TEMPERATURE, mqttClient, topic) {
}

TemperatureSensor::~TemperatureSensor() {
}

void TemperatureSensor::sensorToMqttData(PubSubClient* mqttClient) {
		char sensorCharValue[10];
		dtostrf(this->getValue(), 5, 2, sensorCharValue);
		char* topic = this->getTopic();
		mqttClient->publish(topic, sensorCharValue);
		if (Debug()) {
			mqttClient->publish("DEBUG", "void TemperatureSensor::sensorToMqttData");
		}
}
