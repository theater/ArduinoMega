/*
 * DesiredValue.cpp
 *
 *  Created on: Mar 18, 2018
 *      Author: theater
 */

#include <DesiredSensorValue.h>
#include <MqttUtil.h>

DesiredSensorValue::DesiredSensorValue(ControlType type, char* topic, float initialValue) : UpdateHandler(topic) {
	this->type = type;
	this->callbackTopic = createCallbackTopic(topic);
	this->value = initialValue;
	MqttUtil::subscribe(topic);
}

DesiredSensorValue::~DesiredSensorValue() {
	// TODO Auto-generated destructor stub
}

