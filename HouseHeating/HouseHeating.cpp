// Do not remove the include below

#include "HouseHeating.h"

#include <Arduino.h>
#include <HardwareSerial.h>
#include <IPAddress.h>
#include <PubSubClient.h>
#include <Timer.h>
#include <UIPEthernet.h>

#include "Config/Config.h"
#include "Model/BedRoomKids.h"
#include "Util/mqtt.h"

// Initialization of different objects
byte mqttServerAddress[] = MQTT_SERVER;
uint8_t macAddress[6] = MAC_ADDRESS;
IPAddress ipAddress(IP_ADDRESS);
EthernetClient ethClient;
PubSubClient mqttClient(MQTT_SERVER, 1883, mqttCallback, ethClient);

BedRoomKids bedRoomKids(&mqttClient);

Timer trigger;
void triggerFunc(){
	//TODO take out serial prints
	short desTemperature = random(20,25);	 	//simulation values
	Serial.print("Temperature desired value:\t"); Serial.println(desTemperature);
	short desHumidity = random(60,70); 	 		//simulation values
	Serial.print("Humidity desired value:\t"); Serial.println(desHumidity);
	bedRoomKids.updateDesiredValues(desTemperature,desHumidity);

	short tempSensorReal = random(15,35);  		//simulation values
	Serial.print("Temperature sensor value:\t"); Serial.println(tempSensorReal);
	short humSensorReal = random(40,100); 		//simulation values
	Serial.print("Humidity sensor value:\t"); Serial.println(humSensorReal);
	bedRoomKids.updateSensors(tempSensorReal,humSensorReal);

	bedRoomKids.updateOutputControllers();
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
