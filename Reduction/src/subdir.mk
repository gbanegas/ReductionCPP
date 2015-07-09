################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
GenerateMatrix.cpp \
Otimizator.cpp \
Reduction.cpp \
Thread.cpp \
ThreadMatrix.cpp 

OBJS += \
GenerateMatrix.o \
Otimizator.o \
Reduction.o \
Thread.o \
ThreadMatrix.o 

CPP_DEPS += \
GenerateMatrix.d \
Otimizator.d \
Reduction.d \
Thread.d \
ThreadMatrix.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: %.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



