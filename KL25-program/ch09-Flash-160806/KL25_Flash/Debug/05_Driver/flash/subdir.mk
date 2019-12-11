################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../05_Driver/flash/flash.c 

OBJS += \
./05_Driver/flash/flash.o 

C_DEPS += \
./05_Driver/flash/flash.d 


# Each subdirectory must supply rules for building sources it contributes
05_Driver/flash/%.o: ../05_Driver/flash/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"F:/LbLearning/My Projects/20160314 KL25-NewBook/20160515 KL25_Chap9_Flash/ch09-Flash/KL25_Flash/08_Source" -I"F:/LbLearning/My Projects/20160314 KL25-NewBook/20160515 KL25_Chap9_Flash/ch09-Flash/KL25_Flash/07_Soft_Component" -I"F:/LbLearning/My Projects/20160314 KL25-NewBook/20160515 KL25_Chap9_Flash/ch09-Flash/KL25_Flash/07_Soft_Component/common" -I"F:/LbLearning/My Projects/20160314 KL25-NewBook/20160515 KL25_Chap9_Flash/ch09-Flash/KL25_Flash/07_Soft_Component/printf" -I"F:/LbLearning/My Projects/20160314 KL25-NewBook/20160515 KL25_Chap9_Flash/ch09-Flash/KL25_Flash/04_Linker_File" -I"F:/LbLearning/My Projects/20160314 KL25-NewBook/20160515 KL25_Chap9_Flash/ch09-Flash/KL25_Flash/05_Driver/uart" -I"F:/LbLearning/My Projects/20160314 KL25-NewBook/20160515 KL25_Chap9_Flash/ch09-Flash/KL25_Flash/06_App_Component" -I"F:/LbLearning/My Projects/20160314 KL25-NewBook/20160515 KL25_Chap9_Flash/ch09-Flash/KL25_Flash/06_App_Component/light" -I"F:/LbLearning/My Projects/20160314 KL25-NewBook/20160515 KL25_Chap9_Flash/ch09-Flash/KL25_Flash/05_Driver" -I"F:/LbLearning/My Projects/20160314 KL25-NewBook/20160515 KL25_Chap9_Flash/ch09-Flash/KL25_Flash/03_MCU" -I"F:/LbLearning/My Projects/20160314 KL25-NewBook/20160515 KL25_Chap9_Flash/ch09-Flash/KL25_Flash/02_CPU" -I"F:/LbLearning/My Projects/20160314 KL25-NewBook/20160515 KL25_Chap9_Flash/ch09-Flash/KL25_Flash/01_Doc" -I"F:/LbLearning/My Projects/20160314 KL25-NewBook/20160515 KL25_Chap9_Flash/ch09-Flash/KL25_Flash/05_Driver/gpio" -I"F:/LbLearning/My Projects/20160314 KL25-NewBook/20160515 KL25_Chap9_Flash/ch09-Flash/KL25_Flash/05_Driver/flash" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


