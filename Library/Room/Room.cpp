/*
 * Room.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include <Arduino.h>
#include "Room.h"
#include <string.h>
#include <WString.h>


Room::Room(RoomId id) {
	this->id = id;

	// TODO UGLY creation of arrays - think of better approach later !
	//	(maybe develop dynamic List or ArrayList) Memory fragmentation could be an issue though...
	this->sensors = new Sensor*[arraySize];
	for (int i = 0; i < arraySize; i++) {
		sensors[i] = NULL;
	}

	this->desiredValues = new DesiredSensorValue*[arraySize];
	for (int i = 0; i < arraySize; i++) {
		desiredValues[i] = NULL;
	}

	this->outputs = new OutputControl*[arraySize];
	for (int i = 0; i < arraySize; i++) {
		sensors[i] = NULL;
	}

	mode = new Mode(AUTO);
}

Room::~Room() {

}

Sensor* Room::addSensor(Sensor* sensor) {
	String sensorId = String(sensor->getId());
	for (int i = 0; i < 3; i++) {
		if(sensors[i] == NULL) {
			sensors[i] = sensor;
			logDebug("Added sensor with topic " + sensorId);
			return sensor;
		} else if (i == 2) {
			logDebug("Not enough space in sensors array. Unable to add sensor " + sensorId);
		}
	}
	return NULL;
}

void Room::addDesiredValue(DesiredSensorValue * desiredValue) {
	for (int i = 0; i < (sizeof(desiredValues) / sizeof(desiredValues[0])); i++) {
		if (desiredValues[i] == NULL) {
			desiredValues[i] = desiredValue;
		}
	}
}

void Room::updateItems(const char* id, const char* value) {
	updateSensors(id, value);
	updateDesiredValues(id, value);
	updateMode(id, value);
	updateDecisionMakers();
}

// TODO think how to generalize these
void Room::updateSensors(const char* id, const char* value) {
	for (unsigned int i = 0; i < 3; i++) {
			if (sensors[i] != NULL) {
				sensors[i]->updateValue(id, value);
			}
		}
}

void Room::updateDesiredValues(const char* id, const char* value) {
	for (unsigned int i = 0; i < (sizeof(desiredValues) / sizeof(desiredValues[0])); i++) {
			if (desiredValues[i] != NULL) {
				desiredValues[i]->updateValue(id, value);
			}
		}
}

void Room::updateDecisionMakers() {

	ventDecisionMaker();
	heatingDecisionMaker();

//	updateOutputControllers();
}

// 	Decision maker for humidity control - if there is humidity control do logic, else decision is always false
bool Room::ventDecisionMaker() {
	if (getMode() == ALL_OFF) {
//		setDecisionVent(false);
		return false;
	}
//	if (humSensor != NULL) {
//		float sensorValue = this->humSensor->getValue();
//		if (desiredHumidity + FAN_HIGH_SPEED_TRESHOLD <= sensorValue) {
//			setDecisionVent(ON);
//			setFanSpeed(FAST);
//		} else if (desiredHumidity <= sensorValue - FAN_DEVIATION_TRESHOLD) {
//			setDecisionVent(ON);
//			setFanSpeed(SLOW);
//		} else if (desiredHumidity >= sensorValue + FAN_DEVIATION_TRESHOLD) {
//			setDecisionVent(OFF);
//			setFanSpeed(SLOW);
//		}
//		if (DEBUG) {
//			MqttUtil::publish("DEBUG", "Room::humDecisionMaker()");
//			if (decisionFan) {
//				MqttUtil::publish("DEBUG", "Decision vent = TRUE");
//			} else {
//				MqttUtil::publish("DEBUG", "Decision vent = FALSE");
//			}
//		}
//		return this->decisionFan;
//	}
	return false;
}

// 	Decision maker for temperature control - if there is humidity control do logic, else decision is always false
bool Room::heatingDecisionMaker() {
	if (getMode() == ALL_OFF) {
//		setDecisionHeat(false);
		return false;
	}
//	if (tempSensor != NULL) {
//		float sensorValue = tempSensor->getValue();
//		if (hasHeatingControl) {
//			if (desiredTemperature >= sensorValue + HEATER_TRESHOLD_DEVIATION) {
//				setDecisionHeat(true);
//			} else if (desiredTemperature <= sensorValue - HEATER_TRESHOLD_DEVIATION) {
//				setDecisionHeat(false);
//			}
//		}
//		if (DEBUG) {
//			MqttUtil::publish("DEBUG", "Room::tempDecisionMaker()");
//			if(decisionHeat) {
//				MqttUtil::publish("DEBUG", "Decision heat = TRUE");
//			} else {
//				MqttUtil::publish("DEBUG", "Decision heat = FALSE");
//			}
//		}
//		return decisionHeat;
//	}
	return false;
}


void Room::updateMode(const char* id, const char* value) {
	mode->updateValue(id, value);
	updateDecisionMakers();
}

RoomId Room::getId() const {
	return id;
}

void Room::setId(RoomId id) {
	this->id = id;
}

ModeType Room::getMode() const {
	return mode->getMode();
}

void Room::setMode(ModeType modeType) {
	this->mode->setMode(modeType);
}

void Room::createMode(Mode* mode) {
	this->mode = mode;
}

