/*
 * OutputControl.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef MODEL_OUTPUTCONTROL_H_
#define MODEL_OUTPUTCONTROL_H_

#include <Arduino.h>
#include <stdbool.h>

class OutputControl {
	private:
		short pinId;bool pinStatus;
	public:
		OutputControl();
		OutputControl(short pinId, bool pinStatus);bool outputIsOn();
		const char * getPinStatusToStr();
		virtual ~OutputControl();
		short getPinId() const;
		void setPinId(short pinId);bool getPinStatus() const;
		void setPin(bool pinStatus);
};

#endif /* MODEL_OUTPUTCONTROL_H_ */
