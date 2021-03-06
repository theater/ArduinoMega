/*
 * Util.cpp
 *
 *  Created on: Jan 5, 2018
 *      Author: theater
 */

#include <HardwareSerial.h>
#include <Print.h>
#include <Util.h>

#include "Config.h"
#include "MqttUtil.h"


void log(String severity, String data) {
	Serial.println(severity +": " + data);
}

void logInfo(String data) {
	log("INFO", data);
}

void logDebug(String data) {
	if(DEBUG) {
		log("DEBUG", data);
	}
}

void logError(String data) {
	log("ERROR", data);
}

void printOneWireAddresses(DallasTemperature* owSensors) {
	int count = owSensors->getDeviceCount();
	logDebug("Found " + String(count) + (count == 1 ? " device" : " devices"));
	for (int i = 0; i < count; i++) {
		DeviceAddress deviceAddress;
		bool found = owSensors->getAddress(deviceAddress, i);
		if (found) {
			String strAddress = String(i) +": ";
			for (int j = 0; j < 8; j++) {
				strAddress += "0x" + String(deviceAddress[j], HEX) + ", ";
			}
			logDebug("Found device with address: " + strAddress);

			const char * address = strAddress.c_str();
			MqttUtil::publish(ONE_WIRE_ADDRESSES_TOPIC, address);
		}
	}
}

char* createCallbackTopic(char* topic) {
	// Construct callback topic by creating same string + cb at the end:
	int size = strlen(topic) + 4;
	char* callbackTopic = new char[size];
	strcpy(callbackTopic, topic);
	logDebug("Set topic to :" + String(topic));
	strcat(callbackTopic, "cb");
	logDebug("Callback topic is :" + String(callbackTopic));
	return callbackTopic;
}

// returns free heap size. Taken from internet.
int freeMemory() {
	char top;
#ifdef __arm__
	return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
	return &top - __brkval;
#else  // __arm__
	return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif  // __arm__
}
