/*
 * Sensor.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <Sensor.h>

Sensor::Sensor(ControlType type, PubSubClient* mqttClient, char* topic, bool directlyAttached) {
	this->type = type;
	this->mqttClient = mqttClient;
	this->topic = topic;
	this->directlyAttached = directlyAttached;
}


Sensor::~Sensor() {
	// TODO Auto-generated destructor stub
}

void Sensor::sensorToMqttData(PubSubClient* mqttClient) {
	if (directlyAttached) {
		char sensorCharValue[10];
		dtostrf(this->getValue(), 5, 2, sensorCharValue);
		char* topic = this->getTopic();
		mqttClient->publish(topic, sensorCharValue);
		logDebug("void TemperatureSensor::sensorToMqttData");
		if (DEBUG) {
			mqttClient->publish("DEBUG", "void TemperatureSensor::sensorToMqttData");
		}
	} else {
		logDebug("void TemperatureSensor::sensorToMqttData / Re-publish from remote sensor not allowed");
		if (DEBUG) {
			mqttClient->publish("DEBUG", "void TemperatureSensor::sensorToMqttData / Re-publish from remote sensor not allowed");
		}
	}
}

void Sensor::mqttToSensor(const char* topic, const char* value) {
	if (!directlyAttached) {
		if(!strcmp(this->topic , topic)) {
			this->value = atof(value);
			logDebug("MQTT Updating sensor value: " + String(value));
			if(DEBUG) {
//				mqttClient->publish("DEBUG", ("MQTT Updating sensor value: " + String(value)));
			}
		} else {
			logDebug("Sensor::mqttToSensora / No matching topic");
			if(DEBUG) {
				mqttClient->publish("DEBUG", "Sensor::mqttToSensora / No matching topic");
			}
		}
	}
}

// getters and setters
PubSubClient* Sensor::getMqttClient() const {
	return mqttClient;
}

void Sensor::setMqttClient(PubSubClient* const mqttClient) {
	this->mqttClient = mqttClient;
}

ControlType Sensor::getType() const {
	return type;
}

void Sensor::setType(ControlType type) {
	this->type = type;
}

float Sensor::getValue() const {
	return value;
}

void Sensor::setValue(float value) {
	this->value = value;
}

char* Sensor::getTopic() const {
	return topic;
}

void Sensor::setTopic(char* topic) {
	this->topic = topic;
}

bool Sensor::Debug() const {
	return DEBUG;
}

void Sensor::setDebug(bool debug) {
	DEBUG = debug;
}
