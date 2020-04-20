// Do not remove the include below

#include <Arduino.h>

#include "EmsHandler.h"


long timerCounter = 0;

EmsHandler *handler;
//The setup function is called once at startup of the sketch
void setup() {
	handler = new EmsHandler();
	Serial.begin(SERIAL_BAUD_RATE);
}

// The loop function is called in an endless loop
void loop() {
	handler->loop();
	if (millis() - timerCounter > INTERVAL) {
		timerCounter = millis();
		Serial.print("Incoming water temperature = ");Serial.println(handler->getIncomingWaterTemperature());
		Serial.print("Outgoing water temperature = ");Serial.println(handler->getOutgoingWaterTemperature());
		Serial.print("Hot water temperature = ");Serial.println(handler->getHotWaterTemperature());
		Serial.print("Water pressure = ");Serial.println(handler->getWaterPressure());
	}
}
