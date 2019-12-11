################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../09_MQXLite/psp/cortex_m/cortex.c \
../09_MQXLite/psp/cortex_m/int_gkis.c \
../09_MQXLite/psp/cortex_m/int_inst.c \
../09_MQXLite/psp/cortex_m/int_kisr.c \
../09_MQXLite/psp/cortex_m/int_pvta.c \
../09_MQXLite/psp/cortex_m/int_unx.c \
../09_MQXLite/psp/cortex_m/int_vtab.c \
../09_MQXLite/psp/cortex_m/int_xcpt.c \
../09_MQXLite/psp/cortex_m/mem_zero.c \
../09_MQXLite/psp/cortex_m/psp_iinit.c \
../09_MQXLite/psp/cortex_m/psp_supp.c \
../09_MQXLite/psp/cortex_m/psp_tiad.c \
../09_MQXLite/psp/cortex_m/psp_tinm.c \
../09_MQXLite/psp/cortex_m/psp_tipr.c \
../09_MQXLite/psp/cortex_m/psp_tisu.c \
../09_MQXLite/psp/cortex_m/sc_irdyq.c \
../09_MQXLite/psp/cortex_m/stack_bu.c \
../09_MQXLite/psp/cortex_m/stack_de.c \
../09_MQXLite/psp/cortex_m/stack_st.c 

OBJS += \
./09_MQXLite/psp/cortex_m/cortex.o \
./09_MQXLite/psp/cortex_m/int_gkis.o \
./09_MQXLite/psp/cortex_m/int_inst.o \
./09_MQXLite/psp/cortex_m/int_kisr.o \
./09_MQXLite/psp/cortex_m/int_pvta.o \
./09_MQXLite/psp/cortex_m/int_unx.o \
./09_MQXLite/psp/cortex_m/int_vtab.o \
./09_MQXLite/psp/cortex_m/int_xcpt.o \
./09_MQXLite/psp/cortex_m/mem_zero.o \
./09_MQXLite/psp/cortex_m/psp_iinit.o \
./09_MQXLite/psp/cortex_m/psp_supp.o \
./09_MQXLite/psp/cortex_m/psp_tiad.o \
./09_MQXLite/psp/cortex_m/psp_tinm.o \
./09_MQXLite/psp/cortex_m/psp_tipr.o \
./09_MQXLite/psp/cortex_m/psp_tisu.o \
./09_MQXLite/psp/cortex_m/sc_irdyq.o \
./09_MQXLite/psp/cortex_m/stack_bu.o \
./09_MQXLite/psp/cortex_m/stack_de.o \
./09_MQXLite/psp/cortex_m/stack_st.o 

C_DEPS += \
./09_MQXLite/psp/cortex_m/cortex.d \
./09_MQXLite/psp/cortex_m/int_gkis.d \
./09_MQXLite/psp/cortex_m/int_inst.d \
./09_MQXLite/psp/cortex_m/int_kisr.d \
./09_MQXLite/psp/cortex_m/int_pvta.d \
./09_MQXLite/psp/cortex_m/int_unx.d \
./09_MQXLite/psp/cortex_m/int_vtab.d \
./09_MQXLite/psp/cortex_m/int_xcpt.d \
./09_MQXLite/psp/cortex_m/mem_zero.d \
./09_MQXLite/psp/cortex_m/psp_iinit.d \
./09_MQXLite/psp/cortex_m/psp_supp.d \
./09_MQXLite/psp/cortex_m/psp_tiad.d \
./09_MQXLite/psp/cortex_m/psp_tinm.d \
./09_MQXLite/psp/cortex_m/psp_tipr.d \
./09_MQXLite/psp/cortex_m/psp_tisu.d \
./09_MQXLite/psp/cortex_m/sc_irdyq.d \
./09_MQXLite/psp/cortex_m/stack_bu.d \
./09_MQXLite/psp/cortex_m/stack_de.d \
./09_MQXLite/psp/cortex_m/stack_st.d 


# Each subdirectory must supply rules for building sources it contributes
09_MQXLite/psp/cortex_m/%.o: ../09_MQXLite/psp/cortex_m/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/05_Driver/uart" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/05_Driver" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/app" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/psp/cortex_m/compiler/cwgcc" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/psp/cortex_m/core/M0" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/psp/cortex_m" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/kernel" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/bsp" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/config" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/09_MQXLite/include" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/06_App_Component/light" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/06_App_Component" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/07_Soft_Component/common" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/07_Soft_Component/printf" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/07_Soft_Component" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/08_Sources" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/04_Linker_File" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/05_Driver/gpio" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/03_MCU" -I"D:/suda/KL25_BOOK/program/KL25_MQXLite(20160421)/02_CPU" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


