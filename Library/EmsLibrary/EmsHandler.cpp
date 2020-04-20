/*
 * EmsLibrary.cpp
 *
 *  Created on: 17.04.2020 ?.
 *      Author: polyc
 */

#include "EmsHandler.h"

#include <avr/pgmspace.h>
#include <Print.h>

EmsHandler::EmsHandler() {
	nefitSerial.begin(SERIAL_BAUD_RATE);
	nefitSerial1.begin(9700);

	for (char i = 0; i <= NEFIT_REG_MAX; i++) {
		nefitRegister[i] = 0;
		nefitRegToVar[i] = 0;
	}
	// We might already be intered in some register values, set a trigger
	nefitRegToVar[2] = 1;    // burner on/off
	nefitRegToVar[4] = 2;    // wwvalve on/off

}

EmsHandler::~EmsHandler() {
	nefitSerial1.end();
}

void EmsHandler::updateEntries(int ptr) {
	if (ptr == 2) {
		pollAdress = buffer[0];
	} else if (ptr > 4) {
		if (crcCheckOK(buffer, ptr)) {
			nefitFrame2register(buffer, ptr);
			if (registerChanged > 0) {
				if (bool burner = bitRead(registerChanged, 2)) {
					// if burner-state changed
					if (burner) {
						// burner turns on
						startTimeBurner = millis();
					} else {
						// burner turns off
						burnerTime = burnerTime + millis() - startTimeBurner;
					}
				} else if (bool wwvalve = bitRead(registerChanged, 4)) {
					// wwvalve setting changed
					if (wwvalve) {
						startTimeWW = millis();
					} else {
						// wwvalve off
						WWTime = WWTime + millis() - startTimeWW;
					}
				}

				registerChanged = 0; // clear change flags
			}
		}
	}
}

void EmsHandler::loop() {
	int ptr;
	if (nefitSerial1.available()) {  // check if we need to read
		ptr = readBytes(buffer);
		updateEntries(ptr);
	}

	#if DEBUG
		printDebugData();
	#endif

}

void EmsHandler::printDebugData() {
	if (millis() - lastTime > INTERVAL) {
			lastTime = millis();
			for (int i = 0; i < NEFIT_REG_MAX; i++) {
				nefitSerial.print("nefitRegister[");
				nefitSerial.print(i);
				nefitSerial.print("]: ");
				nefitSerial.println(nefitRegister[i]);
			}
			nefitSerial.println("------------------------");
			nefitSerial.println("NEFIT EMS bus:");

			nefitSerial.print("cv water uitgaand: ");
			nefitSerial.println((float) nefitRegister[0] / 10, 1);

			nefitSerial.print("burner vermogen: ");
			nefitSerial.println((float) nefitRegister[1], 1);

			nefitSerial.print("burner on/off: ");
			nefitSerial.println((float) nefitRegister[2], DEC);   // burner

			nefitSerial.print("cv pump on/off: ");
			nefitSerial.println((float) nefitRegister[3], DEC);   //cv pump

			nefitSerial.print("hot watervraag on/off: ");
			nefitSerial.println((float) nefitRegister[4], DEC);

			nefitSerial.print("keteltemp: ");
			nefitSerial.println((float) nefitRegister[5] / 10, 1);   //keteltemp

			nefitSerial.print("cv return temp: ");
			nefitSerial.println((float) nefitRegister[6] / 10, 1); //waterterug temp

			nefitSerial.print("waterpressure: ");
			nefitSerial.println((float) nefitRegister[7] / 10, 1); // waterpressure

			nefitSerial.print("statuscode: ");
			nefitSerial.print((char) nefitRegister[8]);
			nefitSerial.println((char) nefitRegister[9]);

			nefitSerial.print("hotwater temp: ");
			nefitSerial.println((float) nefitRegister[10] / 10, 1); //hotwatertemp

			nefitSerial.print("boiler verhoting on/off: ");
			nefitSerial.println((float) nefitRegister[11], DEC);

			//nefitSerial.print(",");
			//nefitSerial.print(nefitRegister[14],DEC);           //thermostat 0=low, 1=manual, 2=auto

			nefitSerial.println("END");
			nefitSerial.println("------------------------");
			nefitSerial.println("------------------------");
	}
}

// CRC check
boolean EmsHandler::crcCheckOK(char *buffer, int len) {
	int crc = nefit_ems_crc(buffer, len);
	boolean crcOK = (crc == (uint8_t) buffer[len - 2]);
	return crcOK;
}

// Calculate CRC for buffer
uint8_t EmsHandler::nefit_ems_crc(char *buffer, int len) {
	uint8_t i, crc = 0x0;
	uint8_t d;
	for (i = 0; i < len - 2; i++) {
		d = 0;
		if (crc & 0x80) {
			crc ^= 12;
			d = 1;
		}
		crc = (crc << 1) & 0xfe;
		crc |= d;
		crc ^= buffer[i];
	}
	return crc;
}

// Read one bus frame, return number of read bytes
int EmsHandler::readBytes(char *buffer) {
	int ptr = 0;

//  nefitIO.flush();
	while (nefitSerial1.available()) {
		if ((uint8_t) nefitSerial1.peek() == 0) {
			uint8_t temp = nefitSerial1.read();                   // skip zero's
		} else {
			break;
		}
	}

	while ((!nefitSerial1.frameError()) && ptr < 32) { // read data until frame-error
		if (nefitSerial1.available()) {
			buffer[ptr] = nefitSerial1.read();
			ptr++;
		}
	}
	nefitSerial1.flush();
	return ptr;
}

void EmsHandler::nefitFrame2register(char *buffer, int len) {
	byte sender;
	byte message;
	int registerData;
	uint8_t offset, vartype;
	for (uint8_t i = 0; i < ((NEFIT_REG_MAX) * 4); i = i + 4) {
		sender = pgm_read_byte_near(regNefitCoding + i);
		message = pgm_read_byte_near(regNefitCoding + 1 + i);
		if ((sender <= ((uint8_t) buffer[0]))
				&& (message <= (uint8_t) buffer[2])) {
			offset = pgm_read_byte_near(regNefitCoding + 2 + i);
			if ((sender == ((uint8_t) buffer[0] & 0xF))
					&& (message == (uint8_t) buffer[2])
					&& (offset >= (uint8_t) buffer[3])) {
				offset = offset - (uint8_t) buffer[3] + 4; // rekening houden met lange frames (gesplitst)
				if (offset < len) {
					vartype = pgm_read_byte_near(regNefitCoding + 3 + i);
					registerData = getValue(buffer, offset, vartype);
					if (registerData != nefitRegister[i / 4]) {
						nefitRegister[i / 4] = registerData;
						if (nefitRegToVar[i / 4] > 0) {
							bitSet(registerChanged, i / 4); // alleen wanneer dit een Nodo var is
						}
					}
				}
			}
		} else {
			nefitSerial.println("Entering break");
			break;
		}
	}
	return;
}

int EmsHandler::getValue(char *buffer, byte offset, byte vartype) {
	int result;
	uint8_t type = vartype & 0x0F;
	switch (type) {
	case 0:			//boolean
		result = bitRead(buffer[offset], (vartype & 0x70) >> 4);
		break;
	case 1:			//byte
//			result = (uint8_t)buffer[offset];
//			break;
	case 2:			//ascii
//			result = (uint8_t)buffer[offset];
//                        break;
	case 4:			//byte x 2
//			result = (uint8_t)buffer[offset];
//			break;
	case 6:			//byte x 10
		result = (uint8_t) buffer[offset];
		break;
	case 3:			//int
//			result = getDoubleByte(buffer,offset);
//			break;
	case 5:			//int x 10
		result = buffer[offset] << 8;
		result = result + (uint8_t) buffer[offset + 1];
		break;

	}
	return result;
}

float EmsHandler::getOutgoingWaterTemperature() {
	return (float) nefitRegister[0] / 10;
}

float EmsHandler::getIncomingWaterTemperature() {
	return (float) nefitRegister[6] / 10;
}

float EmsHandler::getWaterPressure() {
	return (float) nefitRegister[7] / 10;
}

float EmsHandler::getHotWaterTemperature() {
	return (float) nefitRegister[10] / 10;
}
