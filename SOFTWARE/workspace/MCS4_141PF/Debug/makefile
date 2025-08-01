################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src_kernel/src/subdir.mk
-include src_app/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := MCS4_141PF
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
MCS4_141PF.hex \

SECONDARY_SIZE += \
MCS4_141PF.siz \


# All Target
all: main-build

# Main-build Target
main-build: MCS4_141PF.elf secondary-outputs

# Tool invocations
MCS4_141PF.elf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU RISC-V Cross C Linker'
	riscv-none-elf-gcc -march=rv32imac_zicsr -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -g3 -ggdb -T "C:\MCS4_141PF\MCS4_SYSTEM\SOFTWARE\workspace\MCS4_141PF\link.ld" -nostartfiles -Xlinker --gc-sections -L/opt/riscv/riscv64-unknown-elf/lib/rv32imafc/ilp32f -L/opt/riscv/lib/gcc/riscv64-unknown-elf/12.2.0/rv32imafc/ilp32f -Xlinker --no-warn-rwx-segmen -Wl,-Map,"MCS4_141PF.map" -nostartfiles -nostdlib -o "MCS4_141PF.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

MCS4_141PF.hex: MCS4_141PF.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GNU RISC-V Cross Create Flash Image'
	riscv-none-elf-objcopy -O ihex "MCS4_141PF.elf"  "MCS4_141PF.hex"
	@echo 'Finished building: $@'
	@echo ' '

MCS4_141PF.siz: MCS4_141PF.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GNU RISC-V Cross Print Size'
	riscv-none-elf-size --format=berkeley "MCS4_141PF.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SX_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) MCS4_141PF.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents main-build

-include ../makefile.targets
