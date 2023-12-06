################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c \
C:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c \
C:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Src/usbd_hid.c \
C:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c 

OBJS += \
./Middlewares/USB_Device_Library/usbd_core.o \
./Middlewares/USB_Device_Library/usbd_ctlreq.o \
./Middlewares/USB_Device_Library/usbd_hid.o \
./Middlewares/USB_Device_Library/usbd_ioreq.o 

C_DEPS += \
./Middlewares/USB_Device_Library/usbd_core.d \
./Middlewares/USB_Device_Library/usbd_ctlreq.d \
./Middlewares/USB_Device_Library/usbd_hid.d \
./Middlewares/USB_Device_Library/usbd_ioreq.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/USB_Device_Library/usbd_core.o: C:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c Middlewares/USB_Device_Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I"C:/Users/LENOVO/STM32CubeIDE/workspace_1.13.0/767_SPI_ILI9341_2/Drivers/ILI9341" -I../USB_DEVICE/App -I../USB_DEVICE/Target -IC:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -IC:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -IC:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/USB_Device_Library/usbd_ctlreq.o: C:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c Middlewares/USB_Device_Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I"C:/Users/LENOVO/STM32CubeIDE/workspace_1.13.0/767_SPI_ILI9341_2/Drivers/ILI9341" -I../USB_DEVICE/App -I../USB_DEVICE/Target -IC:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -IC:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -IC:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/USB_Device_Library/usbd_hid.o: C:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Src/usbd_hid.c Middlewares/USB_Device_Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I"C:/Users/LENOVO/STM32CubeIDE/workspace_1.13.0/767_SPI_ILI9341_2/Drivers/ILI9341" -I../USB_DEVICE/App -I../USB_DEVICE/Target -IC:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -IC:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -IC:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/USB_Device_Library/usbd_ioreq.o: C:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c Middlewares/USB_Device_Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I"C:/Users/LENOVO/STM32CubeIDE/workspace_1.13.0/767_SPI_ILI9341_2/Drivers/ILI9341" -I../USB_DEVICE/App -I../USB_DEVICE/Target -IC:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -IC:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -IC:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/LENOVO/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.1/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-USB_Device_Library

clean-Middlewares-2f-USB_Device_Library:
	-$(RM) ./Middlewares/USB_Device_Library/usbd_core.cyclo ./Middlewares/USB_Device_Library/usbd_core.d ./Middlewares/USB_Device_Library/usbd_core.o ./Middlewares/USB_Device_Library/usbd_core.su ./Middlewares/USB_Device_Library/usbd_ctlreq.cyclo ./Middlewares/USB_Device_Library/usbd_ctlreq.d ./Middlewares/USB_Device_Library/usbd_ctlreq.o ./Middlewares/USB_Device_Library/usbd_ctlreq.su ./Middlewares/USB_Device_Library/usbd_hid.cyclo ./Middlewares/USB_Device_Library/usbd_hid.d ./Middlewares/USB_Device_Library/usbd_hid.o ./Middlewares/USB_Device_Library/usbd_hid.su ./Middlewares/USB_Device_Library/usbd_ioreq.cyclo ./Middlewares/USB_Device_Library/usbd_ioreq.d ./Middlewares/USB_Device_Library/usbd_ioreq.o ./Middlewares/USB_Device_Library/usbd_ioreq.su

.PHONY: clean-Middlewares-2f-USB_Device_Library

