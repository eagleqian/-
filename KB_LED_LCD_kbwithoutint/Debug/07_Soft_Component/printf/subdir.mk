################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../07_Soft_Component/printf/printf.c 

OBJS += \
./07_Soft_Component/printf/printf.o 

C_DEPS += \
./07_Soft_Component/printf/printf.d 


# Each subdirectory must supply rules for building sources it contributes
07_Soft_Component/printf/%.o: ../07_Soft_Component/printf/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"F:/kds/KB_LED_LCD_kbwithoutint/08_Source" -I"F:/kds/KB_LED_LCD_kbwithoutint/07_Soft_Component" -I"F:/kds/KB_LED_LCD_kbwithoutint/07_Soft_Component/common" -I"F:/kds/KB_LED_LCD_kbwithoutint/04_Linker_File" -I"F:/kds/KB_LED_LCD_kbwithoutint/06_App_Component" -I"F:/kds/KB_LED_LCD_kbwithoutint/06_App_Component/light" -I"F:/kds/KB_LED_LCD_kbwithoutint/07_Soft_Component/printf" -I"F:/kds/KB_LED_LCD_kbwithoutint/05_Driver" -I"F:/kds/KB_LED_LCD_kbwithoutint/03_MCU" -I"F:/kds/KB_LED_LCD_kbwithoutint/02_CPU" -I"F:/kds/KB_LED_LCD_kbwithoutint/01_Doc" -I"F:/kds/KB_LED_LCD_kbwithoutint/05_Driver/gpio" -I"F:/kds/KB_LED_LCD_kbwithoutint/05_Driver/systick" -I"F:/kds/KB_LED_LCD_kbwithoutint/05_Driver/uart" -I"F:/kds/KB_LED_LCD_kbwithoutint/06_App_Component/led" -I"F:/kds/KB_LED_LCD_kbwithoutint/06_App_Component/kb" -I"F:/kds/KB_LED_LCD_kbwithoutint/06_App_Component/lcd" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


