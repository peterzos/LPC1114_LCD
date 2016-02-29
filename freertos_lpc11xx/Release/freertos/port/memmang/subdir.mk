################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/port/memmang/heap_2.c 

OBJS += \
./freertos/port/memmang/heap_2.o 

C_DEPS += \
./freertos/port/memmang/heap_2.d 


# Each subdirectory must supply rules for building sources it contributes
freertos/port/memmang/%.o: ../freertos/port/memmang/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_CMSIS=CMSISv1p30_LPC11xx -DNDEBUG -D__REDLIB__ -I"/home/peterz/work/LPCXpresso/CMSISv1p30_LPC11xx/inc" -I"/home/peterz/work/LPCXpresso/lib_small_printf_m0/inc" -I"/home/peterz/work/LPCXpresso/freertos_lpc11xx/freertos/port/lpcxpresso/m0" -I"/home/peterz/work/LPCXpresso/freertos_lpc11xx/inc" -I"/home/peterz/work/LPCXpresso/freertos_lpc11xx/freertos/inc" -Os -Os -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


