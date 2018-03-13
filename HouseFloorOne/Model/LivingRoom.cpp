/*
 * LivingRoom.cpp
 *
 *  Created on: Mar 3, 2018
 *      Author: theater
 */

#include "LivingRoom.h"

#include <Util.h>

LivingRoom::LivingRoom(RoomId id) : Room(id) {
}

LivingRoom::~LivingRoom() {
}

void LivingRoom::mqttReceive(const char* topic, const char* payload) {

}
