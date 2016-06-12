/*
 * mqtt.h
 *
 *  Created on: 12.06.2016 ã.
 *      Author: theater
 */

#ifndef UTIL_MQTT_H_
#define UTIL_MQTT_H_

bool mqttConnect (PubSubClient* mqttClient);
void mqttSubscribe(PubSubClient* mqttClient);
void mqttPublish(PubSubClient* mqttClient, const char* topic, const char* value);
void mqttCallback(char* topic, byte* payload, unsigned int length);
void mqttUpdated(String strTopic, String strPayload);

#endif /* UTIL_MQTT_H_ */
