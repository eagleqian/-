################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../09_MQXLite/app/task_A.c \
../09_MQXLite/app/task_B.c \
../09_MQXLite/app/task_C.c \
../09_MQXLite/app/task_D.c \
../09_MQXLite/app/task_main.c \
../09_MQXLite/app/task_templates.c 

OBJS += \
./09_MQXLite/app/task_A.o \
./09_MQXLite/app/task_B.o \
./09_MQXLite/app/task_C.o \
./09_MQXLite/app/task_D.o \
./09_MQXLite/app/task_main.o \
./09_MQXLite/app/task_templates.o 

C_DEPS += \
./09_MQXLite/app/task_A.d \
./09_MQXLite/app/task_B.d \
./09_MQXLite/app/task_C.d \
./09_MQXLite/app/task_D.d \
./09_MQXLite/app/task_main.d \
./09_MQXLite/app/task_templates.d 


# Each subdirectory must supply rules for building sources it contributes
09_MQXLite/app/%.o: ../09_MQXLite/app/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/05_Driver/uart" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/05_Driver" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/app" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/psp/cortex_m/compiler/cwgcc" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/psp/cortex_m/core/M0" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/psp/cortex_m" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/kernel" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/bsp" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/config" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/include" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/06_App_Component/light" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/06_App_Component" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/07_Soft_Component/common" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/07_Soft_Component/printf" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/07_Soft_Component" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/08_Sources" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/04_Linker_File" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/05_Driver/gpio" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/03_MCU" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/02_CPU" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


