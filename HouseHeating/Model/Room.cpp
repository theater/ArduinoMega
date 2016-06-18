/*
 * Room.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include "Room.h"

#include <HardwareSerial.h>

#include "../Config/Config.h"
#include "Sensor.h"
#include "PubSubClient.h"

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

// 	Decision maker for humidity control - if there is humidity control do logic, else decision is always false
bool Room::humDecisionMaker() {
	float sensorValue = this->humSensor.getValue();
	if (hasHumidityControl) {
		if (desiredHumidity >= sensorValue) {
			this->decisionFan = false;
		} else if (desiredHumidity <= sensorValue - 1) {
			this->decisionFan = true;
		}
	}
	if(DEBUG) {
//		Serial.println("Decision fan:"+decisionFan);
		mqttClient->publish("DEBUG","Room::tempDecisionMaker()");
	}
	return this->decisionFan;
}

// 	Decision maker for temperature control - if there is humidity control do logic, else decision is always false
bool Room::tempDecisionMaker() {
	float sensorValue = tempSensor.getValue();
	if (hasTemperatureControl) {
		if (desiredTemperature >= sensorValue) {
			this->decisionHeating = true;
		} else if (desiredTemperature <= sensorValue - 1) {
			this->decisionHeating = false;
		}
	}
	if(DEBUG) {
//		Serial.println("Decision heating:");
		mqttClient->publish("DEBUG","Room::tempDecisionMaker()");
	}
	return this->decisionHeating;
}

void  Room::updateSensors(short tempSensorValue,short humSensorValue){
	updateTempSensor(tempSensorValue);
	updateHumSensor(humSensorValue);
}

void Room::updateTempSensor(short tempSensorValue) {
	tempSensor.setValue(tempSensorValue);
	if(DEBUG) {
//		Serial.println("Temperature sensor:"+(int)tempSensor.getValue());
		mqttClient->publish("DEBUG","void Room::updateTempSensor");
	}
	tempDecisionMaker();
}

void Room::updateHumSensor(short humSensorValue) {
	humSensor.setValue(humSensorValue);
	if(DEBUG) {
//		Serial.println("Humidity sensor:"+(int)humSensor.getValue());
		mqttClient->publish("DEBUG","void Room::updateHumSensor");
	}
	humDecisionMaker();
}

void Room::updateDesiredValues(short desiredTemperature,short desiredHumidity) {
	updateDesiredTemperature(desiredTemperature);
	updateDesiredHumidity(desiredHumidity);
}

void Room::updateDesiredTemperature(short desiredTemperature) {
	this->desiredTemperature = desiredTemperature;
	if(DEBUG) {
//		Serial.println("Desired temperature.");
		mqttClient->publish("DEBUG","void Room::updateDesiredTemperature");
	}
	tempDecisionMaker();
}

void Room::updateDesiredHumidity(short desiredHumidity) {
	this->desiredHumidity = desiredHumidity;
	if(DEBUG) {
//		Serial.println("Desired humidity.");
		mqttClient->publish("DEBUG","void Room::updateDesiredHumidity");
	}
	humDecisionMaker();
}

short Room::getDesiredHumidity() const {
	return desiredHumidity;
}

void Room::setDesiredHumidity(short desiredHumidity) {
	this->desiredHumidity = desiredHumidity;
}

short Room::getDesiredTemperature() const {
	return desiredTemperature;
}

void Room::setDesiredTemperature(short desiredTemperature) {
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
