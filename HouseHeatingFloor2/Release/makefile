################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ..\makefile.init

RM := del 

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include libraries\UIPEthernet\utility\subdir.mk
-include libraries\UIPEthernet\subdir.mk
-include libraries\Timer\subdir.mk
-include libraries\PubSubClient\src\subdir.mk
-include libraries\OneWire\subdir.mk
-include libraries\EmonLib\subdir.mk
-include libraries\DallasTemperature\subdir.mk
-include libraries\DHT\subdir.mk
-include core\core\subdir.mk
-include Model\subdir.mk
-include Library\Room\subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ..\makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
D:\src\ArduinoMega\HouseHeatingFloor2\Release\arduino.ar \

ELF += \
HouseHeatingFloor2.elf \

HEX += \
HouseHeatingFloor2.hex \


# All Target
all: HouseHeatingFloor2

# Tool invocations
HouseHeatingFloor2: $(HEX)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"C:\Eclipse\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-size" -A "D:/src/ArduinoMega/HouseHeatingFloor2/Release/HouseHeatingFloor2.elf"
	@echo 'Finished building target: $@'
	@echo ' '

D:\src\ArduinoMega\HouseHeatingFloor2\Release\arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"C:\Eclipse\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs    D:/src/ArduinoMega/HouseHeatingFloor2/Release/arduino.ar $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

HouseHeatingFloor2.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"C:\Eclipse\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc" -Wall -Wextra -Os -Wl,--gc-sections,--relax -mmcu=atmega2560 -o "D:\src\ArduinoMega\HouseHeatingFloor2/Release/HouseHeatingFloor2.elf"   $(LINK_OBJ)   D:/src/ArduinoMega/HouseHeatingFloor2/Release/arduino.ar  "-LD:\src\ArduinoMega\HouseHeatingFloor2/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

HouseHeatingFloor2.hex: $(ELF)
	@echo 'Create eeprom image'
	${A.RECIPE.OBJCOPY.EEP.PATTERN}
	${A.RECIPE.OBJCOPY.HEX.PATTERN}
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(HEX)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS)
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ..\makefile.targets
