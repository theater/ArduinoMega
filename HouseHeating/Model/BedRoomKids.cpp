/*
 * BedRoomKids.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include "BedRoomKids.h"

BedRoomKids::BedRoomKids(short outputPinId) {
	kidsOne = new OutputControl(outputPinId,0);
}

BedRoomKids::~BedRoomKids() {
	// TODO Auto-generated destructor stub
}

