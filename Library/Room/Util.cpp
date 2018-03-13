/*
 * Util.cpp
 *
 *  Created on: Jan 5, 2018
 *      Author: theater
 */

#include <Util.h>
#include <Config.h>

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
	Serial.println("Found " + String(count) + (count == 1 ? " device" : " devices"));
	for (int i = 0; i < count; i++) {
		DeviceAddress deviceAddress;
		bool found = owSensors->getAddress(deviceAddress, i);
		if (found) {
			Serial.print("Found device with address: ");
			for (int j = 0; j < 8; j++) {
				Serial.print("0x"+String(deviceAddress[j], HEX)+", ");
			}
			Serial.println();
		}
	}
}
