################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../05_Driver/gpio/gpio.c 

OBJS += \
./05_Driver/gpio/gpio.o 

C_DEPS += \
./05_Driver/gpio/gpio.d 


# Each subdirectory must supply rules for building sources it contributes
05_Driver/gpio/%.o: ../05_Driver/gpio/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"C:/Users/PNN/Downloads/M0+2-160612/ch11-KL25-SPI-I2C-TSI/ch11-KL25-SPI-I2C-TSI/KL25_I2C_SLAVE(20160511)/08_Source" -I"C:\Users\PNN\Downloads\M0+2-160612\ch11-KL25-SPI-I2C-TSI\ch11-KL25-SPI-I2C-TSI\KL25_I2C_SLAVE(20160511)\05_Driver\i2c" -I"C:/Users/PNN/Downloads/M0+2-160612/ch11-KL25-SPI-I2C-TSI/ch11-KL25-SPI-I2C-TSI/KL25_I2C_SLAVE(20160511)/07_Soft_Component" -I"C:/Users/PNN/Downloads/M0+2-160612/ch11-KL25-SPI-I2C-TSI/ch11-KL25-SPI-I2C-TSI/KL25_I2C_SLAVE(20160511)/07_Soft_Component/common" -I"C:/Users/PNN/Downloads/M0+2-160612/ch11-KL25-SPI-I2C-TSI/ch11-KL25-SPI-I2C-TSI/KL25_I2C_SLAVE(20160511)/07_Soft_Component/printf" -I"C:/Users/PNN/Downloads/M0+2-160612/ch11-KL25-SPI-I2C-TSI/ch11-KL25-SPI-I2C-TSI/KL25_I2C_SLAVE(20160511)/04_Linker_File" -I"C:/Users/PNN/Downloads/M0+2-160612/ch11-KL25-SPI-I2C-TSI/ch11-KL25-SPI-I2C-TSI/KL25_I2C_SLAVE(20160511)/05_Driver/uart" -I"C:/Users/PNN/Downloads/M0+2-160612/ch11-KL25-SPI-I2C-TSI/ch11-KL25-SPI-I2C-TSI/KL25_I2C_SLAVE(20160511)/06_App_Component" -I"C:/Users/PNN/Downloads/M0+2-160612/ch11-KL25-SPI-I2C-TSI/ch11-KL25-SPI-I2C-TSI/KL25_I2C_SLAVE(20160511)/06_App_Component/light" -I"C:/Users/PNN/Downloads/M0+2-160612/ch11-KL25-SPI-I2C-TSI/ch11-KL25-SPI-I2C-TSI/KL25_I2C_SLAVE(20160511)/05_Driver" -I"C:/Users/PNN/Downloads/M0+2-160612/ch11-KL25-SPI-I2C-TSI/ch11-KL25-SPI-I2C-TSI/KL25_I2C_SLAVE(20160511)/03_MCU" -I"C:/Users/PNN/Downloads/M0+2-160612/ch11-KL25-SPI-I2C-TSI/ch11-KL25-SPI-I2C-TSI/KL25_I2C_SLAVE(20160511)/02_CPU" -I"C:/Users/PNN/Downloads/M0+2-160612/ch11-KL25-SPI-I2C-TSI/ch11-KL25-SPI-I2C-TSI/KL25_I2C_SLAVE(20160511)/01_Doc" -I"C:/Users/PNN/Downloads/M0+2-160612/ch11-KL25-SPI-I2C-TSI/ch11-KL25-SPI-I2C-TSI/KL25_I2C_SLAVE(20160511)/05_Driver/gpio" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


