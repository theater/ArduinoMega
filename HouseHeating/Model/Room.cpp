/*
 * Room.cpp
 *
 *  Created on: 11.06.2016 �.
 *      Author: theater
 */

#include "Room.h"

#include <PubSubClient.h>
#include <stdio.h>

#include "../Config/Config.h"
#include "Util.h"

Room::Room(PubSubClient* mqttClient, bool DEBUG) {
	this->mqttClient = mqttClient;
	this->DEBUG = DEBUG;
	desiredTemperature = DEFAULT_DESIRED_TEMP;
	decisionHeat = false;
	decisionCool = false;

	desiredHumidity = DEFAULT_DESIRED_HUMIDITY;
	decisionVent = false;

	hasHeatingControl = false;		//default: no control in base class
	hasCoolingControl = false;		//default: no control in base class
	hasVentControl = false;			//default: no control in base class
	hasMotionControl = false;			//default: no control in base class
	hasLightControl = false;			//default: no control in base class
}

Room::~Room() {
}

Sensor* Room::createSensor(ControlType type, PubSubClient* mqttClient, char* topic) {
	switch (type) {
		case TEMPERATURE: {
			return new TemperatureSensor(type, mqttClient, topic);
		}
		case HUMIDITY: {
			return new HumiditySensor(type, mqttClient, topic);
		}
		case MOTION: {
			return new MotionSensor(type, mqttClient, topic);
		}
	}
	return NULL;
}

// 	Decision maker for humidity control - if there is humidity control do logic, else decision is always false
bool Room::ventDecisionMaker() {
	if (humSensor != NULL) {
		float sensorValue = this->humSensor->getValue();
		if (hasVentControl) {
			if (desiredHumidity >= sensorValue) {
				setDecisionVent(true);
			} else if (desiredHumidity <= sensorValue - 1) {
				setDecisionVent(false);
			}
		}
		if (DEBUG) {
//		Serial.println("Decision fan:"+decisionFan);
			mqttClient->publish("DEBUG", "Room::humDecisionMaker()");
		}
		return this->decisionVent;
	}
	return false;
}

// 	Decision maker for temperature control - if there is humidity control do logic, else decision is always false
bool Room::heatingDecisionMaker() {
	if (tempSensor != NULL) {
		float sensorValue = tempSensor->getValue();
		if (hasHeatingControl) {
			if (desiredTemperature >= sensorValue+1) {
				setDecisionHeat(true);
			} else if (desiredTemperature <= sensorValue - 1) {
				setDecisionHeat(false);
			}
		}
		if (DEBUG) {
//		Serial.println("Decision heating:");
			mqttClient->publish("DEBUG", "Room::tempDecisionMaker()");
		}
		return decisionHeat;
	}
	return false;
}

bool Room::coolingDecisionMaker() {
	if (tempSensor != NULL) {
		float sensorValue = tempSensor->getValue();
		if (hasCoolingControl) {
			if (desiredTemperature < sensorValue-0.5) {
				setDecisionCool(true);
			} else if (desiredTemperature > sensorValue+0.5) {
				setDecisionCool(false);
			}
		}
		if (DEBUG) {
//		Serial.println("Decision heating:");
			mqttClient->publish("DEBUG", "Room::tempDecisionMaker()");
		}
		return decisionCool;
	}
	return false;
}

void  Room::updateSensors(short tempSensorValue,short humSensorValue){
	updateTempSensor(tempSensorValue);
	updateHumSensor(humSensorValue);
}

void Room::updateTempSensor(float tempSensorValue) {
	if (tempSensor != NULL) {
		tempSensor->setValue(tempSensorValue);
		heatingDecisionMaker();
		coolingDecisionMaker();

		char sensorCharValue[10];
		dtostrf(tempSensor->getValue(), 5, 2, sensorCharValue);
		char* topic = tempSensor->getTopic();
		mqttClient->publish(topic, sensorCharValue);

		if (DEBUG) {
			mqttClient->publish("DEBUG", "void Room::updateTempSensor");
		}
	} else {
		mqttClient->publish("DEBUG", "TempSensor = NULL");
	}
	updateOutputControllers();
}

void Room::updateHumSensor(short humSensorValue) {
	if (humSensor != NULL) {
		humSensor->setValue(humSensorValue);
		if (DEBUG) {
			mqttClient->publish("DEBUG", "void Room::updateHumSensor");
		}
		ventDecisionMaker();
	} else {
		mqttClient->publish("DEBUG", "HumSensor = NULL");
	}
	updateOutputControllers();
}

void Room::updateDesiredValues(short desiredTemperature,short desiredHumidity) {
	updateDesiredTemperature(desiredTemperature);
	updateDesiredHumidity(desiredHumidity);
}

void Room::updateDesiredTemperature(float desiredTemperature) {
	this->desiredTemperature = desiredTemperature;
	if(DEBUG) {
//		Serial.println("Desired temperature.");
		mqttClient->publish("DEBUG","void Room::updateDesiredTemperature");
	}
	heatingDecisionMaker();
	coolingDecisionMaker();
	updateOutputControllers();
}

void Room::updateDesiredHumidity(short desiredHumidity) {
	this->desiredHumidity = desiredHumidity;
	if(DEBUG) {
//		Serial.println("Desired humidity.");
		mqttClient->publish("DEBUG","void Room::updateDesiredHumidity");
	}
	ventDecisionMaker();
	updateOutputControllers();
}


// GETTERS / SETTERS
short Room::getDesiredHumidity() const {
	return desiredHumidity;
}

void Room::setDesiredHumidity(short desiredHumidity) {
	this->desiredHumidity = desiredHumidity;
}

float Room::getDesiredTemperature() const {
	return desiredTemperature;
}

void Room::setDesiredTemperature(float desiredTemperature) {
	this->desiredTemperature = desiredTemperature;
}

bool Room::getHasLightControl() const {
	return hasLightControl;
}

void Room::setHasLightControl(bool hasLightControl) {
	this->hasLightControl = hasLightControl;
}

bool Room::getHasMotionControl() const {
	return hasMotionControl;
}

void Room::setHasMotionControl(bool hasMotionControl) {
	this->hasMotionControl = hasMotionControl;
}

PubSubClient* Room::getMqttClient() const {
	return mqttClient;
}

void Room::setMqttClient(PubSubClient* mqttClient) {
	this->mqttClient = mqttClient;
}

bool Room::Debug() {
	return DEBUG;
}

void Room::setDebug(bool debug) {
	DEBUG = debug;
}

HumiditySensor* Room::getHumSensor() {
	return humSensor;
}

void Room::setHumSensor(HumiditySensor* humSensor) {
	this->humSensor = humSensor;
}

MotionSensor* Room::getMotionSensor() {
	return motionSensor;
}

void Room::setMotionSensor(MotionSensor* motionSensor) {
	this->motionSensor = motionSensor;
}

TemperatureSensor* Room::getTempSensor() {
	return tempSensor;
}

void Room::setTempSensor(TemperatureSensor* tempSensor) {
	this->tempSensor = tempSensor;
}

bool Room::getDecisionCool() const {
	return decisionCool;
}

void Room::setDecisionCool(bool decisionCool) {
	this->decisionCool = decisionCool;
}

bool Room::getDecisionHeat() const {
	return decisionHeat;
}

void Room::setDecisionHeat(bool decisionHeat) {
	this->decisionHeat = decisionHeat;
}

bool Room::getDecisionVent() const {
	return decisionVent;
}

void Room::setDecisionVent(bool decisionVent) {
	this->decisionVent = decisionVent;
}

bool Room::getHasCoolingControl() const {
	return hasCoolingControl;
}

void Room::setHasCoolingControl(bool hasCoolingControl) {
	this->hasCoolingControl = hasCoolingControl;
}

bool Room::getHasHeatingControl() const {
	return hasHeatingControl;
}

void Room::setHasHeatingControl(bool hasHeatingControl) {
	this->hasHeatingControl = hasHeatingControl;
}

bool Room::getHasVentControl() const {
	return hasVentControl;
}

void Room::setHasVentControl(bool hasVentControl) {
	this->hasVentControl = hasVentControl;
}

const char** Room::getMqttTopics() const {
	return mqttTopics;
}

void Room::setMqttTopics(const char** mqttTopics) {
	this->mqttTopics = mqttTopics;
}
