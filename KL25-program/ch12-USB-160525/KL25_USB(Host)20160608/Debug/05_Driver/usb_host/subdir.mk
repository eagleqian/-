################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../05_Driver/usb_host/usb_host.c 

OBJS += \
./05_Driver/usb_host/usb_host.o 

C_DEPS += \
./05_Driver/usb_host/usb_host.d 


# Each subdirectory must supply rules for building sources it contributes
05_Driver/usb_host/%.o: ../05_Driver/usb_host/%.c
    @echo 'Building file: $<'
    @echo 'Invoking: Cross ARM C Compiler'
    arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch12-USB(HWW)-(20160512)/KL25_USB(Host)20160608/08_Source" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch12-USB(HWW)-(20160512)/KL25_USB(Host)20160608/07_Soft_Component" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch12-USB(HWW)-(20160512)/KL25_USB(Host)20160608/07_Soft_Component/common" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch12-USB(HWW)-(20160512)/KL25_USB(Host)20160608/07_Soft_Component/printf" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch12-USB(HWW)-(20160512)/KL25_USB(Host)20160608/04_Linker_File" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch12-USB(HWW)-(20160512)/KL25_USB(Host)20160608/05_Driver/uart" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch12-USB(HWW)-(20160512)/KL25_USB(Host)20160608/06_App_Component/usb/usb_device" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch12-USB(HWW)-(20160512)/KL25_USB(Host)20160608/06_App_Component" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch12-USB(HWW)-(20160512)/KL25_USB(Host)20160608/05_Driver/usb_host" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch12-USB(HWW)-(20160512)/KL25_USB(Host)20160608/06_App_Component/light" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch12-USB(HWW)-(20160512)/KL25_USB(Host)20160608/06_App_Component/usb" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch12-USB(HWW)-(20160512)/KL25_USB(Host)20160608/06_App_Component/usb/fatfs" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch12-USB(HWW)-(20160512)/KL25_USB(Host)20160608/06_App_Component/usb/usb_class" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch12-USB(HWW)-(20160512)/KL25_USB(Host)20160608/05_Driver" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch12-USB(HWW)-(20160512)/KL25_USB(Host)20160608/03_MCU" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch12-USB(HWW)-(20160512)/KL25_USB(Host)20160608/02_CPU" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch12-USB(HWW)-(20160512)/KL25_USB(Host)20160608/01_Doc" -I"D:/suda/KL25_BOOK/SD-KL-CD(V6.5)-20160505/02-Software/KL25-program/ch12-USB(HWW)-(20160512)/KL25_USB(Host)20160608/05_Driver/gpio" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
    @echo 'Finished building: $<'
    @echo ' '


