################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/dc_motor_handler/dc_motor_prg.c 

OBJS += \
./HAL/dc_motor_handler/dc_motor_prg.o 

C_DEPS += \
./HAL/dc_motor_handler/dc_motor_prg.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/dc_motor_handler/%.o: ../HAL/dc_motor_handler/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


