/*
 * Room.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include "Room.h"
#include "../Config/Config.h"

Room::Room() {
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
			return this->decisionFan = false;
		} else if (desiredHumidity <= sensorValue - 1) {
			return this->decisionFan = true;
		}
	}
	return false;
}

// 	Decision maker for temperature control - if there is humidity control do logic, else decision is always false
bool Room::tempDecisionMaker() {
	float sensorValue = tempSensor.getValue();
	if (hasTemperatureControl) {
		if (desiredTemperature >= sensorValue) {
			return this->decisionHeating = true;
		} else if (desiredTemperature <= sensorValue - 1) {
			return this->decisionHeating = false;
		}
	}
	return false;
}

void  Room::updateSensors(short tempSensorValue,short humSensorValue){
	tempSensor.setValue(tempSensorValue);
	tempDecisionMaker();

	humSensor.setValue(humSensorValue);
	humDecisionMaker();
}

void Room::updateDesiredValues(short desiredTemperature,short desiredHumidity) {
	this->desiredTemperature = desiredTemperature;
	tempDecisionMaker();

	this->desiredHumidity = desiredHumidity;
	humDecisionMaker();
}

short Room::getDesiredHumidity() const {
	return desiredHumidity;
}

void Room::setDesiredHumidity(short desiredHumidity) {
	this->desiredHumidity = desiredHumidity;
	humDecisionMaker();
}

short Room::getDesiredTemperature() const {
	return desiredTemperature;
}

void Room::setDesiredTemperature(short desiredTemperature) {
	this->desiredTemperature = desiredTemperature;
	tempDecisionMaker();
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
