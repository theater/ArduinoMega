/*
 * EmsLibrary.h
 *
 *  Created on: 17.04.2020
 *      Author: polyc
 */

#ifndef EMSHANDLER_H_
#define EMSHANDLER_H_

#include "EmsLibraryConstants.h"
#include "Nefitserial/NefitSerial.h"


class EmsHandler {
private:
	char buffer[32];                		// frame buffer
	int nefitRegister[NEFIT_REG_MAX];	        // index number see above
	byte pollAdress = 0;                            // if not 0, last polling address
	byte nefitRegToVar[NEFIT_REG_MAX];          	// Write to which variable
	unsigned long registerChanged = 0;              // flag if registy changed
	long startTimeBurner = 0;
	long burnerTime = 0;
	long startTimeWW = 0;
	long WWTime = 0;

	long lastTime = 0;

public:
	EmsHandler();
	virtual ~EmsHandler();

	void loop();
	float getOutgoingWaterTemperature();
	float getIncomingWaterTemperature();
	float getWaterPressure();
	float getHotWaterTemperature();

	void print();

private:
	uint8_t nefit_ems_crc(char *buffer, int len);
	boolean crcCheckOK(char *buffer, int len);
	int readBytes(char *buffer);
	void nefitFrame2register(char *buffer, int len);
	void updateEntries(int ptr);
	int getValue(char *buffer, byte offset, byte vartype);
	void printDebugData();
};

#endif /* EMSHANDLER_H_ */
