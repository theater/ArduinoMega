/*
 * BigBathroom.cpp
 *
 *  Created on: 26.06.2016 ã.
 *      Author: theater
 */

#include "BigBathroom.h"


BigBathroom::BigBathroom(PubSubClient* mqttClient, bool DEBUG) : Room(id, mqttClient){
	setDebug(DEBUG);
		if(Debug()) {
			mqttClient->publish("DEBUG","BigBathroom::BigBathroom");
		}

		// initialize and create Output controllers
		radiatorOne = new OutputControl(BIG_BATH_RAD_ONE, OFF, RAD_BIGBATH_01_CB, mqttClient);
		radiatorTwo = new OutputControl(BIG_BATH_RAD_TWO, OFF, RAD_BIGBATH_02_CB, mqttClient);
		setHasHeatingControl(true);
		fan = new Fan(DUAL_SPEED, BIG_BATH_FAN_SWITCH, OFF, FAN_SWITCH_BIGBATH_CB,
					  	  	  	  BIG_BATH_FAN_SPEED, SLOW, FAN_SPEED_BIGBATH_CB, mqttClient);
		setHasFanControl(DUAL_SPEED);

		// initialize and create sensors
		Sensor* tempSensor = createSensor(TEMPERATURE, mqttClient, SENSOR_BIGBATH_01, true);
		setTempSensor((TemperatureSensor*)tempSensor);
		Sensor* humSensor = createSensor(HUMIDITY, mqttClient, SENSOR_BIGBATH_02, true);
		setHumSensor((HumiditySensor*)humSensor);

		// Set MQTT topics to listen to...
		setMqttTopics(topics);
		setLen(length);

		subscribeMqttTopics(mqttClient);
}

BigBathroom::~BigBathroom() {
	delete radiatorOne;
	delete radiatorTwo;
	delete fan;
	delete getTempSensor();
	delete getHumSensor();
}

// Virtual functions - defined here the outputs associated with specific services (heat, chill, humidity)
void BigBathroom::heatOutputs(bool state) {
	radiatorOne->setPin(state);
	radiatorTwo->setPin(state);
}

void BigBathroom::humidityControl(bool state, bool fanSpeed) {
	fan->fanControl(state, fanSpeed);
}

void BigBathroom::mqttReceive(const char* topic, const char* payload) {
	String strTopic = String(topic);
	String strPayload = String(payload);
	if (strTopic.equals(MODE_BIGBATH)) {
		updateMode(payload);
	} else if (strTopic.equals(DESIRED_TEMP_BIGBATH_01)) {
		updateDesiredTemperature(atof(payload));
	} else if (strTopic.equals(DESIRED_HUM_BIGBATH_01)) {
		updateDesiredHumidity(atof(payload));
	} else if (strTopic.equals(RAD_BIGBATH_01)) {
		mqttUpdateOutputControl(radiatorOne, payload);
	} else if (strTopic.equals(RAD_BIGBATH_02)) {
		mqttUpdateOutputControl(radiatorTwo, payload);
	} else if (strTopic.equals(FAN_SWITCH_BIGBATH)) {
		mqttUpdateOutputControl(fan->getFanSwitch(), payload);
	} else if (strTopic.equals(FAN_SPEED_BIGBATH)) {
		mqttUpdateOutputControl(fan->getFanSpeedControl(), payload);
	}else if (strTopic.equals(SENSOR_BIGBATH_01) || strTopic.equals(SENSOR_BIGBATH_02)) {
		mqttUpdateSensors(topic, payload);
	} else {
		getMqttClient()->publish("DEBUG", "No matching rules found");
	}
}
