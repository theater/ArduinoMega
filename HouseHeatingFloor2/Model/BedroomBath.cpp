/*
 * BedroomBath.cpp
 *
 *  Created on: 27.06.2016 ã.
 *      Author: theater
 */

#include "BedroomBath.h"

BedroomBath::BedroomBath(PubSubClient* mqttClient, bool DEBUG) : Room(id, mqttClient){
	setDebug(DEBUG);
		if(Debug()) {
			mqttClient->publish("DEBUG","BigBathroom::BigBathroom");
		}

		// initialize and create Output controllers
		radiatorOne = new OutputControl(BEDROOM_BATH_RAD, OFF, RAD_BEDROOM_BATH_CB, mqttClient);
		setHasHeatingControl(true);

		fan = new OutputControl(BEDROOM_FAN, OFF, FAN_BEDROOM_BATH_CB, mqttClient);
		setHasVentControl(true);

		// initialize and create sensors
		Sensor* tempSensor = createSensor(TEMPERATURE, mqttClient, SENSOR_BEDROOM_BATH_01);
		setTempSensor((TemperatureSensor*)tempSensor);
		Sensor* humSensor = createSensor(HUMIDITY, mqttClient, SENSOR_BEDROOM_BATH_02);
		setHumSensor((HumiditySensor*)humSensor);

		// Set MQTT topics to listen to...
		setMqttTopics(topics);
		setLen(length);

		subscribeMqttTopics(mqttClient);
}

BedroomBath::~BedroomBath() {
	delete radiatorOne;
}

// Virtual functions - defined here the outputs associated with specific services (heat, chill, humidity)
void BedroomBath::heatOutputs(bool state) {
	radiatorOne->setPin(state);
}

void BedroomBath::humidityOutputs(bool state) {
	fan->setPin(state);
}

void BedroomBath::mqttReceive(const char* topic, const char* payload) {
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
	} else if (strTopic.equals(FAN_BEDROOM_BATH)) {
		mqttUpdateOutputControl(fan, payload);
	} else {
		getMqttClient()->publish("DEBUG", "No matching rules found");
	}
}
