/*
 * Room.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include "Room.h"
#include "../Config/Config.h"

Room::Room() {
	desiredTemperature = DEFAULT_DESIRED_TEMP;
	desiredHumidity = DEFAULT_DESIRED_HUMIDITY;
//	decisionTimer.every(REOCCURRENCE,Room::decisionMaker);
}

void Room::decisionMaker() {

}

Room::~Room() {
}

