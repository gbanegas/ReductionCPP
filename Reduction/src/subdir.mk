################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ContXor.cpp \
../src/GenerateMatrix.cpp \
../src/Otimizator.cpp \
../src/Pair.cpp \
../src/Reduction.cpp 

OBJS += \
./src/ContXor.o \
./src/GenerateMatrix.o \
./src/Otimizator.o \
./src/Pair.o \
./src/Reduction.o 

CPP_DEPS += \
./src/ContXor.d \
./src/GenerateMatrix.d \
./src/Otimizator.d \
./src/Pair.d \
./src/Reduction.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


