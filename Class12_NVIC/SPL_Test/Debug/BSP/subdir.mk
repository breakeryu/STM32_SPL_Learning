################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/bsp_adc.c \
../BSP/bsp_board.c \
../BSP/bsp_can.c \
../BSP/bsp_dac.c \
../BSP/bsp_gpio.c \
../BSP/bsp_i2c.c \
../BSP/bsp_nvic.c \
../BSP/bsp_rcc.c \
../BSP/bsp_spi.c \
../BSP/bsp_tim.c \
../BSP/bsp_usart.c \
../BSP/delay.c \
../BSP/sys.c 

OBJS += \
./BSP/bsp_adc.o \
./BSP/bsp_board.o \
./BSP/bsp_can.o \
./BSP/bsp_dac.o \
./BSP/bsp_gpio.o \
./BSP/bsp_i2c.o \
./BSP/bsp_nvic.o \
./BSP/bsp_rcc.o \
./BSP/bsp_spi.o \
./BSP/bsp_tim.o \
./BSP/bsp_usart.o \
./BSP/delay.o \
./BSP/sys.o 

C_DEPS += \
./BSP/bsp_adc.d \
./BSP/bsp_board.d \
./BSP/bsp_can.d \
./BSP/bsp_dac.d \
./BSP/bsp_gpio.d \
./BSP/bsp_i2c.d \
./BSP/bsp_nvic.d \
./BSP/bsp_rcc.d \
./BSP/bsp_spi.d \
./BSP/bsp_tim.d \
./BSP/bsp_usart.d \
./BSP/delay.d \
./BSP/sys.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/%.o BSP/%.su BSP/%.cyclo: ../BSP/%.c BSP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103ZETx -DUSE_STDPERIPH_DRIVER -DSTM32F10X_HD -c -I../Inc -I../Libraries/CMSIS/CM3/CoreSupport -I../Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x -I../Libraries/STM32F10x_StdPeriph_Driver/inc -I../BSP -I../Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BSP

clean-BSP:
	-$(RM) ./BSP/bsp_adc.cyclo ./BSP/bsp_adc.d ./BSP/bsp_adc.o ./BSP/bsp_adc.su ./BSP/bsp_board.cyclo ./BSP/bsp_board.d ./BSP/bsp_board.o ./BSP/bsp_board.su ./BSP/bsp_can.cyclo ./BSP/bsp_can.d ./BSP/bsp_can.o ./BSP/bsp_can.su ./BSP/bsp_dac.cyclo ./BSP/bsp_dac.d ./BSP/bsp_dac.o ./BSP/bsp_dac.su ./BSP/bsp_gpio.cyclo ./BSP/bsp_gpio.d ./BSP/bsp_gpio.o ./BSP/bsp_gpio.su ./BSP/bsp_i2c.cyclo ./BSP/bsp_i2c.d ./BSP/bsp_i2c.o ./BSP/bsp_i2c.su ./BSP/bsp_nvic.cyclo ./BSP/bsp_nvic.d ./BSP/bsp_nvic.o ./BSP/bsp_nvic.su ./BSP/bsp_rcc.cyclo ./BSP/bsp_rcc.d ./BSP/bsp_rcc.o ./BSP/bsp_rcc.su ./BSP/bsp_spi.cyclo ./BSP/bsp_spi.d ./BSP/bsp_spi.o ./BSP/bsp_spi.su ./BSP/bsp_tim.cyclo ./BSP/bsp_tim.d ./BSP/bsp_tim.o ./BSP/bsp_tim.su ./BSP/bsp_usart.cyclo ./BSP/bsp_usart.d ./BSP/bsp_usart.o ./BSP/bsp_usart.su ./BSP/delay.cyclo ./BSP/delay.d ./BSP/delay.o ./BSP/delay.su ./BSP/sys.cyclo ./BSP/sys.d ./BSP/sys.o ./BSP/sys.su

.PHONY: clean-BSP

