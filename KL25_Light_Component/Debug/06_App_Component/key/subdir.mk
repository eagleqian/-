################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../06_App_Component/key/key.c 

OBJS += \
./06_App_Component/key/key.o 

C_DEPS += \
./06_App_Component/key/key.d 


# Each subdirectory must supply rules for building sources it contributes
06_App_Component/key/%.o: ../06_App_Component/key/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"F:/kds/KL25_Light_Component/08_NOS_Prg" -I"F:/kds/KL25_Light_Component/07_Soft_Component" -I"F:/kds/KL25_Light_Component/07_Soft_Component/common" -I"F:/kds/KL25_Light_Component/04_Linker_File" -I"F:/kds/KL25_Light_Component/06_App_Component" -I"F:/kds/KL25_Light_Component/06_App_Component/key" -I"F:/kds/KL25_Light_Component/05_Driver" -I"F:/kds/KL25_Light_Component/03_MCU" -I"F:/kds/KL25_Light_Component/02_CPU" -I"F:/kds/KL25_Light_Component/01_Doc" -I"F:/kds/KL25_Light_Component/05_Driver/gpio" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


