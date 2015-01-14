EESchema Schematic File Version 2
LIBS:BicycleFinder
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
LIBS:BicycleFinder-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "14 jan 2015"
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
$Comp
L GND #PWR01
U 1 1 549A463E
P 8200 6050
F 0 "#PWR01" H 8200 6050 30  0001 C CNN
F 1 "GND" H 8200 5980 30  0001 C CNN
F 2 "" H 8200 6050 60  0000 C CNN
F 3 "" H 8200 6050 60  0000 C CNN
	1    8200 6050
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
L SW_PUSH SW1
U 1 1 549BC4AC
P 7250 4500
F 0 "SW1" H 7400 4610 50  0000 C CNN
F 1 "SW_PUSH" H 7250 4420 50  0000 C CNN
F 2 "~" H 7250 4500 60  0000 C CNN
F 3 "~" H 7250 4500 60  0000 C CNN
	1    7250 4500
	1    0    0    -1  
$EndComp
$Comp
L CP1 C1
U 1 1 549BC5A8
P 8200 2200
F 0 "C1" H 8250 2300 50  0000 L CNN
F 1 "1F" H 8250 2100 50  0000 L CNN
F 2 "~" H 8200 2200 60  0000 C CNN
F 3 "~" H 8200 2200 60  0000 C CNN
	1    8200 2200
	1    0    0    -1  
$EndComp
NoConn ~ 6400 2000
NoConn ~ 6500 2000
NoConn ~ 6600 2000
$Comp
L R R1
U 1 1 54ACCB34
P 3200 1700
F 0 "R1" V 3280 1700 40  0000 C CNN
F 1 "750" V 3207 1701 40  0000 C CNN
F 2 "~" V 3130 1700 30  0000 C CNN
F 3 "~" H 3200 1700 30  0000 C CNN
	1    3200 1700
	0    -1   -1   0   
$EndComp
$Comp
L PWR_FLAG #FLG03
U 1 1 54ACCF53
P 2550 1500
F 0 "#FLG03" H 2550 1595 30  0001 C CNN
F 1 "PWR_FLAG" H 2550 1680 30  0000 C CNN
F 2 "" H 2550 1500 60  0000 C CNN
F 3 "" H 2550 1500 60  0000 C CNN
	1    2550 1500
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
L CONN_7 P1
U 1 1 54AD18E9
P 6000 6150
F 0 "P1" V 5970 6150 60  0000 C CNN
F 1 "CONN_7" V 6070 6150 60  0000 C CNN
F 2 "~" H 6000 6150 60  0000 C CNN
F 3 "~" H 6000 6150 60  0000 C CNN
	1    6000 6150
	0    1    1    0   
$EndComp
$Comp
L LED D1
U 1 1 54AD1F8E
P 7000 4800
F 0 "D1" H 7000 4900 50  0000 C CNN
F 1 "LED" H 7000 4700 50  0000 C CNN
F 2 "~" H 7000 4800 60  0000 C CNN
F 3 "~" H 7000 4800 60  0000 C CNN
	1    7000 4800
	-1   0    0    1   
$EndComp
Text Label 2600 1700 0    60   ~ 0
3V
$Comp
L R R2
U 1 1 54AE44D9
P 7750 4800
F 0 "R2" V 7830 4800 40  0000 C CNN
F 1 "750" V 7757 4801 40  0000 C CNN
F 2 "~" V 7680 4800 30  0000 C CNN
F 3 "~" H 7750 4800 30  0000 C CNN
	1    7750 4800
	0    -1   -1   0   
$EndComp
$Comp
L LITE_LITE U1
U 1 1 549BBD70
P 6700 3100
F 0 "U1" H 6700 3100 10  0001 C CNN
F 1 "LITE_LITE" H 6700 3100 60  0001 C CNN
F 2 "~" H 6700 3100 60  0000 C CNN
F 3 "~" H 6700 3100 60  0000 C CNN
	1    6700 3100
	1    0    0    -1  
$EndComp
NoConn ~ 5700 2700
NoConn ~ 5700 2900
NoConn ~ 5700 3000
NoConn ~ 5700 3200
NoConn ~ 5700 3300
NoConn ~ 6500 4100
NoConn ~ 6900 4100
NoConn ~ 7000 4100
NoConn ~ 7100 4100
NoConn ~ 7800 3400
NoConn ~ 7800 3300
NoConn ~ 7800 3200
NoConn ~ 6800 2000
NoConn ~ 6900 2000
NoConn ~ 7000 2000
NoConn ~ 7800 2900
NoConn ~ 7800 2800
NoConn ~ 7800 2700
NoConn ~ 7100 2000
Text Label 5700 5800 1    60   ~ 0
M1
Text Label 6200 5800 1    60   ~ 0
RST
Text Label 6100 5800 1    60   ~ 0
RX
Text Label 6000 5800 1    60   ~ 0
PRG
Text Label 5900 5800 1    60   ~ 0
TX
Text Label 5800 5800 1    60   ~ 0
GND
Text Label 6300 5800 1    60   ~ 0
DC3V
Text Label 6800 4500 0    60   ~ 0
DI1
Text Label 6800 4800 2    60   ~ 0
K
$Comp
L HN2S01FU U2
U 1 1 54B6402D
P 4150 1700
F 0 "U2" H 4050 2250 60  0000 C CNN
F 1 "HN2S01FU" H 4150 2150 60  0000 C CNN
F 2 "" H 4150 1700 60  0000 C CNN
F 3 "" H 4150 1700 60  0000 C CNN
	1    4150 1700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6200 5500 6200 5800
Wire Wire Line
	5900 5800 5900 4300
Wire Wire Line
	5800 5800 5800 5400
Wire Wire Line
	5700 5800 5700 5300
Wire Wire Line
	2550 2400 2850 2400
Wire Wire Line
	2550 2550 2550 2400
Wire Wire Line
	2550 1500 2550 1800
Connection ~ 4750 1700
Wire Wire Line
	4550 1700 8500 1700
Wire Wire Line
	8100 3000 7800 3000
Wire Wire Line
	6400 4300 6400 4100
Wire Wire Line
	5400 2800 5400 4700
Wire Wire Line
	5700 2800 5400 2800
Wire Wire Line
	5700 5000 5700 3400
Wire Wire Line
	6700 5300 6700 4100
Wire Wire Line
	4750 3100 5700 3100
Wire Wire Line
	6100 5000 6100 5800
Wire Wire Line
	6000 4700 6000 5800
Wire Wire Line
	6300 5800 6300 5700
Wire Wire Line
	6300 5700 9000 5700
Wire Wire Line
	8200 2400 8200 6050
Wire Wire Line
	8100 5500 6200 5500
Wire Wire Line
	6600 4100 6600 4800
Wire Wire Line
	6600 4800 6800 4800
Wire Wire Line
	9000 5700 9000 1100
Wire Wire Line
	8000 4800 8500 4800
Wire Wire Line
	6800 4100 6800 4500
Wire Wire Line
	6800 4500 6950 4500
Wire Wire Line
	7900 3100 7900 4500
Wire Wire Line
	7800 3100 8200 3100
Wire Wire Line
	7900 4500 7550 4500
Wire Wire Line
	8200 2000 8200 1700
Wire Wire Line
	5700 5000 6100 5000
Wire Wire Line
	5400 4700 6000 4700
Wire Wire Line
	5900 4300 6400 4300
Wire Wire Line
	5700 5300 6700 5300
Wire Wire Line
	5800 5400 8200 5400
Wire Wire Line
	8100 3000 8100 5500
Connection ~ 7900 3100
Connection ~ 8200 3100
Connection ~ 8200 1700
Connection ~ 8200 5400
Connection ~ 2550 1700
Wire Wire Line
	3450 1700 3750 1700
Wire Wire Line
	2600 1700 2950 1700
Wire Wire Line
	2550 1700 2650 1700
Wire Wire Line
	3600 1950 3750 1950
Wire Wire Line
	3600 1950 3600 1700
Connection ~ 3600 1700
Wire Wire Line
	4750 1450 4750 3100
Connection ~ 4750 1950
Wire Wire Line
	8500 4800 8500 1700
Wire Wire Line
	4550 1950 4750 1950
Wire Wire Line
	4550 1450 4750 1450
Wire Wire Line
	3750 1450 3700 1450
Wire Wire Line
	3700 1450 3700 1100
Wire Wire Line
	3700 1100 9000 1100
Text Label 5500 1700 0    60   ~ 0
Vcc
Wire Wire Line
	7200 4800 7500 4800
Text Label 7250 4800 0    60   ~ 0
A
Text Label 3500 1700 0    60   ~ 0
CHG
$EndSCHEMATC
