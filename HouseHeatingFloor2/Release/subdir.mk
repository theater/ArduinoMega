################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
..\HouseHeatingFloor2.cpp 

LINK_OBJ += \
.\HouseHeatingFloor2.cpp.o 

CPP_DEPS += \
.\HouseHeatingFloor2.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
HouseHeatingFloor2.cpp.o: ..\HouseHeatingFloor2.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Eclipse\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"C:\Eclipse\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.20\cores\arduino" -I"C:\Eclipse\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.20\variants\mega" -I"D:\src\ArduinoMega\Library\Room" -I"D:\HomeAutomation\ArduinoLibs\Timer" -I"C:\Eclipse\sloeber\arduinoPlugin\libraries\UIPEthernet\2.0.4" -I"C:\Eclipse\sloeber\arduinoPlugin\libraries\UIPEthernet\2.0.4\utility" -I"C:\Eclipse\sloeber\arduinoPlugin\libraries\DallasTemperature\3.7.6" -I"C:\Eclipse\sloeber\arduinoPlugin\libraries\OneWire\2.3.3" -I"C:\Eclipse\sloeber\arduinoPlugin\libraries\PubSubClient\2.6.0" -I"C:\Eclipse\sloeber\arduinoPlugin\libraries\PubSubClient\2.6.0\src" -I"D:\HomeAutomation\ArduinoLibs\DHT" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


