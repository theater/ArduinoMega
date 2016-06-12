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
	desiredHumidity = DEFAULT_DESIRED_HUMIDITY;
	decisionHeating = false;
	decisionFan = false;
}

Room::~Room() {
}

bool Room::humDecisionMaker() {
	float sensorValue = this->humSensor.getValue();
	if (desiredHumidity >= sensorValue) {
		return this->decisionFan = false;
	} else if (desiredHumidity <= sensorValue - 1) {
		return this->decisionFan = true;
	}
	return this->decisionFan;
}

bool Room::tempDecisionMaker() {
	float sensorValue = tempSensor.getValue();
	if (desiredTemperature >= sensorValue) {
		return this->decisionHeating = true;
	} else if (desiredTemperature <= sensorValue - 1) {
		return this->decisionHeating = false;
	}
	return this->decisionHeating;

}

void  Room::updateSensors(short tempSensorValue,short humSensorValue){
	tempSensor.setValue(tempSensorValue);
	tempDecisionMaker();

	humSensor.setValue(humSensorValue);
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
