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
		short pinId;
		bool pinStatus;
	public:
		OutputControl();
		OutputControl(short pinId, bool pinStatus);
		bool outputIsOn();
		const char * getPinStatusToStr();
		virtual ~OutputControl();

		short getPinId() const {
			return pinId;
		}

		void setPinId(short pinId) {
			this->pinId = pinId;
		}

		bool getPinStatus() const {
			return pinStatus;
		}

		void setPinStatus(bool pinStatus) {
			this->pinStatus = pinStatus;
			if (digitalRead(pinId) != pinStatus) {
				digitalWrite(pinId, pinStatus);
			}
		}
};

#endif /* MODEL_OUTPUTCONTROL_H_ */
