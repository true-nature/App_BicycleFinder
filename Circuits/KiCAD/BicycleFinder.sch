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
Date "25 dec 2014"
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
P 1900 1900
F 0 "BT1" H 1900 2100 50  0000 C CNN
F 1 "3V" H 1900 1710 50  0000 C CNN
F 2 "" H 1900 1900 60  0000 C CNN
F 3 "" H 1900 1900 60  0000 C CNN
	1    1900 1900
	0    1    1    0   
$EndComp
$Comp
L VCC #PWR01
U 1 1 549A285E
P 3750 1450
F 0 "#PWR01" H 3750 1550 30  0001 C CNN
F 1 "VCC" H 3750 1550 30  0000 C CNN
F 2 "" H 3750 1450 60  0000 C CNN
F 3 "" H 3750 1450 60  0000 C CNN
	1    3750 1450
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR02
U 1 1 549A2873
P 1900 1350
F 0 "#PWR02" H 1900 1450 30  0001 C CNN
F 1 "VCC" H 1900 1450 30  0000 C CNN
F 2 "" H 1900 1350 60  0000 C CNN
F 3 "" H 1900 1350 60  0000 C CNN
	1    1900 1350
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG03
U 1 1 549A37E5
P 2150 2300
F 0 "#FLG03" H 2150 2395 30  0001 C CNN
F 1 "PWR_FLAG" H 2150 2480 30  0000 C CNN
F 2 "" H 2150 2300 60  0000 C CNN
F 3 "" H 2150 2300 60  0000 C CNN
	1    2150 2300
	1    0    0    -1  
$EndComp
Text Label 9100 4000 0    60   ~ 0
Vcc
Text Label 3800 5400 0    60   Italic 0
GND
$Comp
L PWR_FLAG #FLG04
U 1 1 549A4528
P 2050 1350
F 0 "#FLG04" H 2050 1445 30  0001 C CNN
F 1 "PWR_FLAG" H 2050 1530 30  0000 C CNN
F 2 "" H 2050 1350 60  0000 C CNN
F 3 "" H 2050 1350 60  0000 C CNN
	1    2050 1350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 549A463E
P 7300 5800
F 0 "#PWR05" H 7300 5800 30  0001 C CNN
F 1 "GND" H 7300 5730 30  0001 C CNN
F 2 "" H 7300 5800 60  0000 C CNN
F 3 "" H 7300 5800 60  0000 C CNN
	1    7300 5800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 549A464D
P 1900 2550
F 0 "#PWR06" H 1900 2550 30  0001 C CNN
F 1 "GND" H 1900 2480 30  0001 C CNN
F 2 "" H 1900 2550 60  0000 C CNN
F 3 "" H 1900 2550 60  0000 C CNN
	1    1900 2550
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
Wire Wire Line
	1900 1350 1900 1600
Wire Wire Line
	3750 1450 3750 3100
Wire Wire Line
	3750 3100 4700 3100
Wire Wire Line
	1900 2200 1900 2550
Wire Wire Line
	2150 2400 2150 2300
Wire Wire Line
	1250 2400 2150 2400
Wire Wire Line
	1250 1350 2050 1350
Connection ~ 1900 2400
Connection ~ 1900 1350
Connection ~ 7300 5400
Wire Wire Line
	7300 3100 7300 5850
Wire Wire Line
	5700 5300 5700 4100
Wire Wire Line
	5600 5200 5600 4100
Wire Wire Line
	5500 5100 5500 4100
Wire Wire Line
	6800 3100 8300 3100
Wire Wire Line
	4700 5000 4700 3400
Wire Wire Line
	4600 3200 4700 3200
Wire Wire Line
	4600 3200 4600 4900
Wire Wire Line
	4700 3000 4500 3000
Wire Wire Line
	4500 3000 4500 4800
Wire Wire Line
	4700 2800 4400 2800
Wire Wire Line
	4400 2800 4400 4700
Wire Wire Line
	3700 5400 7300 5400
Wire Wire Line
	3700 5300 5700 5300
Wire Wire Line
	3700 5200 5600 5200
Wire Wire Line
	3700 5100 5500 5100
Wire Wire Line
	3700 5000 4700 5000
Wire Wire Line
	4600 4900 3700 4900
Wire Wire Line
	4500 4800 3700 4800
Wire Wire Line
	4400 4700 3700 4700
Wire Wire Line
	4700 2700 4300 2700
Wire Wire Line
	4300 2700 4300 4600
Wire Wire Line
	4300 4600 3700 4600
Wire Wire Line
	4700 2900 4200 2900
Wire Wire Line
	4200 2900 4200 4500
Wire Wire Line
	4200 4500 3700 4500
Wire Wire Line
	3700 4400 4100 4400
Wire Wire Line
	4100 4400 4100 3300
Wire Wire Line
	4100 3300 4700 3300
Wire Wire Line
	3700 4300 5400 4300
Wire Wire Line
	5400 4300 5400 4100
Wire Wire Line
	3700 4200 5900 4200
Wire Wire Line
	5900 4200 5900 4100
Wire Wire Line
	3700 4100 4000 4100
Wire Wire Line
	5800 4100 5800 5300
Wire Wire Line
	5800 5300 9400 5300
Wire Wire Line
	6000 4100 6000 5200
Wire Wire Line
	6000 5200 9400 5200
Wire Wire Line
	6100 4100 6100 5100
Wire Wire Line
	6100 5100 9400 5100
Wire Wire Line
	6800 3300 6900 3300
Wire Wire Line
	6900 3300 6900 5000
Wire Wire Line
	6900 5000 9400 5000
Wire Wire Line
	6800 3400 6800 3400
Wire Wire Line
	6800 3400 6800 4900
Wire Wire Line
	6800 4900 9400 4900
Wire Wire Line
	6800 3000 7100 3000
Wire Wire Line
	6800 3200 7000 3200
Wire Wire Line
	7000 3200 7000 4800
Wire Wire Line
	7000 4800 9400 4800
Wire Wire Line
	7100 3000 7100 4700
Wire Wire Line
	7100 4700 9400 4700
Wire Wire Line
	6800 2800 7400 2800
Wire Wire Line
	7400 2800 7400 4600
Wire Wire Line
	7400 4600 9400 4600
Wire Wire Line
	6800 2700 7500 2700
Wire Wire Line
	7500 2700 7500 4500
Wire Wire Line
	7500 4500 9400 4500
Wire Wire Line
	6800 2900 7600 2900
Wire Wire Line
	7600 2900 7600 4400
Wire Wire Line
	7600 4400 9400 4400
Wire Wire Line
	6100 2000 7700 2000
Wire Wire Line
	7700 2000 7700 4300
Wire Wire Line
	7700 4300 9400 4300
Wire Wire Line
	6000 2000 6000 1900
Wire Wire Line
	6000 1900 7800 1900
Wire Wire Line
	7800 1900 7800 4200
Wire Wire Line
	7800 4200 9400 4200
Wire Wire Line
	5900 2000 5900 1800
Wire Wire Line
	5900 1800 7900 1800
Wire Wire Line
	7900 1800 7900 4100
Wire Wire Line
	7900 4100 9400 4100
Wire Wire Line
	3750 1700 8000 1700
Wire Wire Line
	8000 1700 8000 4000
Wire Wire Line
	8000 4000 9400 4000
Connection ~ 3750 1700
Wire Wire Line
	5800 2000 5800 1800
Wire Wire Line
	5800 1800 4000 1800
Wire Wire Line
	4000 1800 4000 4100
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
Connection ~ 7300 3100
Wire Wire Line
	8900 3100 8900 5300
Connection ~ 8900 5300
$Comp
L CP1 C1
U 1 1 549BC5A8
P 1250 1900
F 0 "C1" H 1300 2000 50  0000 L CNN
F 1 "1F" H 1300 1800 50  0000 L CNN
F 2 "~" H 1250 1900 60  0000 C CNN
F 3 "~" H 1250 1900 60  0000 C CNN
	1    1250 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 1350 1250 1700
Wire Wire Line
	1250 2100 1250 2400
Text Label 3800 4200 0    60   ~ 0
SCL
Text Label 3800 4100 0    60   ~ 0
GND
Text Label 3800 4300 0    60   ~ 0
RXD
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
TX
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
F 1 "LITE_LITE" H 5700 3100 0   0001 C CNN
F 2 "~" H 5700 3100 60  0000 C CNN
F 3 "~" H 5700 3100 60  0000 C CNN
	1    5700 3100
	1    0    0    -1  
$EndComp
$EndSCHEMATC
