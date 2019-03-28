################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CamAq.cpp \
../src/hog.cpp \
../src/main.cpp \
../src/rpiPWM1.cpp \
../src/rpiServo.cpp \
../src/server.cpp \
../src/video.cpp 

OBJS += \
./src/CamAq.o \
./src/hog.o \
./src/main.o \
./src/rpiPWM1.o \
./src/rpiServo.o \
./src/server.o \
./src/video.o 

CPP_DEPS += \
./src/CamAq.d \
./src/hog.d \
./src/main.d \
./src/rpiPWM1.d \
./src/rpiServo.d \
./src/server.d \
./src/video.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -D__GXX_EXPERIMENTAL_CXX0X__ -D__cplusplus=201402L -I/usr/local/include -I/home/intema/workspace_RPI/libs/raspicam-0.1.6/raspicam-0.1.6/src -I/home/intema/workspace_RPI/libs/dependencies/current/interface/mmal -I/home/intema/workspace_RPI/libs/dependencies/current/interface/vcos -O0 -g3 -Wall -c -fmessage-length=0 -c -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


