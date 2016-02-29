################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc11.c \
../src/debug.c \
../src/lcd.c \
../src/main.c \
../src/ow.c \
../src/small_gpio.c 

OBJS += \
./src/cr_startup_lpc11.o \
./src/debug.o \
./src/lcd.o \
./src/main.o \
./src/ow.o \
./src/small_gpio.o 

C_DEPS += \
./src/cr_startup_lpc11.d \
./src/debug.d \
./src/lcd.d \
./src/main.d \
./src/ow.d \
./src/small_gpio.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_CMSIS=CMSISv1p30_LPC11xx -DNDEBUG -D__REDLIB__ -I"/home/peterz/work/LPCXpresso/CMSISv1p30_LPC11xx/inc" -I"/home/peterz/work/LPCXpresso/lib_small_printf_m0/inc" -I"/home/peterz/work/LPCXpresso/freertos_lpc11xx/freertos/port/lpcxpresso/m0" -I"/home/peterz/work/LPCXpresso/freertos_lpc11xx/inc" -I"/home/peterz/work/LPCXpresso/freertos_lpc11xx/freertos/inc" -Os -Os -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


