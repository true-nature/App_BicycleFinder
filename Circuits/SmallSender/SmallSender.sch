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
LIBS:SmallSender-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "22 feb 2015"
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
F 1 "CR1220" H 2550 1910 50  0000 C CNN
F 2 "" H 2550 2100 60  0000 C CNN
F 3 "" H 2550 2100 60  0000 C CNN
	1    2550 2100
	0    1    1    0   
$EndComp
$Comp
L GND #PWR01
U 1 1 549A463E
P 7200 4400
F 0 "#PWR01" H 7200 4400 30  0001 C CNN
F 1 "GND" H 7200 4330 30  0001 C CNN
F 2 "" H 7200 4400 60  0000 C CNN
F 3 "" H 7200 4400 60  0000 C CNN
	1    7200 4400
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
P 4800 4600
F 0 "SW1" H 4950 4710 50  0000 C CNN
F 1 "JB-15FBP2" H 4800 4520 50  0000 C CNN
F 2 "~" H 4800 4600 60  0000 C CNN
F 3 "~" H 4800 4600 60  0000 C CNN
	1    4800 4600
	0    1    1    0   
$EndComp
$Comp
L CP1 C1
U 1 1 549BC5A8
P 7900 2200
F 0 "C1" H 7950 2300 50  0000 L CNN
F 1 "1F" H 7950 2100 50  0000 L CNN
F 2 "~" H 7900 2200 60  0000 C CNN
F 3 "~" H 7900 2200 60  0000 C CNN
	1    7900 2200
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 54ACCB34
P 3200 1700
F 0 "R1" V 3280 1700 40  0000 C CNN
F 1 "330" V 3207 1701 40  0000 C CNN
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
L LED LD1
U 1 1 54AD1F8E
P 7200 2600
F 0 "LD1" H 7200 2700 50  0000 C CNN
F 1 "SML-012WT" H 7200 2500 50  0000 C CNN
F 2 "~" H 7200 2600 60  0000 C CNN
F 3 "~" H 7200 2600 60  0000 C CNN
	1    7200 2600
	0    1    1    0   
$EndComp
Text Label 2600 1700 0    60   ~ 0
3V
$Comp
L R R2
U 1 1 54AE44D9
P 7200 2050
F 0 "R2" V 7280 2050 40  0000 C CNN
F 1 "680" V 7207 2051 40  0000 C CNN
F 2 "~" V 7130 2050 30  0000 C CNN
F 3 "~" H 7200 2050 30  0000 C CNN
	1    7200 2050
	1    0    0    -1  
$EndComp
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
Text Label 5500 1700 0    60   ~ 0
Vcc
Text Label 3500 1700 0    60   ~ 0
CHG
Text Label 2550 2500 1    60   ~ 0
GND
$Comp
L CONN_2 JP1
U 1 1 54B7E0F7
P 3700 2600
F 0 "JP1" V 3650 2600 40  0000 C CNN
F 1 "BYPASS" V 3750 2600 40  0000 C CNN
F 2 "~" H 3700 2600 60  0000 C CNN
F 3 "~" H 3700 2600 60  0000 C CNN
	1    3700 2600
	0    1    1    0   
$EndComp
$Comp
L SW_PUSH SW2
U 1 1 54E4493A
P 5100 4600
F 0 "SW2" H 5250 4710 50  0000 C CNN
F 1 "MKA-10110" H 5100 4520 50  0000 C CNN
F 2 "~" H 5100 4600 60  0000 C CNN
F 3 "~" H 5100 4600 60  0000 C CNN
	1    5100 4600
	0    1    1    0   
$EndComp
$Comp
L GND #PWR05
U 1 1 54E44A18
P 4800 5250
F 0 "#PWR05" H 4800 5250 30  0001 C CNN
F 1 "GND" H 4800 5180 30  0001 C CNN
F 2 "" H 4800 5250 60  0000 C CNN
F 3 "" H 4800 5250 60  0000 C CNN
	1    4800 5250
	1    0    0    -1  
$EndComp
$Comp
L TWE_LITE_SMD U1
U 1 1 54E4765F
P 6050 2950
F 0 "U1" H 6050 2850 50  0000 C CNN
F 1 "TWE_LITE_SMD" H 6050 3750 50  0000 C CNN
F 2 "MODULE" H 5800 1700 50  0001 C CNN
F 3 "DOCUMENTATION" H 6400 1700 50  0001 C CNN
	1    6050 2950
	1    0    0    -1  
$EndComp
$Comp
L WRITER-VCC P1
U 1 1 54E4785D
P 3700 3700
F 0 "P1" V 3800 3700 60  0000 C CNN
F 1 "WRITER-VCC" V 3900 3700 60  0000 C CNN
F 2 "~" H 3650 3650 60  0000 C CNN
F 3 "~" H 3650 3650 60  0000 C CNN
	1    3700 3700
	-1   0    0    -1  
$EndComp
NoConn ~ 5300 2400
NoConn ~ 5300 2500
NoConn ~ 6800 2450
NoConn ~ 6800 2550
NoConn ~ 6800 2700
NoConn ~ 6800 2800
NoConn ~ 6800 3150
NoConn ~ 6800 3250
NoConn ~ 6800 3450
NoConn ~ 5300 3700
NoConn ~ 5300 3800
Wire Wire Line
	2550 2400 2850 2400
Wire Wire Line
	2550 2550 2550 2400
Wire Wire Line
	2550 1500 2550 1800
Connection ~ 4750 1700
Wire Wire Line
	4550 1700 7900 1700
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
	3600 1700 3600 2250
Connection ~ 3600 1700
Wire Wire Line
	4750 1450 4750 2200
Wire Wire Line
	4750 1950 4550 1950
Wire Wire Line
	4550 1450 4750 1450
Connection ~ 3600 1950
Wire Wire Line
	6800 2300 6900 2300
Wire Wire Line
	6900 2300 6900 1700
Wire Wire Line
	7900 3600 6800 3600
Wire Wire Line
	7900 1550 7900 2000
Connection ~ 6900 1700
Wire Wire Line
	7900 2400 7900 3600
Wire Wire Line
	7200 1700 7200 1800
Connection ~ 7200 1700
Wire Wire Line
	7200 2800 7200 3000
Wire Wire Line
	6800 3000 7550 3000
NoConn ~ 6800 2900
Wire Wire Line
	5300 2650 4700 2650
Wire Wire Line
	4700 2650 4700 3600
Wire Wire Line
	4700 3600 4100 3600
Wire Wire Line
	5100 3900 5300 3900
Wire Wire Line
	5100 3900 5100 4300
Wire Wire Line
	4800 3600 5300 3600
Wire Wire Line
	4800 3600 4800 4300
Wire Wire Line
	4800 4900 4800 5250
Connection ~ 7200 3600
Wire Wire Line
	6800 3700 7200 3700
Connection ~ 7200 3700
Wire Wire Line
	7200 3800 6800 3800
Connection ~ 7200 3800
Wire Wire Line
	7200 3900 6800 3900
Connection ~ 7200 3900
Wire Wire Line
	5100 5000 5100 4900
Wire Wire Line
	4600 5000 5100 5000
Connection ~ 4800 5000
Wire Wire Line
	4100 3800 4600 3800
Wire Wire Line
	4600 3800 4600 2750
Wire Wire Line
	4600 2750 5300 2750
Wire Wire Line
	4100 3500 4500 3500
Wire Wire Line
	4500 3500 4500 2900
Wire Wire Line
	4500 2900 5300 2900
Wire Wire Line
	4100 4000 4400 4000
Wire Wire Line
	4400 4000 4400 2300
Wire Wire Line
	4400 2300 5300 2300
Wire Wire Line
	3800 2250 3800 2200
Wire Wire Line
	3800 2200 4750 2200
Connection ~ 4750 1950
Wire Wire Line
	4100 3900 4600 3900
Wire Wire Line
	4600 3900 4600 5000
Wire Wire Line
	4100 3700 4300 3700
Wire Wire Line
	4300 3700 4300 4200
Wire Wire Line
	4300 4200 6900 4200
Wire Wire Line
	6900 4200 6900 3350
Wire Wire Line
	6900 3350 6800 3350
$Comp
L PWR_FLAG #FLG06
U 1 1 54E48789
P 7900 1550
F 0 "#FLG06" H 7900 1645 30  0001 C CNN
F 1 "PWR_FLAG" H 7900 1730 30  0000 C CNN
F 2 "" H 7900 1550 60  0000 C CNN
F 3 "" H 7900 1550 60  0000 C CNN
	1    7900 1550
	1    0    0    -1  
$EndComp
NoConn ~ 5300 3000
Wire Wire Line
	7200 4000 6800 4000
Wire Wire Line
	7200 3600 7200 4400
Connection ~ 7200 4000
Text Label 6900 3000 0    60   ~ 0
DO4
Text Label 4150 3500 0    60   ~ 0
RST
Text Label 4150 3600 0    60   ~ 0
RXD
Text Label 4150 3700 0    60   ~ 0
PRG
Text Label 4450 3900 0    60   ~ 0
GND
Text Label 4150 4000 0    60   ~ 0
CFG
Text Label 4150 3800 0    60   ~ 0
TXD
Text Label 4850 3600 0    60   ~ 0
DI1
Text Label 5100 3900 0    60   ~ 0
DI4
$Comp
L LED LD2
U 1 1 54E737C6
P 7550 2600
F 0 "LD2" H 7550 2700 50  0000 C CNN
F 1 "LED" H 7550 2500 50  0000 C CNN
F 2 "~" H 7550 2600 60  0000 C CNN
F 3 "~" H 7550 2600 60  0000 C CNN
	1    7550 2600
	0    1    1    0   
$EndComp
Wire Wire Line
	7550 3000 7550 2800
Connection ~ 7200 3000
Wire Wire Line
	7200 2300 7200 2400
Wire Wire Line
	7550 2400 7550 2350
Wire Wire Line
	7550 2350 7200 2350
Connection ~ 7200 2350
Text Label 7250 2350 0    60   ~ 0
LED
Connection ~ 7900 1700
Wire Wire Line
	5300 3150 5150 3150
Wire Wire Line
	5150 3450 5300 3450
Wire Wire Line
	5150 1700 5150 3450
Wire Wire Line
	5300 3250 5150 3250
Connection ~ 5150 3250
Wire Wire Line
	5300 3350 5150 3350
Connection ~ 5150 3350
Text Label 4150 3400 0    60   ~ 0
3V3
Connection ~ 5150 3150
Wire Wire Line
	4900 3400 4100 3400
Wire Wire Line
	3750 1450 3700 1450
Wire Wire Line
	3700 1450 3700 1100
Wire Wire Line
	3700 1100 4900 1100
Wire Wire Line
	4900 1100 4900 3400
Connection ~ 5150 1700
$EndSCHEMATC
