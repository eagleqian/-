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
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"C:/Users/Administrator/Desktop/ch08-KB-LED-LCD-20160508/KB-LED-LCD-kbint/08_Source" -I"C:/Users/Administrator/Desktop/ch08-KB-LED-LCD-20160508/KB-LED-LCD-kbint/07_Soft_Component" -I"C:/Users/Administrator/Desktop/ch08-KB-LED-LCD-20160508/KB-LED-LCD-kbint/07_Soft_Component/common" -I"C:/Users/Administrator/Desktop/ch08-KB-LED-LCD-20160508/KB-LED-LCD-kbint/04_Linker_File" -I"C:/Users/Administrator/Desktop/ch08-KB-LED-LCD-20160508/KB-LED-LCD-kbint/06_App_Component" -I"C:/Users/Administrator/Desktop/ch08-KB-LED-LCD-20160508/KB-LED-LCD-kbint/06_App_Component/light" -I"C:/Users/Administrator/Desktop/ch08-KB-LED-LCD-20160508/KB-LED-LCD-kbint/07_Soft_Component/printf" -I"C:/Users/Administrator/Desktop/ch08-KB-LED-LCD-20160508/KB-LED-LCD-kbint/05_Driver" -I"C:/Users/Administrator/Desktop/ch08-KB-LED-LCD-20160508/KB-LED-LCD-kbint/03_MCU" -I"C:/Users/Administrator/Desktop/ch08-KB-LED-LCD-20160508/KB-LED-LCD-kbint/02_CPU" -I"C:/Users/Administrator/Desktop/ch08-KB-LED-LCD-20160508/KB-LED-LCD-kbint/01_Doc" -I"C:/Users/Administrator/Desktop/ch08-KB-LED-LCD-20160508/KB-LED-LCD-kbint/05_Driver/gpio" -I"C:/Users/Administrator/Desktop/ch08-KB-LED-LCD-20160508/KB-LED-LCD-kbint/05_Driver/systick" -I"C:/Users/Administrator/Desktop/ch08-KB-LED-LCD-20160508/KB-LED-LCD-kbint/05_Driver/uart" -I"C:/Users/Administrator/Desktop/ch08-KB-LED-LCD-20160508/KB-LED-LCD-kbint/06_App_Component/led" -I"C:/Users/Administrator/Desktop/ch08-KB-LED-LCD-20160508/KB-LED-LCD-kbint/06_App_Component/kb" -I"C:/Users/Administrator/Desktop/ch08-KB-LED-LCD-20160508/KB-LED-LCD-kbint/06_App_Component/lcd" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


