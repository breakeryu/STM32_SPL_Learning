﻿param([String]$debugfile = "");

# This powershell file has been generated by the IAR Embedded Workbench
# C - SPY Debugger, as an aid to preparing a command line for running
# the cspybat command line utility using the appropriate settings.
#
# Note that this file is generated every time a new debug session
# is initialized, so you may want to move or rename the file before
# making changes.
#
# You can launch cspybat by typing Powershell.exe -File followed by the name of this batch file, followed
# by the name of the debug file (usually an ELF / DWARF or UBROF file).
#
# Read about available command line parameters in the C - SPY Debugging
# Guide. Hints about additional command line parameters that may be
# useful in specific cases :
#   --download_only   Downloads a code image without starting a debug
#                     session afterwards.
#   --silent          Omits the sign - on message.
#   --timeout         Limits the maximum allowed execution time.
#


if ($debugfile -eq "")
{
& "E:\ProgramFiles\IAR Systems\Embedded Workbench 8.2\common\bin\cspybat" -f "E:\Users\Learning\STM32_SPL_Learning\STM32F10X\02_Library_STM32\en.stm32cubef1\STM32Cube_FW_F1_V1.8.0\Projects\STM32F103RB-Nucleo\Examples\UART\UART_TwoBoards_ComPolling\EWARM\settings\Project.STM32F103RB_Nucleo.general.xcl" --backend -f "E:\Users\Learning\STM32_SPL_Learning\STM32F10X\02_Library_STM32\en.stm32cubef1\STM32Cube_FW_F1_V1.8.0\Projects\STM32F103RB-Nucleo\Examples\UART\UART_TwoBoards_ComPolling\EWARM\settings\Project.STM32F103RB_Nucleo.driver.xcl" 
}
else
{
& "E:\ProgramFiles\IAR Systems\Embedded Workbench 8.2\common\bin\cspybat" -f "E:\Users\Learning\STM32_SPL_Learning\STM32F10X\02_Library_STM32\en.stm32cubef1\STM32Cube_FW_F1_V1.8.0\Projects\STM32F103RB-Nucleo\Examples\UART\UART_TwoBoards_ComPolling\EWARM\settings\Project.STM32F103RB_Nucleo.general.xcl" --debug_file=$debugfile --backend -f "E:\Users\Learning\STM32_SPL_Learning\STM32F10X\02_Library_STM32\en.stm32cubef1\STM32Cube_FW_F1_V1.8.0\Projects\STM32F103RB-Nucleo\Examples\UART\UART_TwoBoards_ComPolling\EWARM\settings\Project.STM32F103RB_Nucleo.driver.xcl" 
}