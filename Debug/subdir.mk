################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Aktoren.cpp \
../Automat.cpp \
../Automaten_Funktionen.cpp \
../Digital_Input_Output.cpp \
../DoorControl.cpp \
../DoorInterface.cpp \
../Konfiguration.cpp \
../Sensoren.cpp \
../Transition.cpp \
../Zustaende.cpp \
../main.cpp 

OBJS += \
./Aktoren.o \
./Automat.o \
./Automaten_Funktionen.o \
./Digital_Input_Output.o \
./DoorControl.o \
./DoorInterface.o \
./Konfiguration.o \
./Sensoren.o \
./Transition.o \
./Zustaende.o \
./main.o 

CPP_DEPS += \
./Aktoren.d \
./Automat.d \
./Automaten_Funktionen.d \
./Digital_Input_Output.d \
./DoorControl.d \
./DoorInterface.d \
./Konfiguration.d \
./Sensoren.d \
./Transition.d \
./Zustaende.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


