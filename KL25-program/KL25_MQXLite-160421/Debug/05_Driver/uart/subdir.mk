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
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/05_Driver/uart" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/05_Driver" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/app" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/psp/cortex_m/compiler/cwgcc" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/psp/cortex_m/core/M0" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/psp/cortex_m" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/kernel" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/bsp" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/config" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/include" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/06_App_Component/light" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/06_App_Component" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/07_Soft_Component/common" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/07_Soft_Component/printf" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/07_Soft_Component" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/08_Sources" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/04_Linker_File" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/05_Driver/gpio" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/03_MCU" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/02_CPU" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


