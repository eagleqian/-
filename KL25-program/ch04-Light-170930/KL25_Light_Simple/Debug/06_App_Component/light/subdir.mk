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
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"F:/嵌入式/SD-(M0+)-CD(V2.7)-170930/02-Software/KL25-program/ch04-Light-170930/KL25_Light_Simple/08_Source" -I"F:/嵌入式/SD-(M0+)-CD(V2.7)-170930/02-Software/KL25-program/ch04-Light-170930/KL25_Light_Simple/07_Soft_Component" -I"F:/嵌入式/SD-(M0+)-CD(V2.7)-170930/02-Software/KL25-program/ch04-Light-170930/KL25_Light_Simple/07_Soft_Component/common" -I"F:/嵌入式/SD-(M0+)-CD(V2.7)-170930/02-Software/KL25-program/ch04-Light-170930/KL25_Light_Simple/04_Linker_File" -I"F:/嵌入式/SD-(M0+)-CD(V2.7)-170930/02-Software/KL25-program/ch04-Light-170930/KL25_Light_Simple/06_App_Component" -I"F:/嵌入式/SD-(M0+)-CD(V2.7)-170930/02-Software/KL25-program/ch04-Light-170930/KL25_Light_Simple/06_App_Component/light" -I"F:/嵌入式/SD-(M0+)-CD(V2.7)-170930/02-Software/KL25-program/ch04-Light-170930/KL25_Light_Simple/05_Driver" -I"F:/嵌入式/SD-(M0+)-CD(V2.7)-170930/02-Software/KL25-program/ch04-Light-170930/KL25_Light_Simple/03_MCU" -I"F:/嵌入式/SD-(M0+)-CD(V2.7)-170930/02-Software/KL25-program/ch04-Light-170930/KL25_Light_Simple/02_CPU" -I"F:/嵌入式/SD-(M0+)-CD(V2.7)-170930/02-Software/KL25-program/ch04-Light-170930/KL25_Light_Simple/01_Doc" -I"F:/嵌入式/SD-(M0+)-CD(V2.7)-170930/02-Software/KL25-program/ch04-Light-170930/KL25_Light_Simple/05_Driver/gpio" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


