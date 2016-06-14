// Do not remove the include below

#include "HouseHeating.h"

#include <Arduino.h>
#include <ethernet_comp.h>
#include <HardwareSerial.h>
#include <IPAddress.h>
#include <PubSubClient.h>
#include <Timer.h>
#include <UIPClient.h>

#include "Config/Config.h"
#include "Model/HeatingAdapter.h"
#include "Util/mqtt.h"

byte mqttServerAddress[] = MQTT_SERVER;
uint8_t macAddress[6] = MAC_ADDRESS;
IPAddress ipAddress(IP_ADDRESS);
EthernetClient ethClient;
PubSubClient mqttClient(mqttServerAddress, 1883, mqttCallback, ethClient);

HeatingAdapter heatingAdapter(&mqttClient);
//BedRoomKids bedRoomKids(&mqttClient);


Timer trigger;
void triggerFunc(){
	//TODO take out serial prints
	short desTemperature = random(20,25);	 	//simulation values
	heatingAdapter.updateRoomDesiredValue(KIDS_BEDROOM, TEMPERATURE, desTemperature);

	short tempSensorReal = random(15,35);  		//simulation values
	heatingAdapter.sensorUpdate(SENSOR_KIDS_01,tempSensorReal);
}

//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(115200);
	trigger.every(REOCCURRENCE,&triggerFunc);
	triggerFunc();
}

// The loop function is called in an endless loop
void loop()
{
	trigger.update();
}
