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
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -x assembler-with-cpp -I"F:\cbfkds\KL25_gpio_uart(asm)\03_MCU" -I"F:\cbfkds\KL25_gpio_uart(asm)\05_Driver\gpio" -I"F:\cbfkds\KL25_gpio_uart(asm)\05_Driver\uart" -I"F:\cbfkds\KL25_gpio_uart(asm)\07_Soft_Component\common" -I"F:\cbfkds\KL25_gpio_uart(asm)\06_App_Component\light" -I"F:\cbfkds\KL25_gpio_uart(asm)\08_Source" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

03_MCU/%.o: ../03_MCU/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"F:/cbfkds/KL25_gpio_uart(asm)/08_Source" -I"F:/cbfkds/KL25_gpio_uart(asm)/07_Soft_Component" -I"F:/cbfkds/KL25_gpio_uart(asm)/07_Soft_Component/common" -I"F:/cbfkds/KL25_gpio_uart(asm)/04_Linker_File" -I"F:/cbfkds/KL25_gpio_uart(asm)/06_App_Component" -I"F:/cbfkds/KL25_gpio_uart(asm)/06_App_Component/light" -I"F:/cbfkds/KL25_gpio_uart(asm)/05_Driver" -I"F:/cbfkds/KL25_gpio_uart(asm)/03_MCU" -I"F:/cbfkds/KL25_gpio_uart(asm)/02_CPU" -I"F:/cbfkds/KL25_gpio_uart(asm)/01_Doc" -I"F:/cbfkds/KL25_gpio_uart(asm)/05_Driver/gpio" -I"F:/cbfkds/KL25_gpio_uart(asm)/05_Driver/uart" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


