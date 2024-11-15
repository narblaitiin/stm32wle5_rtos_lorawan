# Code for 6Sens Project : LoRaWAN code for my own MAMWLExx (based on STM32WLEx) board

## Overview
This application contains example code to allow testing of LoRaWAN Network Application. This code also allows to test a physical link from the node to the gateway then from the gateway to TTN. The packets sent have the following characteristics:

    - Timer : packets every 30 minutes
    - Random value with the range min = 0 to max = 3 like values from ADC
    - Number of packets : 10
    - Number of nodes : 5

LoRaWAN Device EUI, Join EUI and Application Key should be entered into the app_lorawan.h file prior to compiling. The example stores the DevNonce in NVS (Non-volatile Storage) as per LoRaWAN 1.0.4 Specifications. The version of Zephyr RTOS used is the version v3.6.0.

**Board used** : Original MAMWLExx board, powered by battery/solar panel. (see 6sens_project_stm32wl repository/hardware part, for more information.)

## Building and Running
The following commands clean build folder, build and flash the sample:

**Command to use**

west build -p always -b stm32wl_dw1000_iot_board applications/stm32wle5_rtos_lorawan

west flash --runner pyocd