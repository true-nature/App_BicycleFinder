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
Date "24 dec 2014"
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
P 1750 2300
F 0 "BT1" H 1750 2500 50  0000 C CNN
F 1 "BATTERY" H 1750 2110 50  0000 C CNN
F 2 "" H 1750 2300 60  0000 C CNN
F 3 "" H 1750 2300 60  0000 C CNN
	1    1750 2300
	0    1    1    0   
$EndComp
$Comp
L LITE_LITE U1
U 1 1 549A2144
P 4000 2900
F 0 "U1" H 4000 2900 10  0001 C CNN
F 1 "LITE_LITE" H 4000 2900 60  0001 C CNN
F 2 "" H 4000 2900 60  0000 C CNN
F 3 "" H 4000 2900 60  0000 C CNN
	1    4000 2900
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR01
U 1 1 549A285E
P 2700 1750
F 0 "#PWR01" H 2700 1850 30  0001 C CNN
F 1 "VCC" H 2700 1850 30  0000 C CNN
F 2 "" H 2700 1750 60  0000 C CNN
F 3 "" H 2700 1750 60  0000 C CNN
	1    2700 1750
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR02
U 1 1 549A2873
P 1750 1750
F 0 "#PWR02" H 1750 1850 30  0001 C CNN
F 1 "VCC" H 1750 1850 30  0000 C CNN
F 2 "" H 1750 1750 60  0000 C CNN
F 3 "" H 1750 1750 60  0000 C CNN
	1    1750 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 1750 1750 2000
Wire Wire Line
	2700 1750 2700 2900
Wire Wire Line
	2700 2900 3100 2900
Wire Wire Line
	5000 2900 5600 2900
Wire Wire Line
	5600 2900 5600 3500
Wire Wire Line
	1750 2600 1750 2950
NoConn ~ 4000 1900
NoConn ~ 4100 1900
NoConn ~ 4200 1900
NoConn ~ 4300 1900
NoConn ~ 4400 1900
NoConn ~ 3100 2500
NoConn ~ 3100 2600
NoConn ~ 3100 2700
NoConn ~ 3100 2800
NoConn ~ 3100 3000
NoConn ~ 3100 3100
NoConn ~ 3100 3200
NoConn ~ 3700 3800
NoConn ~ 3800 3800
NoConn ~ 3900 3800
NoConn ~ 4000 3800
NoConn ~ 4100 3800
NoConn ~ 4200 3800
NoConn ~ 4300 3800
NoConn ~ 4400 3800
NoConn ~ 5000 3200
NoConn ~ 5000 3000
NoConn ~ 5000 2800
NoConn ~ 5000 2700
NoConn ~ 5000 2600
NoConn ~ 5000 2500
NoConn ~ 5000 3100
Connection ~ 5600 3350
$Comp
L PWR_FLAG #FLG03
U 1 1 549A37E5
P 5850 3250
F 0 "#FLG03" H 5850 3345 30  0001 C CNN
F 1 "PWR_FLAG" H 5850 3430 30  0000 C CNN
F 2 "" H 5850 3250 60  0000 C CNN
F 3 "" H 5850 3250 60  0000 C CNN
	1    5850 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 3250 5850 3350
Wire Wire Line
	5850 3350 5600 3350
Text Label 2750 2900 0    60   ~ 0
Vcc
Text Label 5200 2900 0    60   ~ 0
GND
$Comp
L PWR_FLAG #FLG04
U 1 1 549A4528
P 1900 1750
F 0 "#FLG04" H 1900 1845 30  0001 C CNN
F 1 "PWR_FLAG" H 1900 1930 30  0000 C CNN
F 2 "" H 1900 1750 60  0000 C CNN
F 3 "" H 1900 1750 60  0000 C CNN
	1    1900 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 1750 1750 1750
$Comp
L GND #PWR05
U 1 1 549A463E
P 5600 3500
F 0 "#PWR05" H 5600 3500 30  0001 C CNN
F 1 "GND" H 5600 3430 30  0001 C CNN
F 2 "" H 5600 3500 60  0000 C CNN
F 3 "" H 5600 3500 60  0000 C CNN
	1    5600 3500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 549A464D
P 1750 2950
F 0 "#PWR06" H 1750 2950 30  0001 C CNN
F 1 "GND" H 1750 2880 30  0001 C CNN
F 2 "" H 1750 2950 60  0000 C CNN
F 3 "" H 1750 2950 60  0000 C CNN
	1    1750 2950
	1    0    0    -1  
$EndComp
$EndSCHEMATC
