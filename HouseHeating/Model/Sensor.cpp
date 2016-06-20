/*
 * Sensor.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include "../Model/Sensor.h"

Sensor::Sensor(ControlType type, PubSubClient* mqttClient, char* topic, bool DEBUG) {
	this->type = type;
	this->mqttClient = mqttClient;
	this->topic = topic;
	this->DEBUG = DEBUG;
}

Sensor::~Sensor() {
	// TODO Auto-generated destructor stub
}

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
