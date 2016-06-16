################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../HouseHeating.cpp 

LINK_OBJ += \
./HouseHeating.cpp.o 

CPP_DEPS += \
./HouseHeating.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
HouseHeating.cpp.o: ../HouseHeating.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"D:\HomeAutomation\Arduino\hardware\tools\avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10605 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"D:\HomeAutomation\Arduino\hardware\arduino\avr\cores\arduino" -I"D:\HomeAutomation\Arduino\hardware\arduino\avr\variants\mega" -I"D:\HomeAutomation\Arduino\libraries\Timer" -I"D:\HomeAutomation\Arduino\libraries\DHTlib" -I"D:\HomeAutomation\Arduino\libraries\MQTT" -I"D:\HomeAutomation\Arduino\libraries\OneWire" -I"D:\HomeAutomation\Arduino\libraries\UIPEthernet" -I"D:\HomeAutomation\Arduino\libraries\UIPEthernet\utility" -I"D:\HomeAutomation\Arduino\libraries\EmonLib" -I"D:\HomeAutomation\Arduino\libraries\DalasTemperature" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '


