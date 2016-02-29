################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/core_cm0.c \
../src/system_LPC11xx.c 

OBJS += \
./src/core_cm0.o \
./src/system_LPC11xx.o 

C_DEPS += \
./src/core_cm0.d \
./src/system_LPC11xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DNDEBUG -D__CODE_RED -D__REDLIB__ -I"/home/peterz/work/LPCXpresso/CMSISv1p30_LPC11xx/inc" -Os -Os -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


