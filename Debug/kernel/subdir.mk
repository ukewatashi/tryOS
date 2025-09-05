################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../kernel/context.c \
../kernel/inittsk.c \
../kernel/scheduler.c \
../kernel/syslib.c \
../kernel/systimer.c \
../kernel/task_mange.c \
../kernel/task_queue.c \
../kernel/task_sync.c 

S_UPPER_SRCS += \
../kernel/dispatch.S 

OBJS += \
./kernel/context.o \
./kernel/dispatch.o \
./kernel/inittsk.o \
./kernel/scheduler.o \
./kernel/syslib.o \
./kernel/systimer.o \
./kernel/task_mange.o \
./kernel/task_queue.o \
./kernel/task_sync.o 

S_UPPER_DEPS += \
./kernel/dispatch.d 

C_DEPS += \
./kernel/context.d \
./kernel/inittsk.d \
./kernel/scheduler.d \
./kernel/syslib.d \
./kernel/systimer.d \
./kernel/task_mange.d \
./kernel/task_queue.d \
./kernel/task_sync.d 


# Each subdirectory must supply rules for building sources it contributes
kernel/%.o: ../kernel/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -ffreestanding  -g3 -I"C:\Users\sippu\eclipse-workspace\tryos02\include" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

kernel/%.o: ../kernel/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -ffreestanding  -g3 -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


