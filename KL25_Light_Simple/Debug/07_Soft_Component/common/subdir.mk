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
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"F:/kds/KL25_Light_Simple/08_Source" -I"F:/kds/KL25_Light_Simple/07_Soft_Component" -I"F:/kds/KL25_Light_Simple/07_Soft_Component/common" -I"F:/kds/KL25_Light_Simple/04_Linker_File" -I"F:/kds/KL25_Light_Simple/06_App_Component" -I"F:/kds/KL25_Light_Simple/06_App_Component/light" -I"F:/kds/KL25_Light_Simple/05_Driver" -I"F:/kds/KL25_Light_Simple/03_MCU" -I"F:/kds/KL25_Light_Simple/02_CPU" -I"F:/kds/KL25_Light_Simple/01_Doc" -I"F:/kds/KL25_Light_Simple/05_Driver/gpio" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


