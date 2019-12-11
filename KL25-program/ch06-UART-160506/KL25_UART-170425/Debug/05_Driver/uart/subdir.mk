################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../05_Driver/uart/uart.c 

OBJS += \
./05_Driver/uart/uart.o 

C_DEPS += \
./05_Driver/uart/uart.d 


# Each subdirectory must supply rules for building sources it contributes
05_Driver/uart/%.o: ../05_Driver/uart/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"E:/2013-2017 BOOK-170523/2012-2016 M0+-170523/06-User/SD-(M0+)-CD(V2.6)-170401/02-Software/KL25-program-160611/ch06-UART-160506/KL25_UART-170425/08_Source" -I"E:/2013-2017 BOOK-170523/2012-2016 M0+-170523/06-User/SD-(M0+)-CD(V2.6)-170401/02-Software/KL25-program-160611/ch06-UART-160506/KL25_UART-170425/07_Soft_Component" -I"E:/2013-2017 BOOK-170523/2012-2016 M0+-170523/06-User/SD-(M0+)-CD(V2.6)-170401/02-Software/KL25-program-160611/ch06-UART-160506/KL25_UART-170425/07_Soft_Component/common" -I"E:/2013-2017 BOOK-170523/2012-2016 M0+-170523/06-User/SD-(M0+)-CD(V2.6)-170401/02-Software/KL25-program-160611/ch06-UART-160506/KL25_UART-170425/07_Soft_Component/printf" -I"E:/2013-2017 BOOK-170523/2012-2016 M0+-170523/06-User/SD-(M0+)-CD(V2.6)-170401/02-Software/KL25-program-160611/ch06-UART-160506/KL25_UART-170425/04_Linker_File" -I"E:/2013-2017 BOOK-170523/2012-2016 M0+-170523/06-User/SD-(M0+)-CD(V2.6)-170401/02-Software/KL25-program-160611/ch06-UART-160506/KL25_UART-170425/05_Driver/uart" -I"E:/2013-2017 BOOK-170523/2012-2016 M0+-170523/06-User/SD-(M0+)-CD(V2.6)-170401/02-Software/KL25-program-160611/ch06-UART-160506/KL25_UART-170425/06_App_Component" -I"E:/2013-2017 BOOK-170523/2012-2016 M0+-170523/06-User/SD-(M0+)-CD(V2.6)-170401/02-Software/KL25-program-160611/ch06-UART-160506/KL25_UART-170425/06_App_Component/light" -I"E:/2013-2017 BOOK-170523/2012-2016 M0+-170523/06-User/SD-(M0+)-CD(V2.6)-170401/02-Software/KL25-program-160611/ch06-UART-160506/KL25_UART-170425/05_Driver" -I"E:/2013-2017 BOOK-170523/2012-2016 M0+-170523/06-User/SD-(M0+)-CD(V2.6)-170401/02-Software/KL25-program-160611/ch06-UART-160506/KL25_UART-170425/03_MCU" -I"E:/2013-2017 BOOK-170523/2012-2016 M0+-170523/06-User/SD-(M0+)-CD(V2.6)-170401/02-Software/KL25-program-160611/ch06-UART-160506/KL25_UART-170425/02_CPU" -I"E:/2013-2017 BOOK-170523/2012-2016 M0+-170523/06-User/SD-(M0+)-CD(V2.6)-170401/02-Software/KL25-program-160611/ch06-UART-160506/KL25_UART-170425/01_Doc" -I"E:/2013-2017 BOOK-170523/2012-2016 M0+-170523/06-User/SD-(M0+)-CD(V2.6)-170401/02-Software/KL25-program-160611/ch06-UART-160506/KL25_UART-170425/05_Driver/gpio" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


