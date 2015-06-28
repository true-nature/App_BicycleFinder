EESchema Schematic File Version 2
LIBS:favorites
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
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Bicycle Finder / Remote Commander"
Date "24 feb 2015"
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
F 2 "favorites:TWE-001L-NC7" H 4800 1300 50  0001 C CNN
F 3 "DOCUMENTATION" H 5400 1300 50  0001 C CNN
	1    5050 2550
	1    0    0    -1  
$EndComp
$Comp
L Battery BT1
U 1 1 54DE9794
P 1200 1400
F 0 "BT1" H 1400 1450 50  0000 C CNN
F 1 "2x AAA/LR03" V 1050 1400 50  0000 C CNN
F 2 "favorites:FINDER_RECEIVER" H 1200 1400 60  0001 C CNN
F 3 "~" H 1200 1400 60  0000 C CNN
	1    1200 1400
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
P 7000 1950
F 0 "LD2" H 7000 2050 50  0000 C CNN
F 1 "LED" H 7000 1850 50  0000 C CNN
F 2 "LEDs:LED-3MM" H 7000 1800 60  0001 C CNN
F 3 "~" H 7000 1950 60  0000 C CNN
	1    7000 1950
	0    -1   -1   0   
$EndComp
$Comp
L VCC #PWR05
U 1 1 54DE9A46
P 7000 1000
F 0 "#PWR05" H 7000 1100 30  0001 C CNN
F 1 "VCC" H 7000 1100 30  0000 C CNN
F 2 "" H 7000 1000 60  0000 C CNN
F 3 "" H 7000 1000 60  0000 C CNN
	1    7000 1000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 54DE9C03
P 3400 2500
F 0 "#PWR06" H 3400 2500 30  0001 C CNN
F 1 "GND" H 3400 2430 30  0001 C CNN
F 2 "" H 3400 2500 60  0000 C CNN
F 3 "" H 3400 2500 60  0000 C CNN
	1    3400 2500
	1    0    0    -1  
$EndComp
NoConn ~ 4300 2000
NoConn ~ 4300 2100
NoConn ~ 4300 2600
NoConn ~ 4300 3300
NoConn ~ 4300 3400
NoConn ~ 4300 3500
NoConn ~ 5800 2050
NoConn ~ 5800 2150
NoConn ~ 5800 2850
$Comp
L PWR_FLAG #FLG07
U 1 1 54DE9E1D
P 1550 1000
F 0 "#FLG07" H 1550 1095 30  0001 C CNN
F 1 "PWR_FLAG" H 1550 1180 30  0000 C CNN
F 2 "" H 1550 1000 60  0000 C CNN
F 3 "" H 1550 1000 60  0000 C CNN
	1    1550 1000
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG08
U 1 1 54DE9E2C
P 1550 1650
F 0 "#FLG08" H 1550 1745 30  0001 C CNN
F 1 "PWR_FLAG" H 1550 1830 30  0000 C CNN
F 2 "" H 1550 1650 60  0000 C CNN
F 3 "" H 1550 1650 60  0000 C CNN
	1    1550 1650
	1    0    0    -1  
$EndComp
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
Text Label 6200 2600 0    60   ~ 0
DO4
Text Label 6150 2750 0    60   ~ 0
SOUND
$Comp
L SPEAKER SP1
U 1 1 54E33E0C
P 9250 2450
F 0 "SP1" H 9150 2700 70  0000 C CNN
F 1 "PIEZO SP" H 9350 2050 70  0000 C CNN
F 2 "favorites:PIEZOSPK" H 9250 2850 60  0001 C CNN
F 3 "~" H 9250 2450 60  0000 C CNN
	1    9250 2450
	1    0    0    -1  
$EndComp
$Comp
L LED LD1
U 1 1 54E33E98
P 6400 1950
F 0 "LD1" H 6400 2050 50  0000 C CNN
F 1 "LED" H 6400 1850 50  0000 C CNN
F 2 "LEDs:LED-3MM" H 6400 1800 60  0001 C CNN
F 3 "~" H 6400 1950 60  0000 C CNN
	1    6400 1950
	0    -1   -1   0   
$EndComp
Text Label 6150 2500 0    60   ~ 0
DO3
$Comp
L VCC #PWR09
U 1 1 54EA582A
P 4050 2700
F 0 "#PWR09" H 4050 2800 30  0001 C CNN
F 1 "VCC" H 4050 2800 30  0000 C CNN
F 2 "" H 4050 2700 60  0000 C CNN
F 3 "" H 4050 2700 60  0000 C CNN
	1    4050 2700
	1    0    0    -1  
$EndComp
NoConn ~ 5800 3050
$Comp
L WRITER-VCC P1
U 1 1 550EA9F6
P 2900 2100
F 0 "P1" V 3000 2100 60  0000 C CNN
F 1 "WRITER-VCC" V 3100 2100 60  0000 C CNN
F 2 "favorites:WRITE-7P" H 2850 2050 60  0001 C CNN
F 3 "" H 2850 2050 60  0000 C CNN
	1    2900 2100
	-1   0    0    -1  
$EndComp
NoConn ~ 3300 1800
$Comp
L NJU72501MJE U2
U 1 1 5516B540
P 7950 2300
F 0 "U2" H 7950 2600 50  0000 C CNN
F 1 "NJU72501MJE" H 8000 2000 50  0000 C CNN
F 2 "favorites:AE-NJU72501MJE" H 7950 2300 50  0001 C CNN
F 3 "" H 7950 2300 50  0001 C CNN
	1    7950 2300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 5516B8A9
P 7350 3050
F 0 "#PWR010" H 7350 2800 50  0001 C CNN
F 1 "GND" H 7350 2900 50  0000 C CNN
F 2 "" H 7350 3050 60  0000 C CNN
F 3 "" H 7350 3050 60  0000 C CNN
	1    7350 3050
	1    0    0    -1  
$EndComp
Text Label 8800 2350 0    60   ~ 0
VO1
Text Label 8800 2550 0    60   ~ 0
VO2
Text Label 6900 3000 0    60   ~ 0
EN2
$Comp
L SW_PUSH SW1
U 1 1 553B3A5B
P 3550 3600
F 0 "SW1" H 3700 3710 50  0000 C CNN
F 1 "SW_PUSH" H 3550 3520 50  0000 C CNN
F 2 "favorites:RUBBER_SWITCH" H 3550 3600 60  0001 C CNN
F 3 "" H 3550 3600 60  0000 C CNN
	1    3550 3600
	0    1    1    0   
$EndComp
$Comp
L GND #PWR011
U 1 1 553B3BEC
P 3550 4000
F 0 "#PWR011" H 3550 3750 50  0001 C CNN
F 1 "GND" H 3550 3850 50  0000 C CNN
F 2 "" H 3550 4000 60  0000 C CNN
F 3 "" H 3550 4000 60  0000 C CNN
	1    3550 4000
	1    0    0    -1  
$EndComp
Text Label 3700 3200 0    60   ~ 0
DI1
$Comp
L R R1
U 1 1 5576694C
P 7000 1450
F 0 "R1" V 7080 1450 40  0000 C CNN
F 1 "680" V 7007 1451 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 6930 1450 30  0001 C CNN
F 3 "~" H 7000 1450 30  0000 C CNN
	1    7000 1450
	1    0    0    -1  
$EndComp
Text Label 6500 1650 0    60   ~ 0
LED
Text Label 6900 2900 0    60   ~ 0
EN1
$Comp
L R R2
U 1 1 55819164
P 7900 3250
F 0 "R2" V 7980 3250 40  0000 C CNN
F 1 "2M" V 7907 3251 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 7830 3250 30  0001 C CNN
F 3 "~" H 7900 3250 30  0000 C CNN
	1    7900 3250
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 5581930C
P 8100 3250
F 0 "R3" V 8180 3250 40  0000 C CNN
F 1 "2M" V 8107 3251 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 8030 3250 30  0001 C CNN
F 3 "~" H 8100 3250 30  0000 C CNN
	1    8100 3250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 558195C3
P 7900 3550
F 0 "#PWR012" H 7900 3300 50  0001 C CNN
F 1 "GND" H 7900 3400 50  0000 C CNN
F 2 "" H 7900 3550 60  0000 C CNN
F 3 "" H 7900 3550 60  0000 C CNN
	1    7900 3550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 558195F8
P 8100 3550
F 0 "#PWR013" H 8100 3300 50  0001 C CNN
F 1 "GND" H 8100 3400 50  0000 C CNN
F 2 "" H 8100 3550 60  0000 C CNN
F 3 "" H 8100 3550 60  0000 C CNN
	1    8100 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 950  1200 1250
Wire Wire Line
	1200 1550 1200 1850
Wire Wire Line
	5800 1900 6000 1900
Wire Wire Line
	6000 1900 6000 1550
Wire Wire Line
	5800 3200 6100 3200
Wire Wire Line
	6100 3200 6100 3950
Wire Wire Line
	5800 2600 7000 2600
Wire Wire Line
	7000 1000 7000 1300
Wire Wire Line
	7000 1200 7350 1200
Wire Wire Line
	7350 1200 7350 2150
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
Wire Wire Line
	5800 3300 6100 3300
Connection ~ 6100 3300
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
Wire Wire Line
	3550 1900 3550 2500
Wire Wire Line
	7350 2150 7400 2150
Wire Wire Line
	5800 2500 6400 2500
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
Wire Wire Line
	7400 2250 7350 2250
Wire Wire Line
	7350 2250 7350 3050
Wire Wire Line
	7400 2350 7350 2350
Connection ~ 7350 2350
Wire Wire Line
	8500 2350 8950 2350
Wire Wire Line
	8500 2450 8750 2450
Wire Wire Line
	8750 2450 8750 2550
Wire Wire Line
	8750 2550 8950 2550
Wire Wire Line
	5800 2400 6000 2400
Wire Wire Line
	6000 2400 6000 3000
Wire Wire Line
	6000 3000 8650 3000
Wire Wire Line
	8650 3000 8650 2250
Wire Wire Line
	8650 2250 8500 2250
Wire Wire Line
	7000 2600 7000 2150
Wire Wire Line
	6400 2500 6400 2150
Wire Wire Line
	7000 1600 7000 1750
Connection ~ 7000 1200
Wire Wire Line
	5800 3400 6100 3400
Connection ~ 6100 3400
Wire Wire Line
	5800 3500 6100 3500
Connection ~ 6100 3500
Wire Wire Line
	5800 3600 6100 3600
Connection ~ 6100 3600
Wire Wire Line
	3550 4000 3550 3900
Wire Wire Line
	4300 3200 3550 3200
Wire Wire Line
	3550 3200 3550 3300
Wire Wire Line
	6400 1750 6400 1650
Wire Wire Line
	6400 1650 7000 1650
Connection ~ 7000 1650
Wire Wire Line
	5800 2750 7250 2750
Wire Wire Line
	7250 2750 7250 2450
Wire Wire Line
	7250 2450 7400 2450
Wire Wire Line
	8500 2150 8550 2150
Wire Wire Line
	8550 2150 8550 2900
Wire Wire Line
	8550 2900 6100 2900
Wire Wire Line
	6100 2900 6100 2300
Wire Wire Line
	6100 2300 5800 2300
Wire Wire Line
	7900 3550 7900 3400
Wire Wire Line
	8100 3550 8100 3400
Wire Wire Line
	7900 3100 7900 2900
Connection ~ 7900 2900
Wire Wire Line
	8100 3100 8100 3000
Connection ~ 8100 3000
$EndSCHEMATC
