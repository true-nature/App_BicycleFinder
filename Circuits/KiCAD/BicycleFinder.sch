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
Date "13 jan 2015"
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
P 7200 6050
F 0 "#PWR01" H 7200 6050 30  0001 C CNN
F 1 "GND" H 7200 5980 30  0001 C CNN
F 2 "" H 7200 6050 60  0000 C CNN
F 3 "" H 7200 6050 60  0000 C CNN
	1    7200 6050
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
P 6250 4500
F 0 "SW1" H 6400 4610 50  0000 C CNN
F 1 "SW_PUSH" H 6250 4420 50  0000 C CNN
F 2 "~" H 6250 4500 60  0000 C CNN
F 3 "~" H 6250 4500 60  0000 C CNN
	1    6250 4500
	1    0    0    -1  
$EndComp
$Comp
L CP1 C1
U 1 1 549BC5A8
P 7200 2200
F 0 "C1" H 7250 2300 50  0000 L CNN
F 1 "1F" H 7250 2100 50  0000 L CNN
F 2 "~" H 7200 2200 60  0000 C CNN
F 3 "~" H 7200 2200 60  0000 C CNN
	1    7200 2200
	1    0    0    -1  
$EndComp
NoConn ~ 5400 2000
NoConn ~ 5500 2000
NoConn ~ 5600 2000
$Comp
L R R1
U 1 1 54ACCB34
P 3250 1700
F 0 "R1" V 3330 1700 40  0000 C CNN
F 1 "750" V 3257 1701 40  0000 C CNN
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
L CONN_7 P1
U 1 1 54AD18E9
P 5000 6150
F 0 "P1" V 4970 6150 60  0000 C CNN
F 1 "CONN_7" V 5070 6150 60  0000 C CNN
F 2 "~" H 5000 6150 60  0000 C CNN
F 3 "~" H 5000 6150 60  0000 C CNN
	1    5000 6150
	0    1    1    0   
$EndComp
Wire Wire Line
	5200 5500 5200 5800
Wire Wire Line
	4900 5800 4900 4300
Wire Wire Line
	4800 5800 4800 5400
Wire Wire Line
	4700 5800 4700 5300
Wire Wire Line
	2550 2400 2850 2400
Wire Wire Line
	2550 2550 2550 2400
Wire Wire Line
	2550 1700 2550 1800
Connection ~ 3750 1700
Wire Wire Line
	3500 1700 8000 1700
Wire Wire Line
	7100 3000 6800 3000
Wire Wire Line
	5400 4300 5400 4100
Wire Wire Line
	4400 2800 4400 4700
Wire Wire Line
	4700 2800 4400 2800
Wire Wire Line
	4700 5000 4700 3400
Wire Wire Line
	5700 5300 5700 4100
Wire Wire Line
	3750 3100 4700 3100
Wire Wire Line
	5100 5000 5100 5800
Wire Wire Line
	5000 4700 5000 5800
Wire Wire Line
	5300 5800 5300 5700
Wire Wire Line
	5300 5700 8000 5700
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
Wire Wire Line
	7200 2400 7200 6050
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
F 1 "750" V 6457 5601 40  0000 C CNN
F 2 "~" V 6380 5600 30  0000 C CNN
F 3 "~" H 6450 5600 30  0000 C CNN
	1    6450 5600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6700 5600 8000 5600
Wire Wire Line
	5800 4100 5800 4500
Wire Wire Line
	5800 4500 5950 4500
Wire Wire Line
	6900 3100 6900 4500
Wire Wire Line
	6800 3100 7200 3100
Wire Wire Line
	6900 4500 6550 4500
Wire Wire Line
	7200 2000 7200 1700
Wire Wire Line
	4700 5000 5100 5000
Wire Wire Line
	3750 3100 3750 1600
Wire Wire Line
	4400 4700 5000 4700
Wire Wire Line
	4900 4300 5400 4300
Wire Wire Line
	4700 5300 5700 5300
Wire Wire Line
	4800 5400 7200 5400
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
NoConn ~ 4700 2700
NoConn ~ 4700 2900
NoConn ~ 4700 3000
NoConn ~ 4700 3200
NoConn ~ 4700 3300
NoConn ~ 5500 4100
NoConn ~ 5900 4100
NoConn ~ 6000 4100
NoConn ~ 6100 4100
NoConn ~ 6800 3400
NoConn ~ 6800 3300
NoConn ~ 6800 3200
NoConn ~ 5800 2000
NoConn ~ 5900 2000
NoConn ~ 6000 2000
Wire Wire Line
	7100 3000 7100 5500
Connection ~ 6900 3100
Connection ~ 7200 3100
Connection ~ 7200 1700
NoConn ~ 6800 2900
NoConn ~ 6800 2800
NoConn ~ 6800 2700
NoConn ~ 6100 2000
Connection ~ 7200 5400
Text Label 4700 5800 1    60   ~ 0
M1
Text Label 5200 5800 1    60   ~ 0
RST
Text Label 5100 5800 1    60   ~ 0
RX
Text Label 5000 5800 1    60   ~ 0
PRG
Text Label 4900 5800 1    60   ~ 0
TX
Text Label 4800 5800 1    60   ~ 0
GND
Text Label 5300 5800 1    60   ~ 0
Vcc
Text Label 5800 4500 0    60   ~ 0
DI1
Text Label 5600 4800 1    60   ~ 0
DO4
$EndSCHEMATC
