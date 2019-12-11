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
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/08_Source" -I"C:\Users\XZH\Desktop\KL25_SPI_1-6\05_Driver\spi" -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/07_Soft_Component" -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/07_Soft_Component/common" -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/07_Soft_Component/printf" -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/04_Linker_File" -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/05_Driver/uart" -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/06_App_Component" -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/06_App_Component/light" -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/05_Driver" -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/03_MCU" -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/02_CPU" -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/01_Doc" -I"C:/Users/XZH/Desktop/KL25_SPI_1-6/05_Driver/gpio" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


