################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../05_Driver/systick/systick.c 

OBJS += \
./05_Driver/systick/systick.o 

C_DEPS += \
./05_Driver/systick/systick.d 


# Each subdirectory must supply rules for building sources it contributes
05_Driver/systick/%.o: ../05_Driver/systick/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"F:/kds/KL25_Systick/08_Source" -I"F:/kds/KL25_Systick/07_Soft_Component" -I"F:/kds/KL25_Systick/07_Soft_Component/common" -I"F:/kds/KL25_Systick/07_Soft_Component/printf" -I"F:/kds/KL25_Systick/04_Linker_File" -I"F:/kds/KL25_Systick/05_Driver/uart" -I"F:/kds/KL25_Systick/06_App_Component" -I"F:/kds/KL25_Systick/06_App_Component/light" -I"F:/kds/KL25_Systick/05_Driver" -I"F:/kds/KL25_Systick/03_MCU" -I"F:/kds/KL25_Systick/02_CPU" -I"F:/kds/KL25_Systick/01_Doc" -I"F:/kds/KL25_Systick/05_Driver/gpio" -I"F:/kds/KL25_Systick/05_Driver/systick" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


