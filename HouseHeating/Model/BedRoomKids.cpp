/*
 * BedRoomKids.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include "BedRoomKids.h"

BedRoomKids::BedRoomKids() {
	kidsRadiatorOne = new OutputControl(KIDS_BEDROOM_RAD_ONE, 0);
	kidsRadiatorTwo = new OutputControl(KIDS_BEDROOM_RAD_TWO, 0);
	kidsRoomFan = new OutputControl(BIG_BATH_RAD_ONE, 0);
}

BedRoomKids::~BedRoomKids() {
	delete kidsRadiatorOne;
	delete kidsRadiatorTwo;
	delete kidsRoomFan;
}

void BedRoomKids::updateOutputControllers() {
	//Heating
	if (getDecisionHeating()) {
		kidsRadiatorOne->setPin(ON);
		kidsRadiatorTwo->setPin(ON);
	} else {
		kidsRadiatorOne->setPin(OFF);
		kidsRadiatorTwo->setPin(OFF);
	}
	//Humidity
	if(getDecisionFan()) {
		kidsRoomFan->setPin(ON);
	} else {
		kidsRoomFan->setPin(OFF);
	}
}

