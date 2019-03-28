################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/communication/server_communication.cpp \
../src/communication/slave_communication.cpp 

OBJS += \
./src/communication/server_communication.o \
./src/communication/slave_communication.o 

CPP_DEPS += \
./src/communication/server_communication.d \
./src/communication/slave_communication.d 


# Each subdirectory must supply rules for building sources it contributes
src/communication/%.o: ../src/communication/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -D__GXX_EXPERIMENTAL_CXX0X__ -D__cplusplus=201402L -I/usr/local/include -I/home/intema/workspace_RPI/libs/raspicam-0.1.6/raspicam-0.1.6/src -I/home/intema/workspace_RPI/libs/dependencies/current/interface/mmal -I/home/intema/workspace_RPI/libs/dependencies/current/interface/vcos -O0 -g3 -Wall -c -fmessage-length=0 -c -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


