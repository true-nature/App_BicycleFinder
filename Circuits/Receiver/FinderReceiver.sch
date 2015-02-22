EESchema Schematic File Version 2
LIBS:TWE-Lite
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
LIBS:FinderReceiver-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Bicycle Finder / Remote Commander"
Date "22 feb 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L TWE_LITE_SMD U1
U 1 1 54DE9748
P 5050 2550
F 0 "U1" H 5050 2450 50  0000 C CNN
F 1 "TWE_LITE_SMD" H 5050 3350 50  0000 C CNN
F 2 "MODULE" H 4800 1300 50  0001 C CNN
F 3 "DOCUMENTATION" H 5400 1300 50  0001 C CNN
	1    5050 2550
	1    0    0    -1  
$EndComp
$Comp
L BATTERY BT1
U 1 1 54DE9794
P 1200 1400
F 0 "BT1" H 1200 1600 50  0000 C CNN
F 1 "BATTERY" H 1200 1210 50  0000 C CNN
F 2 "~" H 1200 1400 60  0000 C CNN
F 3 "~" H 1200 1400 60  0000 C CNN
	1    1200 1400
	0    1    1    0   
$EndComp
$Comp
L SPEAKER SP2
U 1 1 54DE9911
P 7900 2150
F 0 "SP2" H 7800 2400 70  0000 C CNN
F 1 "PIEZO SP" H 8000 1750 70  0000 C CNN
F 2 "~" H 7900 2150 60  0000 C CNN
F 3 "~" H 7900 2150 60  0000 C CNN
	1    7900 2150
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR01
U 1 1 54DE9961
P 1200 950
F 0 "#PWR01" H 1200 1050 30  0001 C CNN
F 1 "VCC" H 1200 1050 30  0000 C CNN
F 2 "" H 1200 950 60  0000 C CNN
F 3 "" H 1200 950 60  0000 C CNN
	1    1200 950 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 54DE9970
P 1200 1850
F 0 "#PWR02" H 1200 1850 30  0001 C CNN
F 1 "GND" H 1200 1780 30  0001 C CNN
F 2 "" H 1200 1850 60  0000 C CNN
F 3 "" H 1200 1850 60  0000 C CNN
	1    1200 1850
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR03
U 1 1 54DE999E
P 6000 1550
F 0 "#PWR03" H 6000 1650 30  0001 C CNN
F 1 "VCC" H 6000 1650 30  0000 C CNN
F 2 "" H 6000 1550 60  0000 C CNN
F 3 "" H 6000 1550 60  0000 C CNN
	1    6000 1550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 54DE99AD
P 6100 3950
F 0 "#PWR04" H 6100 3950 30  0001 C CNN
F 1 "GND" H 6100 3880 30  0001 C CNN
F 2 "" H 6100 3950 60  0000 C CNN
F 3 "" H 6100 3950 60  0000 C CNN
	1    6100 3950
	1    0    0    -1  
$EndComp
$Comp
L LED LD2
U 1 1 54DE99E0
P 6700 2600
F 0 "LD2" H 6700 2700 50  0000 C CNN
F 1 "LED" H 6700 2500 50  0000 C CNN
F 2 "~" H 6700 2600 60  0000 C CNN
F 3 "~" H 6700 2600 60  0000 C CNN
	1    6700 2600
	-1   0    0    1   
$EndComp
$Comp
L R R1
U 1 1 54DE9A28
P 7000 2000
F 0 "R1" V 7080 2000 40  0000 C CNN
F 1 "680" V 7007 2001 40  0000 C CNN
F 2 "~" V 6930 2000 30  0000 C CNN
F 3 "~" H 7000 2000 30  0000 C CNN
	1    7000 2000
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR05
U 1 1 54DE9A46
P 7000 1550
F 0 "#PWR05" H 7000 1650 30  0001 C CNN
F 1 "VCC" H 7000 1650 30  0000 C CNN
F 2 "" H 7000 1550 60  0000 C CNN
F 3 "" H 7000 1550 60  0000 C CNN
	1    7000 1550
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR06
U 1 1 54DE9ABA
P 7300 1550
F 0 "#PWR06" H 7300 1650 30  0001 C CNN
F 1 "VCC" H 7300 1650 30  0000 C CNN
F 2 "" H 7300 1550 60  0000 C CNN
F 3 "" H 7300 1550 60  0000 C CNN
	1    7300 1550
	1    0    0    -1  
$EndComp
$Comp
L DIODE D1
U 1 1 54DE9AF2
P 7300 2300
F 0 "D1" H 7300 2400 40  0000 C CNN
F 1 "1N4148W" H 7300 2200 40  0000 C CNN
F 2 "~" H 7300 2300 60  0000 C CNN
F 3 "~" H 7300 2300 60  0000 C CNN
	1    7300 2300
	0    -1   -1   0   
$EndComp
$Comp
L R R2
U 1 1 54DE9B06
P 6950 3050
F 0 "R2" V 7030 3050 40  0000 C CNN
F 1 "1k" V 6957 3051 40  0000 C CNN
F 2 "~" V 6880 3050 30  0000 C CNN
F 3 "~" H 6950 3050 30  0000 C CNN
	1    6950 3050
	0    -1   -1   0   
$EndComp
$Comp
L WRITER P1
U 1 1 54DE9BCC
P 2900 2150
F 0 "P1" V 3000 2150 60  0000 C CNN
F 1 "WRITER" V 3100 2150 60  0000 C CNN
F 2 "~" H 2850 2150 60  0000 C CNN
F 3 "~" H 2850 2150 60  0000 C CNN
	1    2900 2150
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 54DE9C03
P 3400 2500
F 0 "#PWR07" H 3400 2500 30  0001 C CNN
F 1 "GND" H 3400 2430 30  0001 C CNN
F 2 "" H 3400 2500 60  0000 C CNN
F 3 "" H 3400 2500 60  0000 C CNN
	1    3400 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 950  1200 1100
Wire Wire Line
	1200 1700 1200 1850
Wire Wire Line
	5800 1900 6000 1900
Wire Wire Line
	6000 1900 6000 1550
Wire Wire Line
	5800 3200 6100 3200
Wire Wire Line
	6100 3200 6100 3950
Wire Wire Line
	5800 2600 6500 2600
Wire Wire Line
	7000 2600 6900 2600
Wire Wire Line
	7000 2250 7000 2600
Wire Wire Line
	7000 1550 7000 1750
Wire Wire Line
	7300 1550 7300 2100
Wire Wire Line
	7300 2050 7600 2050
Connection ~ 7300 2050
Wire Wire Line
	7600 2250 7550 2250
Wire Wire Line
	7550 3050 7550 1800
Wire Wire Line
	7200 3050 7550 3050
Wire Wire Line
	7300 2500 7300 3050
Connection ~ 7300 3050
Wire Wire Line
	6700 3050 5800 3050
Wire Wire Line
	3300 2300 3400 2300
Wire Wire Line
	3400 2300 3400 2500
Wire Wire Line
	3300 1900 3550 1900
Wire Wire Line
	3550 2500 4300 2500
Wire Wire Line
	3300 2000 3650 2000
Wire Wire Line
	3650 2000 3650 2250
Wire Wire Line
	3650 2250 4300 2250
Wire Wire Line
	3300 2200 3450 2200
Wire Wire Line
	3450 2200 3450 2350
Wire Wire Line
	3450 2350 4300 2350
Wire Wire Line
	5800 2950 5900 2950
Wire Wire Line
	5900 2950 5900 1600
Wire Wire Line
	5900 1600 3800 1600
Wire Wire Line
	3800 1600 3800 2100
Wire Wire Line
	3800 2100 3300 2100
Wire Wire Line
	3300 2400 3900 2400
Wire Wire Line
	3900 2400 3900 1900
Wire Wire Line
	3900 1900 4300 1900
NoConn ~ 4300 2000
NoConn ~ 4300 2100
NoConn ~ 4300 2600
NoConn ~ 4300 3200
NoConn ~ 4300 3300
NoConn ~ 4300 3400
NoConn ~ 4300 3500
NoConn ~ 5800 2050
NoConn ~ 5800 2150
NoConn ~ 5800 2300
NoConn ~ 5800 2400
NoConn ~ 5800 2750
NoConn ~ 5800 2850
Wire Wire Line
	5800 3300 6100 3300
Connection ~ 6100 3300
Wire Wire Line
	5800 3400 6100 3400
Connection ~ 6100 3400
Wire Wire Line
	5800 3500 6100 3500
Connection ~ 6100 3500
Wire Wire Line
	5800 3600 6100 3600
Connection ~ 6100 3600
$Comp
L PWR_FLAG #FLG08
U 1 1 54DE9E1D
P 1550 1000
F 0 "#FLG08" H 1550 1095 30  0001 C CNN
F 1 "PWR_FLAG" H 1550 1180 30  0000 C CNN
F 2 "" H 1550 1000 60  0000 C CNN
F 3 "" H 1550 1000 60  0000 C CNN
	1    1550 1000
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG09
U 1 1 54DE9E2C
P 1550 1650
F 0 "#FLG09" H 1550 1745 30  0001 C CNN
F 1 "PWR_FLAG" H 1550 1830 30  0000 C CNN
F 2 "" H 1550 1650 60  0000 C CNN
F 3 "" H 1550 1650 60  0000 C CNN
	1    1550 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 1000 1550 1050
Wire Wire Line
	1550 1050 1200 1050
Connection ~ 1200 1050
Wire Wire Line
	1550 1650 1550 1750
Wire Wire Line
	1550 1750 1200 1750
Connection ~ 1200 1750
Text Label 3350 1900 0    60   ~ 0
RST
Text Label 3350 2000 0    60   ~ 0
RXD
Text Label 3350 2100 0    60   ~ 0
PRG
Text Label 3350 2200 0    60   ~ 0
TXD
Text Label 3950 1900 0    60   ~ 0
CFG
Text Label 5950 2600 0    60   ~ 0
DO4
Text Label 7350 3050 0    60   ~ 0
SPK
Text Label 6050 3050 0    60   ~ 0
SOUND
Wire Wire Line
	3550 1900 3550 2500
Text Label 7000 2550 0    60   ~ 0
LED
$Comp
L SPEAKER SP1
U 1 1 54E33E0C
P 7850 1700
F 0 "SP1" H 7750 1950 70  0000 C CNN
F 1 "PIEZO SP" H 7950 1300 70  0000 C CNN
F 2 "~" H 7850 1700 60  0000 C CNN
F 3 "~" H 7850 1700 60  0000 C CNN
	1    7850 1700
	1    0    0    -1  
$EndComp
Connection ~ 7550 2250
Wire Wire Line
	7550 1600 7300 1600
Connection ~ 7300 1600
$Comp
L LED LD1
U 1 1 54E33E98
P 6700 2300
F 0 "LD1" H 6700 2400 50  0000 C CNN
F 1 "LED" H 6700 2200 50  0000 C CNN
F 2 "~" H 6700 2300 60  0000 C CNN
F 3 "~" H 6700 2300 60  0000 C CNN
	1    6700 2300
	-1   0    0    1   
$EndComp
Wire Wire Line
	6900 2300 7000 2300
Connection ~ 7000 2300
Wire Wire Line
	5800 2500 6400 2500
Wire Wire Line
	6400 2500 6400 2300
Wire Wire Line
	6400 2300 6500 2300
Text Label 6400 2300 0    60   ~ 0
DO3
$Comp
L VCC #PWR010
U 1 1 54EA582A
P 4050 2700
F 0 "#PWR010" H 4050 2800 30  0001 C CNN
F 1 "VCC" H 4050 2800 30  0000 C CNN
F 2 "" H 4050 2700 60  0000 C CNN
F 3 "" H 4050 2700 60  0000 C CNN
	1    4050 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 2700 4050 3050
Wire Wire Line
	4050 3050 4300 3050
Wire Wire Line
	4300 2950 4050 2950
Connection ~ 4050 2950
Wire Wire Line
	4300 2850 4050 2850
Connection ~ 4050 2850
Wire Wire Line
	4300 2750 4050 2750
Connection ~ 4050 2750
$EndSCHEMATC