/*
 * HumiditySensor.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include "HumiditySensor.h"

HumiditySensor::HumiditySensor(ControlType type, PubSubClient* mqttClient, char* topic) : Sensor(HUMIDITY, mqttClient, topic) {
}

HumiditySensor::~HumiditySensor() {
}

void HumiditySensor::sensorToMqttData(PubSubClient* mqttClient) {
	char sensorCharValue[10];
	dtostrf(this->getValue(), 4, 2, sensorCharValue);
	char* topic = this->getTopic();
	mqttClient->publish(topic, sensorCharValue);
	if (Debug()) {
		mqttClient->publish("DEBUG", "void HumiditySensor::sensorToMqttData");
	}
}
