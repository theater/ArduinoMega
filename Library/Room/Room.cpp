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
	this->sensors = new Sensor*[3];
	for (int i = 0; i < 3; i++) {
		sensors[i] = NULL;
	}
	this->outputs = new OutputControl*[3];
	for (int i = 0; i < 3; i++) {
		sensors[i] = NULL;
	}

	setMode(AUTO);
	desiredTemperature = DEFAULT_DESIRED_TEMP;
	decisionHeat = false;
	decisionCool = false;

	desiredHumidity = DEFAULT_DESIRED_HUMIDITY;
	decisionFan = false;

	hasHeatingControl = false;		//default: no control in base class
	hasCoolingControl = false;		//default: no control in base class
	hasVentControl = false;			//default: no control in base class
	hasMotionControl = false;			//default: no control in base class
	hasLightControl = false;			//default: no control in base class

}

Room::~Room() {

}

Sensor* Room::addSensor(Sensor* sensor) {
	for (int i = 0; i < (sizeof(sensors) / sizeof(sensors[0])); i++) {
		if(sensors[i] == NULL) {
			sensors[i] = sensor;
			return sensor;
		}
	}
	return NULL;
}

void Room::updateItems(const char* id, const char* value) {
	for (int i = 0; i < (sizeof(sensors) / sizeof(sensors[0])); i++) {
		if (sensors[i] != NULL) {
			sensors[i]->setValue(id, value);
		}
	}

	for (int i = 0; i < (sizeof(outputs) / sizeof(outputs[0])); i++) {
		if (outputs[i] != NULL) {
			outputs[i]->setValue(id, value);
		}
	}
}

Sensor* Room::createSensor(ControlType type, char* topic, boolean directlyAttached) {
	switch (type) {
		case TEMPERATURE: {
			return new TemperatureSensor(type, topic, directlyAttached);
		}
		case HUMIDITY: {
			return new HumiditySensor(type, topic, directlyAttached);
		}
		case MOTION: {
			return new MotionSensor(type, topic, directlyAttached);
		}
	}
	return NULL;
}
void Room::updateDecisionMakers() {
	ventDecisionMaker();
	heatingDecisionMaker();
	coolingDecisionMaker();

	updateOutputControllers();
}

// 	Decision maker for humidity control - if there is humidity control do logic, else decision is always false
bool Room::ventDecisionMaker() {
	if (getMode() == ALL_OFF) {
		setDecisionVent(false);
		return false;
	}
	if (humSensor != NULL) {
		float sensorValue = this->humSensor->getValue();
		if (desiredHumidity + FAN_HIGH_SPEED_TRESHOLD <= sensorValue) {
			setDecisionVent(ON);
			setFanSpeed(FAST);
		} else if (desiredHumidity <= sensorValue - FAN_DEVIATION_TRESHOLD) {
			setDecisionVent(ON);
			setFanSpeed(SLOW);
		} else if (desiredHumidity >= sensorValue + FAN_DEVIATION_TRESHOLD) {
			setDecisionVent(OFF);
			setFanSpeed(SLOW);
		}
		if (DEBUG) {
			MqttUtil::publish("DEBUG", "Room::humDecisionMaker()");
			if (decisionFan) {
				MqttUtil::publish("DEBUG", "Decision vent = TRUE");
			} else {
				MqttUtil::publish("DEBUG", "Decision vent = FALSE");
			}
		}
		return this->decisionFan;
	}
	return false;
}

// 	Decision maker for temperature control - if there is humidity control do logic, else decision is always false
bool Room::heatingDecisionMaker() {
	if (getMode() == ALL_OFF) {
		setDecisionHeat(false);
		return false;
	}
	if (tempSensor != NULL) {
		float sensorValue = tempSensor->getValue();
		if (hasHeatingControl) {
			if (desiredTemperature >= sensorValue + HEATER_TRESHOLD_DEVIATION) {
				setDecisionHeat(true);
			} else if (desiredTemperature <= sensorValue - HEATER_TRESHOLD_DEVIATION) {
				setDecisionHeat(false);
			}
		}
//		if (DEBUG) {
//			MqttUtil::publish("DEBUG", "Room::tempDecisionMaker()");
//			if(decisionHeat) {
//				MqttUtil::publish("DEBUG", "Decision heat = TRUE");
//			} else {
//				MqttUtil::publish("DEBUG", "Decision heat = FALSE");
//			}
//		}
		return decisionHeat;
	}
	return false;
}

bool Room::coolingDecisionMaker() {
	if (getMode() == ALL_OFF) {
		setDecisionCool(false);
		return false;
	}
	if (tempSensor != NULL) {
		float sensorValue = tempSensor->getValue();
		if (hasCoolingControl) {
			if (desiredTemperature <= sensorValue - HEATER_TRESHOLD_DEVIATION) {
				setDecisionCool(true);
			} else if (desiredTemperature >= sensorValue + HEATER_TRESHOLD_DEVIATION) {
				setDecisionCool(false);
			}
		}
		if (DEBUG) {
			MqttUtil::publish("DEBUG", "Room::coolingDecisionMaker()");
		}
		return decisionCool;
	}
	return false;
}

void Room::updateSensors(short tempSensorValue, short humSensorValue) {
	updateTempSensor(tempSensorValue);
	updateHumSensor(humSensorValue);
}

void Room::updateTempSensor(float tempSensorValue) {
	if (tempSensor != NULL) {
//		tempSensor->setValue(tempSensorValue);
		heatingDecisionMaker();
		coolingDecisionMaker();

		tempSensor->sensorToMqttData();

	} else {
		MqttUtil::publish("DEBUG", "TempSensor = NULL");
	}
	if (getMode() != MANUAL) {
		updateOutputControllers();
	}
}

void Room::updateHumSensor(short humSensorValue) {
	if (humSensor != NULL) {
//		humSensor->setValue(humSensorValue);
		ventDecisionMaker();

		humSensor->sensorToMqttData();

		if (DEBUG) {
			MqttUtil::publish("DEBUG", "void Room::updateHumSensor");
		}
	} else {
		MqttUtil::publish("DEBUG", "HumSensor = NULL");
	}
	if (getMode() != MANUAL) {
		updateOutputControllers();
	}
}

void Room::updateMotionSensor(bool motionSensorValue) {
	if (motionSensor != NULL) {
		motionSensor->setValue(motionSensorValue);
		motionSensor->sensorToMqttData();
	}
	if(getMode() != MANUAL) {
		updateOutputControllers();
	}
}

void Room::updateDesiredValues(short desiredTemperature, short desiredHumidity) {
	updateDesiredTemperature(desiredTemperature);
	updateDesiredHumidity(desiredHumidity);
}

void Room::updateDesiredTemperature(float desiredTemperature) {
	this->desiredTemperature = desiredTemperature;
	if (DEBUG) {
//		Serial.println("Desired temperature.");
		MqttUtil::publish("DEBUG", "void Room::updateDesiredTemperature");
	}
	heatingDecisionMaker();
	coolingDecisionMaker();
	if (getMode() != MANUAL) {
		updateOutputControllers();
	}
}

void Room::updateDesiredHumidity(short desiredHumidity) {
	this->desiredHumidity = desiredHumidity;
	if (DEBUG) {
//		Serial.println("Desired humidity.");
		MqttUtil::publish("DEBUG", "void Room::updateDesiredHumidity");
	}
	ventDecisionMaker();
	if (getMode() != MANUAL) {
		updateOutputControllers();
	}
}

void Room::updateMode(const char* mode) {
	if (!strcmp(mode, "ALL_OFF")) {
		setMode(ALL_OFF);
	} else if (!strcmp(mode, "MANUAL")) {
		setMode(MANUAL);
		return;
	} else {
		setMode(AUTO);
	}
	updateDecisionMakers();
}

bool Room::containsTopic(const char * topic) {
	for (int i = 0; i < len; i++) {
		if (!strcmp(mqttTopics[i], topic)) {
			return true;
		}
	}
	return false;
}

void Room::subscribeMqttTopics() {
	char** topics = getMqttTopics();
	int len = getLen();
	for (int i = 0; i < len; i++) {
		logDebug("MQTT Subscribing to topic: " + String(topics[i]));
		MqttUtil::subscribe(topics[i]);
	}
}

void Room::mqttUpdateSensors(const char* topic, const char* value) {
	if(tempSensor != NULL) {
		tempSensor->mqttToSensor(topic, value);
	}
	if(humSensor != NULL) {
		humSensor->mqttToSensor(topic, value);
	}
	if(motionSensor != NULL) {
		motionSensor->mqttToSensor(topic, value);
	}
	updateDecisionMakers();
}

void Room::mqttUpdateOutputControl(OutputControl* outputControl, const char* payload) {
	if (!strcmp(payload, "ON")) {
		outputControl->setPin(ON);
	} else {
		outputControl->setPin(OFF);
	}
}

void Room::updateOutputControllers() {
//	if (getHasHeatingControl() && getDecisionHeat()) {
//		heatOutputs(ON);
//	} else {
//		heatOutputs(OFF);
//	}
//	if(getHasCoolingControl() && getDecisionCool()) { //
//		chillOutputs(ON);
//	} else {
//		chillOutputs(OFF);
//	}
//	if(getHasVentControl() && getDecisionVent()) {
//		humidityControl(ON, fanSpeed);
//	} else {
//		humidityControl(OFF, fanSpeed);
//	}
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
	return decisionFan;
}

void Room::setDecisionVent(bool decisionVent) {
	this->decisionFan = decisionVent;
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

void Room::setHasFanControl(bool hasVentControl) {
	this->hasVentControl = hasVentControl;
}

const char** Room::getMqttTopics() const {
	return mqttTopics;
}

void Room::setMqttTopics(const char** mqttTopics) {
	this->mqttTopics = mqttTopics;
}

int Room::getLen() const {
	return len;
}

void Room::setLen(int len) {
	this->len = len;
}

Mode Room::getMode() const {
	return mode;
}

void Room::setMode(Mode mode) {
	this->mode = mode;
}

RoomId Room::getId() const {
	return id;
}

void Room::setId(RoomId id) {
	this->id = id;
}

bool Room::getFanSpeed() {
	return fanSpeed;
}

void Room::setFanSpeed(bool fanSpeed) {
	this->fanSpeed = fanSpeed;
}

