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
}

BedRoomKids::~BedRoomKids() {
	delete kidsRadiatorOne;
	delete kidsRadiatorTwo;
}

void BedRoomKids::setOutputControllers() {
	if (getDecisionHeating()) {
		kidsRadiatorOne->setPin(OFF);
		kidsRadiatorTwo->setPin(OFF);
	} else {
		kidsRadiatorOne->setPin(ON);
		kidsRadiatorTwo->setPin(ON);
	}
}

