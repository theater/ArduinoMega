/*
 * BedroomBath.cpp
 *
 *  Created on: 27.06.2016 ã.
 *      Author: theater
 */

#include "BedroomBath.h"

BedroomBath::BedroomBath() : Room(id){
		if(DEBUG) {
			MqttUtil::publish("DEBUG","BigBathroom::BigBathroom");
		}

		// initialize and create Output controllers
		radiatorOne = new OutputControl(BEDROOM_BATH_RAD, OFF, RAD_BEDROOM_BATH_CB);
		setHasHeatingControl(true);

//		fan = new OutputControl(BEDROOM_FAN_SWITCH, OFF, FAN_BEDROOM_BATH_CB, mqttClient);
		fan = new Fan(DUAL_SPEED, BEDROOM_FAN_SWITCH, OFF, FAN_SWITCH_BEDROOM_BATH_CB,
					  BEDROOM_FAN_SPEED, OFF, FAN_SPEED_BEDROOM_BATH_CB);
		setHasFanControl(DUAL_SPEED);

		// initialize and create sensors
		Sensor* tempSensor = createSensor(TEMPERATURE, SENSOR_BEDROOM_BATH_01, true);
		sensors[0] = tempSensor;
		Sensor* humSensor = createSensor(HUMIDITY, SENSOR_BEDROOM_BATH_02, true);
		sensors[1] = humSensor;

		// Set MQTT topics to listen to...
		setMqttTopics(topics);
		setLen(length);

		subscribeMqttTopics();
}

// Virtual functions - defined here the outputs associated with specific services (heat, chill, humidity)
void BedroomBath::heatOutputs(bool state) {
	radiatorOne->setPin(state);
}

void BedroomBath::humidityControl(bool state, bool fanSpeed) {
	fan->fanControl(state, fanSpeed);
}

void BedroomBath::mqttReceive(const char* topic, const char* payload) {
	logInfo("Received message on topic:" + String(topic) + ", payload:" + String(payload));
	String strTopic = String(topic);
	String strPayload = String(payload);
	if (strTopic.equals(MODE_BEDROOM_BATH)) {
		updateMode(payload);
	} else if (strTopic.equals(DESIRED_TEMP_BEDROOM_BATH_01)) {
		updateDesiredTemperature(atof(payload));
	} else if (strTopic.equals(DESIRED_HUM_BEDROOM_BATH_01)) {
		updateDesiredHumidity(atof(payload));
	} else if (strTopic.equals(RAD_BEDROOM_BATH)) {
		mqttUpdateOutputControl(radiatorOne, payload);
	} else if (strTopic.equals(FAN_SWITCH_BEDROOM_BATH)) {
		mqttUpdateOutputControl(fan->getFanSwitch(), payload);
	} else if (strTopic.equals(FAN_SPEED_BEDROOM_BATH)) {
		mqttUpdateOutputControl(fan->getFanSpeedControl(), payload);
	} else {
		MqttUtil::publish("DEBUG", "No matching rules found");
	}
}


BedroomBath::~BedroomBath() {
	delete radiatorOne;
	delete fan;
	delete getTempSensor();
	delete getHumSensor();
}
