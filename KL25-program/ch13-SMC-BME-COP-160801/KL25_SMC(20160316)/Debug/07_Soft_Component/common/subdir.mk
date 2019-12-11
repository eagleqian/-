################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../07_Soft_Component/common/common.c 

OBJS += \
./07_Soft_Component/common/common.o 

C_DEPS += \
./07_Soft_Component/common/common.d 


# Each subdirectory must supply rules for building sources it contributes
07_Soft_Component/common/%.o: ../07_Soft_Component/common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"E:/KL25 AND MQX CD/KL25_20160317/KL25_sample/KL25/KL25_SMC(20160316)/08_Source" -I"E:/KL25 AND MQX CD/KL25_20160317/KL25_sample/KL25/KL25_SMC(20160316)/07_Soft_Component" -I"E:/KL25 AND MQX CD/KL25_20160317/KL25_sample/KL25/KL25_SMC(20160316)/07_Soft_Component/common" -I"E:/KL25 AND MQX CD/KL25_20160317/KL25_sample/KL25/KL25_SMC(20160316)/07_Soft_Component/printf" -I"E:/KL25 AND MQX CD/KL25_20160317/KL25_sample/KL25/KL25_SMC(20160316)/04_Linker_File" -I"E:/KL25 AND MQX CD/KL25_20160317/KL25_sample/KL25/KL25_SMC(20160316)/05_Driver/uart" -I"E:/KL25 AND MQX CD/KL25_20160317/KL25_sample/KL25/KL25_SMC(20160316)/05_Driver/smc" -I"E:/KL25 AND MQX CD/KL25_20160317/KL25_sample/KL25/KL25_SMC(20160316)/06_App_Component" -I"E:/KL25 AND MQX CD/KL25_20160317/KL25_sample/KL25/KL25_SMC(20160316)/06_App_Component/light" -I"E:/KL25 AND MQX CD/KL25_20160317/KL25_sample/KL25/KL25_SMC(20160316)/05_Driver" -I"E:/KL25 AND MQX CD/KL25_20160317/KL25_sample/KL25/KL25_SMC(20160316)/03_MCU" -I"E:/KL25 AND MQX CD/KL25_20160317/KL25_sample/KL25/KL25_SMC(20160316)/02_CPU" -I"E:/KL25 AND MQX CD/KL25_20160317/KL25_sample/KL25/KL25_SMC(20160316)/01_Doc" -I"E:/KL25 AND MQX CD/KL25_20160317/KL25_sample/KL25/KL25_SMC(20160316)/05_Driver/gpio" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


