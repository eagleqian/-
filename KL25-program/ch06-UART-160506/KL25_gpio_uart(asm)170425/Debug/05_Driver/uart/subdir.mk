################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../05_Driver/uart/uart.S 

OBJS += \
./05_Driver/uart/uart.o 

S_UPPER_DEPS += \
./05_Driver/uart/uart.d 


# Each subdirectory must supply rules for building sources it contributes
05_Driver/uart/%.o: ../05_Driver/uart/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -x assembler-with-cpp -I"F:\cbfkds\KL25_gpio_uart(asm)\03_MCU" -I"F:\cbfkds\KL25_gpio_uart(asm)\05_Driver\gpio" -I"F:\cbfkds\KL25_gpio_uart(asm)\05_Driver\uart" -I"F:\cbfkds\KL25_gpio_uart(asm)\07_Soft_Component\common" -I"F:\cbfkds\KL25_gpio_uart(asm)\06_App_Component\light" -I"F:\cbfkds\KL25_gpio_uart(asm)\08_Source" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


