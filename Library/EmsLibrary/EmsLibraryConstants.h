#include <Arduino.h>

#define NEFIT_REG_MAX	17

#define DEBUG 0

#define SERIAL_BAUD_RATE 115200

const long INTERVAL = 10000;

PROGMEM const unsigned char regNefitCoding[] = {

// 0x18 UBAMonitorFast (boiler status high frequency report)
		0x08, 0x18, 0x01, 0x05,	//#1   0 temperature water out (uitgaand) x 10
		0x08, 0x18, 0x04, 0x01,				//#2   1 burner power
		0x08, 0x18, 0x07, 0x00,				//#3   2 burner on/off
		0x08, 0x18, 0x07, 0x50,			//#4   3 heating pump on/off
		0x08, 0x18, 0x07, 0x60,		//#5   4 tap water heating on/off
		0x08, 0x18, 0x0B, 0x05,			//#6   5 boiler temperature x 10
		0x08, 0x18, 0x0D, 0x05,	//#7   6 temperature water in (cv return) x 10
		0x08, 0x18, 0x11, 0x06,			//#8   7 water pressure x 10
		0x08, 0x18, 0x12, 0x02,			//#9   8 status code 1st letter
		0x08, 0x18, 0x13, 0x02,			//#10  9 status code 2nd letter
// 0x34 UBAMonitorWWMessage (hot water status report)
		0x08, 0x34, 0x01, 0x05,		//#11 10 tap water temperature x 10
		0x08, 0x34, 0x05, 0x50,	//#12 11 heater boiler on/off (not always available)
// 0x91 and 0xA8 are specific to the RC20 and are setting regarding the thermostat.
// If you have f.i. a RC35 you need to set other messages here.
		0x17, 0x91, 0x01, 0x04,		//#13 12 setpoint room temperature x 2
		0x17, 0x91, 0x02, 0x05,			//#14 13 room temperature x 10
		0x17, 0xA8, 0x17, 0x81,	//#15 14 setting 0=low, 1=manual, 2=clock
		0x17, 0xA8, 0x1C, 0x84,	//#16 15 overruled clock setting x 2 ( 0 = not overruled)
		0x17, 0xA8, 0x1D, 0x84		//#17 16 manual setpoint temperature x 2
		};
