/*
 * BedRoomKids.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include "BedRoomKids.h"

BedRoomKids::BedRoomKids(short outputPinId) {
	kidsRadiatorOne = new OutputControl(KIDS_RAD_ONE, 0);
	kidsRadiatorTwo = new OutputControl(KIDS_RAD_TWO, 0);
}

BedRoomKids::~BedRoomKids() {
	delete kidsRadiatorOne;
	delete kidsRadiatorTwo;
}

