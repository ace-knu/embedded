################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/Service/CpuGeneric/SysSe/Time/Ifx_DateTime.c 

COMPILED_SRCS += \
./Libraries/Service/CpuGeneric/SysSe/Time/Ifx_DateTime.src 

C_DEPS += \
./Libraries/Service/CpuGeneric/SysSe/Time/Ifx_DateTime.d 

OBJS += \
./Libraries/Service/CpuGeneric/SysSe/Time/Ifx_DateTime.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Service/CpuGeneric/SysSe/Time/%.src: ../Libraries/Service/CpuGeneric/SysSe/Time/%.c Libraries/Service/CpuGeneric/SysSe/Time/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc27xd "-fD:/PersonalFiles/jehongjeon/AURIX Studio/workspace/tc275_Motor_2/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/Libraries\/Service\/CpuGeneric\/SysSe\/Time\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

Libraries/Service/CpuGeneric/SysSe/Time/%.o: ./Libraries/Service/CpuGeneric/SysSe/Time/%.src Libraries/Service/CpuGeneric/SysSe/Time/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Libraries-2f-Service-2f-CpuGeneric-2f-SysSe-2f-Time

clean-Libraries-2f-Service-2f-CpuGeneric-2f-SysSe-2f-Time:
	-$(RM) ./Libraries/Service/CpuGeneric/SysSe/Time/Ifx_DateTime.d ./Libraries/Service/CpuGeneric/SysSe/Time/Ifx_DateTime.o ./Libraries/Service/CpuGeneric/SysSe/Time/Ifx_DateTime.src

.PHONY: clean-Libraries-2f-Service-2f-CpuGeneric-2f-SysSe-2f-Time

