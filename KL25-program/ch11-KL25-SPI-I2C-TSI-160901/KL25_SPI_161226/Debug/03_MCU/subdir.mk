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
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/08_Source" -I"C:\Users\XZH\Desktop\KL25_SPI_1-6\05_Driver\spi" -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/07_Soft_Component" -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/07_Soft_Component/common" -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/07_Soft_Component/printf" -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/04_Linker_File" -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/05_Driver/uart" -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/06_App_Component" -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/06_App_Component/light" -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/05_Driver" -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/03_MCU" -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/02_CPU" -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/01_Doc" -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/05_Driver/gpio" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


