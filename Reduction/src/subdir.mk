################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
ExpThread.cpp \
GenerateMatrix.cpp \
Otimizator.cpp \
Reduction.cpp \
ReductionMatrixThread.cpp \
Thread.cpp \
ThreadMatrix.cpp 

OBJS += \
ExpThread.o \
GenerateMatrix.o \
Otimizator.o \
Reduction.o \
ReductionMatrixThread.o \
Thread.o \
ThreadMatrix.o 

CPP_DEPS += \
ExpThread.d \
GenerateMatrix.d \
Otimizator.d \
Reduction.d \
ReductionMatrixThread.d \
Thread.d \
ThreadMatrix.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: %.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



