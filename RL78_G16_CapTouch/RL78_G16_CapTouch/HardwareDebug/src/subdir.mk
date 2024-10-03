################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/Led.c \
../src/RL78_G16_CapTouch.c \
../src/chimney.c 

COMPILER_OBJS += \
src/Led.obj \
src/RL78_G16_CapTouch.obj \
src/chimney.obj 

C_DEPS += \
src/Led.d \
src/RL78_G16_CapTouch.d \
src/chimney.d 

# Each subdirectory must supply rules for building sources it contributes
src/%.obj: ../src/%.c 
	@echo 'Scanning and building file: $<'
	ccrl -subcommand="src\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	ccrl -subcommand="src\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"


