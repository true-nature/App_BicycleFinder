EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:TWE-Lite
LIBS:BicycleFinder-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "8 jan 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L BATTERY BT1
U 1 1 5493D0B5
P 2550 2100
F 0 "BT1" H 2550 2300 50  0000 C CNN
F 1 "3V" H 2550 1910 50  0000 C CNN
F 2 "" H 2550 2100 60  0000 C CNN
F 3 "" H 2550 2100 60  0000 C CNN
	1    2550 2100
	0    1    1    0   
$EndComp
Text Label 9100 4000 0    60   ~ 0
Vcc
Text Label 3800 5400 0    60   Italic 0
GND
$Comp
L GND #PWR01
U 1 1 549A463E
P 7300 6050
F 0 "#PWR01" H 7300 6050 30  0001 C CNN
F 1 "GND" H 7300 5980 30  0001 C CNN
F 2 "" H 7300 6050 60  0000 C CNN
F 3 "" H 7300 6050 60  0000 C CNN
	1    7300 6050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 549A464D
P 2550 2550
F 0 "#PWR02" H 2550 2550 30  0001 C CNN
F 1 "GND" H 2550 2480 30  0001 C CNN
F 2 "" H 2550 2550 60  0000 C CNN
F 3 "" H 2550 2550 60  0000 C CNN
	1    2550 2550
	1    0    0    -1  
$EndComp
$Comp
L CONN_14 P1
U 1 1 549BABE9
P 3350 4750
F 0 "P1" V 3320 4750 60  0000 C CNN
F 1 "CONN_14" V 3430 4750 60  0000 C CNN
F 2 "~" H 3350 4750 60  0000 C CNN
F 3 "~" H 3350 4750 60  0000 C CNN
	1    3350 4750
	-1   0    0    -1  
$EndComp
$Comp
L CONN_14 P2
U 1 1 549BADEF
P 9750 4650
F 0 "P2" V 9720 4650 60  0000 C CNN
F 1 "CONN_14" V 9830 4650 60  0000 C CNN
F 2 "~" H 9750 4650 60  0000 C CNN
F 3 "~" H 9750 4650 60  0000 C CNN
	1    9750 4650
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW1
U 1 1 549BC4AC
P 8600 3100
F 0 "SW1" H 8750 3210 50  0000 C CNN
F 1 "SW_PUSH" H 8600 3020 50  0000 C CNN
F 2 "~" H 8600 3100 60  0000 C CNN
F 3 "~" H 8600 3100 60  0000 C CNN
	1    8600 3100
	1    0    0    -1  
$EndComp
$Comp
L CP1 C1
U 1 1 549BC5A8
P 3750 3550
F 0 "C1" H 3800 3650 50  0000 L CNN
F 1 "1F" H 3800 3450 50  0000 L CNN
F 2 "~" H 3750 3550 60  0000 C CNN
F 3 "~" H 3750 3550 60  0000 C CNN
	1    3750 3550
	1    0    0    -1  
$EndComp
Text Label 3800 4200 0    60   ~ 0
SCL
Text Label 3800 4100 0    60   ~ 0
GND
Text Label 3800 4300 0    60   ~ 0
TXD
Text Label 3800 4400 0    60   ~ 0
PWM1
Text Label 3800 4500 0    60   ~ 0
DO1
Text Label 3800 4600 0    60   ~ 0
PWM2
Text Label 3800 4700 0    60   ~ 0
PWM3
Text Label 3800 4800 0    60   ~ 0
DO2
Text Label 3800 4900 0    60   ~ 0
DO3
Text Label 3800 5000 0    60   ~ 0
RXD
Text Label 3800 5100 0    60   ~ 0
PWM4
Text Label 3800 5200 0    60   ~ 0
DO4
Text Label 3800 5300 0    60   ~ 0
M1
Text Label 9100 4100 0    60   ~ 0
M3
Text Label 9100 4200 0    60   ~ 0
M2
Text Label 9100 4300 0    60   ~ 0
AI4
Text Label 9100 4400 0    60   ~ 0
AI3
Text Label 9100 4500 0    60   ~ 0
AI2
Text Label 9100 4600 0    60   ~ 0
AI1
Text Label 9100 4700 0    60   ~ 0
RST
Text Label 9100 4800 0    60   ~ 0
BPS
Text Label 9100 4900 0    60   ~ 0
SDA
Text Label 9100 5000 0    60   ~ 0
DI4
Text Label 9100 5100 0    60   ~ 0
DI3
Text Label 9100 5200 0    60   ~ 0
DI2
Text Label 9100 5300 0    60   ~ 0
DI1
NoConn ~ 5400 2000
NoConn ~ 5500 2000
NoConn ~ 5600 2000
$Comp
L LITE_LITE U1
U 1 1 549BBD70
P 5700 3100
F 0 "U1" H 5700 3100 10  0001 C CNN
F 1 "LITE_LITE" H 5700 3100 60  0001 C CNN
F 2 "~" H 5700 3100 60  0000 C CNN
F 3 "~" H 5700 3100 60  0000 C CNN
	1    5700 3100
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 54ACCB34
P 3250 1700
F 0 "R1" V 3330 1700 40  0000 C CNN
F 1 "1k" V 3257 1701 40  0000 C CNN
F 2 "~" V 3180 1700 30  0000 C CNN
F 3 "~" H 3250 1700 30  0000 C CNN
	1    3250 1700
	0    -1   -1   0   
$EndComp
$Comp
L PWR_FLAG #FLG03
U 1 1 54ACCF53
P 3750 1600
F 0 "#FLG03" H 3750 1695 30  0001 C CNN
F 1 "PWR_FLAG" H 3750 1780 30  0000 C CNN
F 2 "" H 3750 1600 60  0000 C CNN
F 3 "" H 3750 1600 60  0000 C CNN
	1    3750 1600
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG04
U 1 1 54ACCF62
P 2850 2400
F 0 "#FLG04" H 2850 2495 30  0001 C CNN
F 1 "PWR_FLAG" H 2850 2580 30  0000 C CNN
F 2 "" H 2850 2400 60  0000 C CNN
F 3 "" H 2850 2400 60  0000 C CNN
	1    2850 2400
	1    0    0    -1  
$EndComp
$Comp
L CONN_7 P3
U 1 1 54AD18E9
P 5000 6150
F 0 "P3" V 4970 6150 60  0000 C CNN
F 1 "CONN_7" V 5070 6150 60  0000 C CNN
F 2 "~" H 5000 6150 60  0000 C CNN
F 3 "~" H 5000 6150 60  0000 C CNN
	1    5000 6150
	0    1    1    0   
$EndComp
Connection ~ 7100 4700
Wire Wire Line
	5200 5500 5200 5800
Connection ~ 8000 4000
Connection ~ 4900 4300
Wire Wire Line
	4900 5800 4900 4300
Connection ~ 4800 5400
Wire Wire Line
	4800 5800 4800 5400
Connection ~ 4700 5300
Wire Wire Line
	4700 5800 4700 5300
Wire Wire Line
	2550 2400 2850 2400
Wire Wire Line
	2550 2550 2550 2400
Connection ~ 3750 4100
Wire Wire Line
	3750 3750 3750 4100
Connection ~ 3750 3100
Wire Wire Line
	2550 1700 2550 1800
Connection ~ 8900 5300
Wire Wire Line
	8900 3100 8900 5300
Connection ~ 7300 3100
Wire Wire Line
	4000 1800 4000 4100
Wire Wire Line
	5800 1800 4000 1800
Wire Wire Line
	5800 2000 5800 1800
Connection ~ 3750 1700
Wire Wire Line
	8000 4000 9400 4000
Wire Wire Line
	3500 1700 8000 1700
Wire Wire Line
	7900 4100 9400 4100
Wire Wire Line
	7900 1800 7900 4100
Wire Wire Line
	5900 1800 7900 1800
Wire Wire Line
	5900 2000 5900 1800
Wire Wire Line
	7800 4200 9400 4200
Wire Wire Line
	7800 1900 7800 4200
Wire Wire Line
	6000 1900 7800 1900
Wire Wire Line
	6000 2000 6000 1900
Wire Wire Line
	7700 4300 9400 4300
Wire Wire Line
	7700 2000 7700 4300
Wire Wire Line
	6100 2000 7700 2000
Wire Wire Line
	7600 4400 9400 4400
Wire Wire Line
	7600 2900 7600 4400
Wire Wire Line
	6800 2900 7600 2900
Wire Wire Line
	7500 4500 9400 4500
Wire Wire Line
	7500 2700 7500 4500
Wire Wire Line
	6800 2700 7500 2700
Wire Wire Line
	7400 4600 9400 4600
Wire Wire Line
	7400 2800 7400 4600
Wire Wire Line
	6800 2800 7400 2800
Wire Wire Line
	7100 4700 9400 4700
Wire Wire Line
	7000 4800 9400 4800
Wire Wire Line
	7000 3200 7000 4800
Wire Wire Line
	6800 3200 7000 3200
Wire Wire Line
	7100 3000 6800 3000
Wire Wire Line
	6800 4900 9400 4900
Wire Wire Line
	6800 3400 6800 4900
Wire Wire Line
	6900 5000 9400 5000
Wire Wire Line
	6900 3300 6900 5000
Wire Wire Line
	6800 3300 6900 3300
Wire Wire Line
	6100 5100 9400 5100
Wire Wire Line
	6100 4100 6100 5100
Wire Wire Line
	6000 5200 9400 5200
Wire Wire Line
	6000 4100 6000 5200
Wire Wire Line
	5800 5300 9400 5300
Wire Wire Line
	5800 4100 5800 5300
Wire Wire Line
	4000 4100 3700 4100
Wire Wire Line
	5900 4200 5900 4100
Wire Wire Line
	3700 4200 5900 4200
Wire Wire Line
	5400 4300 5400 4100
Wire Wire Line
	3700 4300 5400 4300
Wire Wire Line
	4100 3300 4700 3300
Wire Wire Line
	4100 4400 4100 3300
Wire Wire Line
	3700 4400 4100 4400
Wire Wire Line
	4200 4500 3700 4500
Wire Wire Line
	4200 2900 4200 4500
Wire Wire Line
	4700 2900 4200 2900
Wire Wire Line
	4300 4600 3700 4600
Wire Wire Line
	4300 2700 4300 4600
Wire Wire Line
	4700 2700 4300 2700
Wire Wire Line
	3700 4700 5000 4700
Wire Wire Line
	4500 4800 3700 4800
Wire Wire Line
	4600 4900 3700 4900
Wire Wire Line
	3700 5000 5100 5000
Wire Wire Line
	3700 5100 5500 5100
Wire Wire Line
	3700 5200 5600 5200
Wire Wire Line
	3700 5300 5700 5300
Wire Wire Line
	3700 5400 7300 5400
Wire Wire Line
	4400 2800 4400 4700
Wire Wire Line
	4700 2800 4400 2800
Wire Wire Line
	4500 3000 4500 4800
Wire Wire Line
	4700 3000 4500 3000
Wire Wire Line
	4600 3200 4600 4900
Wire Wire Line
	4600 3200 4700 3200
Wire Wire Line
	4700 5000 4700 3400
Wire Wire Line
	6800 3100 8300 3100
Wire Wire Line
	5500 5100 5500 4100
Wire Wire Line
	5700 5300 5700 4100
Wire Wire Line
	7300 3100 7300 6050
Connection ~ 7300 5400
Wire Wire Line
	3750 3100 4700 3100
Wire Wire Line
	5100 5000 5100 5800
Connection ~ 4700 5000
Wire Wire Line
	5000 4700 5000 5800
Connection ~ 4400 4700
Wire Wire Line
	5300 5800 5300 5700
Wire Wire Line
	5300 5700 8000 5700
Wire Wire Line
	3750 1600 3750 3350
Wire Wire Line
	3000 1700 2550 1700
$Comp
L LED D1
U 1 1 54AD1F8E
P 6000 5600
F 0 "D1" H 6000 5700 50  0000 C CNN
F 1 "LED" H 6000 5500 50  0000 C CNN
F 2 "~" H 6000 5600 60  0000 C CNN
F 3 "~" H 6000 5600 60  0000 C CNN
	1    6000 5600
	-1   0    0    1   
$EndComp
Connection ~ 5600 5200
Wire Wire Line
	7100 3000 7100 5500
Wire Wire Line
	7100 5500 5200 5500
Wire Wire Line
	5600 4100 5600 5600
Wire Wire Line
	5600 5600 5800 5600
Connection ~ 8000 5600
Wire Wire Line
	8000 5700 8000 1700
Text Label 2600 1700 0    60   ~ 0
3V
$Comp
L R R2
U 1 1 54AE44D9
P 6450 5600
F 0 "R2" V 6530 5600 40  0000 C CNN
F 1 "1k" V 6457 5601 40  0000 C CNN
F 2 "~" V 6380 5600 30  0000 C CNN
F 3 "~" H 6450 5600 30  0000 C CNN
	1    6450 5600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6700 5600 8000 5600
$EndSCHEMATC
