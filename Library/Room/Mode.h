/*
 * Mode.h
 *
 *  Created on: Mar 15, 2018
 *      Author: theater
 */

#ifndef LIBRARIES_ROOM_MODE_H_
#define LIBRARIES_ROOM_MODE_H_

#include <Util.h>

class Mode {
	private:
		char * id;
		char * callbackTopic;
		ModeType mode;

	public:
		Mode(ModeType mode);
		Mode(ModeType mode, char * id);
		virtual ~Mode();

		char* getId();
		ModeType getMode();
		void setMode(ModeType mode);
};

#endif /* LIBRARIES_ROOM_MODE_H_ */
