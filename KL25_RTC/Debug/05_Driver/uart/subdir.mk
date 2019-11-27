################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../05_Driver/uart/uart.c 

OBJS += \
./05_Driver/uart/uart.o 

C_DEPS += \
./05_Driver/uart/uart.d 


# Each subdirectory must supply rules for building sources it contributes
05_Driver/uart/%.o: ../05_Driver/uart/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"F:/kds/KL25_RTC/08_Source" -I"F:/kds/KL25_RTC/07_Soft_Component" -I"F:/kds/KL25_RTC/07_Soft_Component/common" -I"F:/kds/KL25_RTC/07_Soft_Component/printf" -I"F:/kds/KL25_RTC/04_Linker_File" -I"F:/kds/KL25_RTC/05_Driver/uart" -I"F:/kds/KL25_RTC/06_App_Component" -I"F:/kds/KL25_RTC/06_App_Component/light" -I"F:/kds/KL25_RTC/05_Driver" -I"F:/kds/KL25_RTC/03_MCU" -I"F:/kds/KL25_RTC/02_CPU" -I"F:/kds/KL25_RTC/01_Doc" -I"F:/kds/KL25_RTC/05_Driver/gpio" -I"F:/kds/KL25_RTC/05_Driver/rtc" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


