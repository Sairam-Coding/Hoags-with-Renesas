################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_ctsu/r_ctsu.c 

COMPILER_OBJS += \
src/smc_gen/r_ctsu/r_ctsu.obj 

C_DEPS += \
src/smc_gen/r_ctsu/r_ctsu.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_ctsu/%.obj: ../src/smc_gen/r_ctsu/%.c 
	@echo 'Scanning and building file: $<'
	ccrl -subcommand="src\smc_gen\r_ctsu\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	ccrl -subcommand="src\smc_gen\r_ctsu\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"


