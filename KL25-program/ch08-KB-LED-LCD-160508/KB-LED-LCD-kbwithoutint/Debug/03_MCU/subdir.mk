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
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

03_MCU/%.o: ../03_MCU/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch08-KB-LED-LCD-20160509/KB-LED-LCD-kbwithoutint/08_Source" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch08-KB-LED-LCD-20160509/KB-LED-LCD-kbwithoutint/07_Soft_Component" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch08-KB-LED-LCD-20160509/KB-LED-LCD-kbwithoutint/07_Soft_Component/common" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch08-KB-LED-LCD-20160509/KB-LED-LCD-kbwithoutint/04_Linker_File" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch08-KB-LED-LCD-20160509/KB-LED-LCD-kbwithoutint/06_App_Component" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch08-KB-LED-LCD-20160509/KB-LED-LCD-kbwithoutint/06_App_Component/light" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch08-KB-LED-LCD-20160509/KB-LED-LCD-kbwithoutint/07_Soft_Component/printf" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch08-KB-LED-LCD-20160509/KB-LED-LCD-kbwithoutint/05_Driver" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch08-KB-LED-LCD-20160509/KB-LED-LCD-kbwithoutint/03_MCU" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch08-KB-LED-LCD-20160509/KB-LED-LCD-kbwithoutint/02_CPU" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch08-KB-LED-LCD-20160509/KB-LED-LCD-kbwithoutint/01_Doc" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch08-KB-LED-LCD-20160509/KB-LED-LCD-kbwithoutint/05_Driver/gpio" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch08-KB-LED-LCD-20160509/KB-LED-LCD-kbwithoutint/05_Driver/systick" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch08-KB-LED-LCD-20160509/KB-LED-LCD-kbwithoutint/05_Driver/uart" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch08-KB-LED-LCD-20160509/KB-LED-LCD-kbwithoutint/06_App_Component/led" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch08-KB-LED-LCD-20160509/KB-LED-LCD-kbwithoutint/06_App_Component/kb" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch08-KB-LED-LCD-20160509/KB-LED-LCD-kbwithoutint/06_App_Component/lcd" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


