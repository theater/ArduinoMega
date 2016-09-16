/*
 * Fan.cpp
 *
 *  Created on: 16.09.2016 ã.
 *      Author: theater
 */

#include <Fan.h>

Fan::Fan(FanControlType fanType, short fanSwitchPinId, bool fanSwitchPinStatus, char * fanSwitchTopicCB,
	 	 	short fanSpeedPinId, bool fanSpeedPinStatus, char * fanSpeedTopicCB,
		PubSubClient* mqttClient, bool DEBUG) {
	this->fanType = fanType;
	fanSwitch = new OutputControl(fanSwitchPinId, fanSwitchPinStatus, fanSwitchTopicCB, mqttClient);
	fanSpeedControl = new OutputControl(fanSpeedPinStatus, fanSpeedPinStatus, fanSpeedTopicCB, mqttClient);
}

Fan::Fan(FanControlType fanType, short fanSwitchPinId, bool fanSwitchPinStatus, char * fanSwitchTopicCB,
		PubSubClient* mqttClient, bool DEBUG) {
	this->fanType = fanType;
	fanSwitch = new OutputControl(fanSwitchPinId, fanSwitchPinStatus, fanSwitchTopicCB, mqttClient);
}

void Fan::FanControl(bool state, bool speed) {
	fanSwitch->setPin(state);
	if(fanType == DUAL_SPEED) {
		fanSpeedControl->setPin(speed);
	}
}

Fan::~Fan() {
	delete fanSpeedControl;
	delete fanSwitch;
}


FanControlType Fan::getFanType() {
	return fanType;
}

void Fan::setFanType(FanControlType fanType) {
	this->fanType = fanType;
}


