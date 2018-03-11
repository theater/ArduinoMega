/*
 * LivingRoom.h
 *
 *  Created on: Mar 3, 2018
 *      Author: theater
 */

#ifndef MODEL_LIVINGROOM_H_
#define MODEL_LIVINGROOM_H_

#include <Room.h>
#include "../Config/Config.h"

class LivingRoom: public Room {
	private:
//		OutputControl* outputs = new OutputControl[2];
	public:
		LivingRoom(RoomId id);
		virtual ~LivingRoom();
		void mqttReceive(const char* topic, const char* payload);
};

#endif /* MODEL_LIVINGROOM_H_ */
