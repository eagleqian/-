################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../06_App_Component/light/light.c 

OBJS += \
./06_App_Component/light/light.o 

C_DEPS += \
./06_App_Component/light/light.d 


# Each subdirectory must supply rules for building sources it contributes
06_App_Component/light/%.o: ../06_App_Component/light/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"F:/kds/KL25_TPM-incap-outcomp-pwm/08_Source" -I"F:/kds/KL25_TPM-incap-outcomp-pwm/07_Soft_Component" -I"F:/kds/KL25_TPM-incap-outcomp-pwm/07_Soft_Component/common" -I"F:/kds/KL25_TPM-incap-outcomp-pwm/07_Soft_Component/printf" -I"F:/kds/KL25_TPM-incap-outcomp-pwm/04_Linker_File" -I"F:/kds/KL25_TPM-incap-outcomp-pwm/05_Driver/uart" -I"F:/kds/KL25_TPM-incap-outcomp-pwm/06_App_Component" -I"F:/kds/KL25_TPM-incap-outcomp-pwm/06_App_Component/light" -I"F:/kds/KL25_TPM-incap-outcomp-pwm/05_Driver" -I"F:/kds/KL25_TPM-incap-outcomp-pwm/03_MCU" -I"F:/kds/KL25_TPM-incap-outcomp-pwm/02_CPU" -I"F:/kds/KL25_TPM-incap-outcomp-pwm/01_Doc" -I"F:/kds/KL25_TPM-incap-outcomp-pwm/05_Driver/gpio" -I"F:/kds/KL25_TPM-incap-outcomp-pwm/05_Driver/tpm" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


