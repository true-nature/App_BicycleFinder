#!/bin/sh

make TWE_CHIP_MODEL=JN5148 APP_UART_CONFIG=CONFIG_NORMAL clean 
make TWE_CHIP_MODEL=JN5148 APP_UART_CONFIG=CONFIG_NORMAL all -j 4
make TWE_CHIP_MODEL=JN5164 APP_UART_CONFIG=CONFIG_NORMAL clean
make TWE_CHIP_MODEL=JN5164 APP_UART_CONFIG=CONFIG_NORMAL all -j 4
make TWE_CHIP_MODEL=JN5164 APP_UART_CONFIG=CONFIG_NORMAL TWE_DEVKIT=002L clean 
make TWE_CHIP_MODEL=JN5164 APP_UART_CONFIG=CONFIG_NORMAL TWE_DEVKIT=002L all -j 4
make TWE_CHIP_MODEL=JN5164 APP_UART_CONFIG=CONFIG_NORMAL TWE_DEVKIT=TOCOSTICK clean 
make TWE_CHIP_MODEL=JN5164 APP_UART_CONFIG=CONFIG_NORMAL TWE_DEVKIT=TOCOSTICK all -j 4