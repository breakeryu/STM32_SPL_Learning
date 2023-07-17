################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/bsp_board.c \
../BSP/bsp_gpio.c \
../BSP/bsp_rcc.c \
../BSP/delay.c \
../BSP/sys.c 

OBJS += \
./BSP/bsp_board.o \
./BSP/bsp_gpio.o \
./BSP/bsp_rcc.o \
./BSP/delay.o \
./BSP/sys.o 

C_DEPS += \
./BSP/bsp_board.d \
./BSP/bsp_gpio.d \
./BSP/bsp_rcc.d \
./BSP/delay.d \
./BSP/sys.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/%.o BSP/%.su BSP/%.cyclo: ../BSP/%.c BSP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103ZETx -DUSE_STDPERIPH_DRIVER -DSTM32F10X_HD -c -I../Inc -I../Libraries/CMSIS/CM3/CoreSupport -I../Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x -I../Libraries/STM32F10x_StdPeriph_Driver/inc -I../BSP -I../Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BSP

clean-BSP:
	-$(RM) ./BSP/bsp_board.cyclo ./BSP/bsp_board.d ./BSP/bsp_board.o ./BSP/bsp_board.su ./BSP/bsp_gpio.cyclo ./BSP/bsp_gpio.d ./BSP/bsp_gpio.o ./BSP/bsp_gpio.su ./BSP/bsp_rcc.cyclo ./BSP/bsp_rcc.d ./BSP/bsp_rcc.o ./BSP/bsp_rcc.su ./BSP/delay.cyclo ./BSP/delay.d ./BSP/delay.o ./BSP/delay.su ./BSP/sys.cyclo ./BSP/sys.d ./BSP/sys.o ./BSP/sys.su

.PHONY: clean-BSP

