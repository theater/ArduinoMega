/*
 * mqtt.cpp
 *
 *  Created on: 12.06.2016 ã.
 *      Author: theater
 */

#include <Config.h>
#include <MqttUtil.h>
#include <PubSubClient.h>
#include <stddef.h>
#include <Util.h>

//MQTT
PubSubClient * MqttUtil::mqttClient = NULL;

void MqttUtil::initializeMqttUtil(PubSubClient * client) {
	MqttUtil::mqttClient = client;
}

bool MqttUtil::connect() {
	if (!mqttClient->connected()) {
		logDebug("MQTT not connected. Attempting to connect");
		if (mqttClient->connect(MQTT_CLIENT_NAME, MQTT_USER, MQTT_PASSWORD)) {
			delay(3000);
			logDebug("Initial mqtt connect attempt SUCCESS !");
			if(isConnected()) {
				publish(MQTT_CLIENT_NAME, MQTT_CLIENT_NAME);
				return true;
			}
		} else {
			logDebug("Initial mqtt connect attempt FAILED !");
			return false;
		}
	} else {
		return true;
	}
}

void MqttUtil::publish(const char* topic, const char* value) {
	if(isConnected()) {
		logDebug("Publishing on topic: " + String(topic) + ", value: " + String(value));
		mqttClient->publish(topic, value);
	} else {
		logDebug("Not connected. Unable to publish on topic " + String(topic));
	}

}



void MqttUtil::subscribe(const char* topic) {
	if(isConnected()) {
		logDebug("Subscribing to topic: " + String(topic));
		mqttClient->subscribe(topic);
	} else {
		logDebug("Not connected. Unable to subscribe for topic: " + String(topic));
	}
}

bool MqttUtil::isConnected() {
	if(mqttClient != NULL) {
		return mqttClient->connected();
	}
	return false;
}

void MqttUtil::loop() {
	mqttClient->loop();
}
