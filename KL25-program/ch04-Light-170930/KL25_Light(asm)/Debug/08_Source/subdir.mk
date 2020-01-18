################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../08_Source/include.S \
../08_Source/main.S 

OBJS += \
./08_Source/include.o \
./08_Source/main.o 

S_UPPER_DEPS += \
./08_Source/include.d \
./08_Source/main.d 


# Each subdirectory must supply rules for building sources it contributes
08_Source/%.o: ../08_Source/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -x assembler-with-cpp -I"E:\2013-2017 BOOK-170523\2012-2016 M0+-170523\06-User\SD-(M0+)-CD(V2.7)-170930\02-Software\KL25-program\ch04-Light-170930\KL25_Light(asm)\05_Driver\gpio" -I"E:\2013-2017 BOOK-170523\2012-2016 M0+-170523\06-User\SD-(M0+)-CD(V2.7)-170930\02-Software\KL25-program\ch04-Light-170930\KL25_Light(asm)\06_App_Component\light" -I"E:\2013-2017 BOOK-170523\2012-2016 M0+-170523\06-User\SD-(M0+)-CD(V2.7)-170930\02-Software\KL25-program\ch04-Light-170930\KL25_Light(asm)\08_Source" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


