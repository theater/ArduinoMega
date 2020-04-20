// Do not remove the include below

#include "EmsHandler.h"

long timerCounter = 0;

EmsHandler *handler;
//The setup function is called once at startup of the sketch
void setup() {
	handler = new EmsHandler();
}

// The loop function is called in an endless loop
void loop() {
	handler->loop();
	if (millis() - timerCounter > INTERVAL) {
		timerCounter = millis();
		nefitSerial.print("Incoming water temperature = ");nefitSerial.println(handler->getIncomingWaterTemperature());
		nefitSerial.print("Outgoing water temperature = ");nefitSerial.println(handler->getOutgoingWaterTemperature());
		nefitSerial.print("Hot water temperature = ");nefitSerial.println(handler->getHotWaterTemperature());
		nefitSerial.print("Water pressure = ");nefitSerial.println(handler->getWaterPressure());
	}
}
