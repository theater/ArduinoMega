/*
 * Room.cpp
 *
 *  Created on: 11.06.2016 ã.
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
	decisionHeating = false;

	desiredHumidity = DEFAULT_DESIRED_HUMIDITY;
	decisionFan = false;

	hasTemperatureControl = false;		//default: no control in base class
	hasHumidityControl = false;			//default: no control in base class
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
bool Room::humDecisionMaker() {
	if (humSensor != NULL) {
		float sensorValue = this->humSensor->getValue();
		if (hasHumidityControl) {
			if (desiredHumidity >= sensorValue) {
				this->decisionFan = false;
			} else if (desiredHumidity <= sensorValue - 1) {
				this->decisionFan = true;
			}
		}
		if (DEBUG) {
//		Serial.println("Decision fan:"+decisionFan);
			mqttClient->publish("DEBUG", "Room::humDecisionMaker()");
		}
		return this->decisionFan;
	}
	return false;
}

// 	Decision maker for temperature control - if there is humidity control do logic, else decision is always false
bool Room::tempDecisionMaker() {
	if (tempSensor != NULL) {
		float sensorValue = tempSensor->getValue();
		if (hasTemperatureControl) {
			if (desiredTemperature >= sensorValue+1) {
				this->decisionHeating = true;
			} else if (desiredTemperature <= sensorValue - 1) {
				this->decisionHeating = false;
			}
		}
		if (DEBUG) {
//		Serial.println("Decision heating:");
			mqttClient->publish("DEBUG", "Room::tempDecisionMaker()");
		}
		return this->decisionHeating;
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
		tempDecisionMaker();

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
		humDecisionMaker();
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
	tempDecisionMaker();
	updateOutputControllers();
}

void Room::updateDesiredHumidity(short desiredHumidity) {
	this->desiredHumidity = desiredHumidity;
	if(DEBUG) {
//		Serial.println("Desired humidity.");
		mqttClient->publish("DEBUG","void Room::updateDesiredHumidity");
	}
	humDecisionMaker();
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

bool Room::getDecisionFan() const {
	return decisionFan;
}

void Room::setDecisionFan(bool decisionFan) {
	this->decisionFan = decisionFan;
}

bool Room::getDecisionHeating() const {
	return decisionHeating;
}

void Room::setDecisionHeating(bool decisionHeating) {
	this->decisionHeating = decisionHeating;
}

bool Room::getHasHumidityControl() const {
	return hasHumidityControl;
}

void Room::setHasHumidityControl(bool hasHumidityControl) {
	this->hasHumidityControl = hasHumidityControl;
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

bool Room::getHasTemperatureControl() const {
	return hasTemperatureControl;
}

void Room::setHasTemperatureControl(bool hasTemperatureControl) {
	this->hasTemperatureControl = hasTemperatureControl;
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

