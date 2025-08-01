################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src_app/src/cui_141pf.c \
../src_app/src/gpio.c \
../src_app/src/gui_141pf.c \
../src_app/src/i2c.c \
../src_app/src/interrupt.c \
../src_app/src/libc-hooks.c \
../src_app/src/main.c \
../src_app/src/mcs4.c \
../src_app/src/spi.c \
../src_app/src/system.c \
../src_app/src/touchlcd_cap.c \
../src_app/src/touchlcd_res.c \
../src_app/src/touchlcd_tft.c \
../src_app/src/uart.c \
../src_app/src/xprintf.c 

S_UPPER_SRCS += \
../src_app/src/startup.S 

OBJS += \
./src_app/src/cui_141pf.o \
./src_app/src/gpio.o \
./src_app/src/gui_141pf.o \
./src_app/src/i2c.o \
./src_app/src/interrupt.o \
./src_app/src/libc-hooks.o \
./src_app/src/main.o \
./src_app/src/mcs4.o \
./src_app/src/spi.o \
./src_app/src/startup.o \
./src_app/src/system.o \
./src_app/src/touchlcd_cap.o \
./src_app/src/touchlcd_res.o \
./src_app/src/touchlcd_tft.o \
./src_app/src/uart.o \
./src_app/src/xprintf.o 

S_UPPER_DEPS += \
./src_app/src/startup.d 

C_DEPS += \
./src_app/src/cui_141pf.d \
./src_app/src/gpio.d \
./src_app/src/gui_141pf.d \
./src_app/src/i2c.d \
./src_app/src/interrupt.d \
./src_app/src/libc-hooks.d \
./src_app/src/main.d \
./src_app/src/mcs4.d \
./src_app/src/spi.d \
./src_app/src/system.d \
./src_app/src/touchlcd_cap.d \
./src_app/src/touchlcd_res.d \
./src_app/src/touchlcd_tft.d \
./src_app/src/uart.d \
./src_app/src/xprintf.d 


# Each subdirectory must supply rules for building sources it contributes
src_app/src/%.o: ../src_app/src/%.c src_app/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-elf-gcc -march=rv32imac_zicsr -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -g3 -ggdb -I"C:\MCS4_141PF\MCS4_SYSTEM\SOFTWARE\workspace\MCS4_141PF\src_kernel\inc" -I"C:\MCS4_141PF\MCS4_SYSTEM\SOFTWARE\workspace\MCS4_141PF\src_app\inc" -fno-common -fno-builtin-printf -nostartfiles -nostdlib -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src_app/src/%.o: ../src_app/src/%.S src_app/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross Assembler'
	riscv-none-elf-gcc -march=rv32imac_zicsr -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -g3 -ggdb -x assembler-with-cpp -DportasmHANDLE_INTERRUPT=External_Interrupt_Handler -I"C:\MCS4_141PF\MCS4_SYSTEM\SOFTWARE\workspace\MCS4_141PF\src_kernel\inc" -I"C:\MCS4_141PF\MCS4_SYSTEM\SOFTWARE\workspace\MCS4_141PF\src_app\inc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


