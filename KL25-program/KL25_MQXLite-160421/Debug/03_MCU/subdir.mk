################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../03_MCU/system_MKL25Z4.c 

S_UPPER_SRCS += \
../03_MCU/startup_MKL25Z4.S 

OBJS += \
./03_MCU/startup_MKL25Z4.o \
./03_MCU/system_MKL25Z4.o 

C_DEPS += \
./03_MCU/system_MKL25Z4.d 

S_UPPER_DEPS += \
./03_MCU/startup_MKL25Z4.d 


# Each subdirectory must supply rules for building sources it contributes
03_MCU/%.o: ../03_MCU/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -x assembler-with-cpp -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/03_MCU" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/psp/cortex_m/compiler/cwgcc" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/psp/cortex_m/core/M0" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/psp/cortex_m" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/kernel" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/bsp" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/config" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/include" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/03_MCU" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

03_MCU/%.o: ../03_MCU/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/05_Driver/uart" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/05_Driver" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/app" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/psp/cortex_m/compiler/cwgcc" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/psp/cortex_m/core/M0" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/psp/cortex_m" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/kernel" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/bsp" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/config" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/include" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/06_App_Component/light" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/06_App_Component" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/07_Soft_Component/common" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/07_Soft_Component/printf" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/07_Soft_Component" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/08_Sources" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/04_Linker_File" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/05_Driver/gpio" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/03_MCU" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/02_CPU" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


