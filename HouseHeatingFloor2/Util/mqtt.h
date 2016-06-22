/*
 * mqtt.h
 *
 *  Created on: 12.06.2016 ã.
 *      Author: theater
 */

#ifndef UTIL_MQTT_H_
#define UTIL_MQTT_H_

#include <Arduino.h>
#include <stdbool.h>
#include <PubSubClient.h>

#include "../Model/HeatingAdapter.h"


bool mqttConnect(PubSubClient* const mqttClient, HeatingAdapter* const inputAdapter);
void mqttSubscribe(PubSubClient* mqttClient, HeatingAdapter* const inputAdapter);
void mqttPublish(PubSubClient* mqttClient, const char* topic, const char* value);
void mqttCallback(char* topic, byte* payload, unsigned int length);
void mqttSendUpdatedData(char* topic, char* payload);

#endif /* UTIL_MQTT_H_ */
