/*
 * Sensor.cpp
 *
 *  Created on: 11.06.2016 �.
 *      Author: theater
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <Sensor.h>
#include <MqttUtil.h>

Sensor::Sensor(ControlType type, char* topic, bool directlyAttached) {
	this->type = type;
	this->topic = topic;
	this->directlyAttached = directlyAttached;
}


Sensor::~Sensor() {
	// TODO Auto-generated destructor stub
}

void Sensor::sensorToMqttData() {
	if (directlyAttached) {

	} else {
		logDebug("void TemperatureSensor::sensorToMqttData / Re-publish from remote sensor not allowed");
		if (DEBUG) {
			MqttUtil::publish("DEBUG", "void TemperatureSensor::sensorToMqttData / Re-publish from remote sensor not allowed");
		}
	}
}

void Sensor::mqttToSensor(const char* topic, const char* value) {
	if (directlyAttached) {

		char sensorCharValue[10];
		dtostrf(this->getValue(), 5, 2, sensorCharValue);
		MqttUtil::publish(this->getTopic(), sensorCharValue);
		logDebug("void TemperatureSensor::sensorToMqttData");
	} else {
		if(!strcmp(this->topic , topic)) {
			this->value = atof(value);
			logDebug("MQTT Updating sensor value: " + String(value));
//			if(DEBUG) {
//			}
		} else {
			logDebug("Sensor::mqttToSensora / No matching topic");
//			if(DEBUG) {
//				MqttUtil::publish("DEBUG", "Sensor::mqttToSensora / No matching topic");
//			}
		}
	}
}

// getters and setters
ControlType Sensor::getType() const {
	return type;
}

void Sensor::setType(ControlType type) {
	this->type = type;
}

float Sensor::getValue() const {
	return value;
}

void Sensor::setValue(const char* topic, float value) {
	if (value > -30 && strcmp(topic, this->getTopic()) == 0) {
		this->value = value;
		char sensorCharValue[10];
		dtostrf(this->getValue(), 5, 2, sensorCharValue);
		MqttUtil::publish(this->getTopic(), sensorCharValue);
	}
	logDebug("void TemperatureSensor::sensorToMqttData");
}

char* Sensor::getTopic() const {
	return topic;
}

void Sensor::setTopic(char* topic) {
	this->topic = topic;
}

