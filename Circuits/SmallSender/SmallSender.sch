EESchema Schematic File Version 2
LIBS:SmallSender-rescue
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
LIBS:SmallSender-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "10 mar 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Battery BATTERY1
U 1 1 5493D0B5
P 1850 2850
F 0 "BATTERY1" H 1650 2950 50  0000 C CNN
F 1 "CR2032" H 1650 2750 50  0000 C CNN
F 2 "favorites:BK-888+BK-2032M" H 1850 2850 60  0001 C CNN
F 3 "" H 1850 2850 60  0000 C CNN
	1    1850 2850
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW2
U 1 1 549BC4AC
P 6250 5100
F 0 "SW2" H 6400 5210 50  0000 C CNN
F 1 "SPST" H 6250 5020 50  0000 C CNN
F 2 "favorites:B3FS-4002P" H 6250 5100 60  0001 C CNN
F 3 "~" H 6250 5100 60  0000 C CNN
	1    6250 5100
	0    1    1    0   
$EndComp
$Comp
L PWR_FLAG #FLG01
U 1 1 54ACCF53
P 1850 2250
F 0 "#FLG01" H 1850 2345 30  0001 C CNN
F 1 "PWR_FLAG" H 1850 2430 30  0000 C CNN
F 2 "" H 1850 2250 60  0000 C CNN
F 3 "" H 1850 2250 60  0000 C CNN
	1    1850 2250
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG02
U 1 1 54ACCF62
P 2150 3150
F 0 "#FLG02" H 2150 3245 30  0001 C CNN
F 1 "PWR_FLAG" H 2150 3330 30  0000 C CNN
F 2 "" H 2150 3150 60  0000 C CNN
F 3 "" H 2150 3150 60  0000 C CNN
	1    2150 3150
	1    0    0    -1  
$EndComp
$Comp
L Led_Small LD1
U 1 1 54AD1F8E
P 9000 3100
F 0 "LD1" H 9000 3200 50  0000 C CNN
F 1 "SML-012WT" H 9000 3000 50  0000 C CNN
F 2 "favorites:LED-1206" H 9000 3100 60  0001 C CNN
F 3 "~" H 9000 3100 60  0000 C CNN
	1    9000 3100
	0    1    -1   0   
$EndComp
Text Label 1900 2450 0    60   ~ 0
3V
$Comp
L R R1
U 1 1 54AE44D9
P 9000 2550
F 0 "R1" V 9080 2550 40  0000 C CNN
F 1 "680" V 9007 2551 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 8930 2550 30  0001 C CNN
F 3 "~" H 9000 2550 30  0000 C CNN
	1    9000 2550
	1    0    0    -1  
$EndComp
$Comp
L HN2S01FU U2
U 1 1 54B6402D
P 2900 2450
F 0 "U2" H 2800 3000 60  0000 C CNN
F 1 "HN2S01FU" H 2900 2900 60  0000 C CNN
F 2 "Housings_SOT-23_SOT-143_TSOT-6:SC-70-6_Handsoldering" H 2900 2450 60  0001 C CNN
F 3 "" H 2900 2450 60  0000 C CNN
	1    2900 2450
	-1   0    0    -1  
$EndComp
Text Label 6950 2200 0    60   ~ 0
Vcc
$Comp
L SW_PUSH SW3
U 1 1 54E4493A
P 6550 5100
F 0 "SW3" H 6700 5210 50  0000 C CNN
F 1 "FR2S1015" H 6550 5020 50  0000 C CNN
F 2 "favorites:FR2S1015" H 6550 5100 60  0001 C CNN
F 3 "~" H 6550 5100 60  0000 C CNN
	1    6550 5100
	0    1    1    0   
$EndComp
$Comp
L TWE_LITE_SMD U1
U 1 1 54E4765F
P 7500 3450
F 0 "U1" H 7500 3350 50  0000 C CNN
F 1 "TWE_LITE_SMD" H 7500 4250 50  0000 C CNN
F 2 "favorites:TWE-001L-NC7" H 7250 2200 50  0001 C CNN
F 3 "DOCUMENTATION" H 7850 2200 50  0001 C CNN
	1    7500 3450
	1    0    0    -1  
$EndComp
$Comp
L WRITER-VCC P1
U 1 1 54E4785D
P 5450 1100
F 0 "P1" V 5550 1100 60  0000 C CNN
F 1 "WRITER-VCC" V 5650 1100 60  0000 C CNN
F 2 "favorites:WRITE-7P" H 5450 650 60  0001 C CNN
F 3 "~" H 5400 1050 60  0000 C CNN
	1    5450 1100
	0    -1   -1   0   
$EndComp
NoConn ~ 6750 3000
NoConn ~ 8250 2950
NoConn ~ 8250 3050
NoConn ~ 8250 3300
NoConn ~ 8250 3650
NoConn ~ 8250 3750
NoConn ~ 8250 3950
NoConn ~ 6750 4200
NoConn ~ 6750 4300
NoConn ~ 8250 3400
$Comp
L PWR_FLAG #FLG03
U 1 1 54E48789
P 9700 2050
F 0 "#FLG03" H 9700 2145 30  0001 C CNN
F 1 "PWR_FLAG" H 9700 2230 30  0000 C CNN
F 2 "" H 9700 2050 60  0000 C CNN
F 3 "" H 9700 2050 60  0000 C CNN
	1    9700 2050
	1    0    0    -1  
$EndComp
NoConn ~ 6750 3500
Text Label 8650 3500 0    60   ~ 0
DO4
Text Label 5250 1550 3    60   ~ 0
RST
Text Label 5350 1550 3    60   ~ 0
RXD
Text Label 5450 1550 3    60   ~ 0
PRG
Text Label 5750 1550 3    60   ~ 0
CFG
Text Label 5550 1550 3    60   ~ 0
TXD
Text Label 6300 4100 0    60   ~ 0
DI1
Text Label 6550 4400 0    60   ~ 0
DI4
Text Label 2600 1850 0    60   ~ 0
ExtVcc
Text Label 1850 3850 1    60   ~ 0
GND
$Comp
L GND #PWR04
U 1 1 54F3DF41
P 1850 4250
F 0 "#PWR04" H 1850 4250 30  0001 C CNN
F 1 "GND" H 1850 4180 30  0001 C CNN
F 2 "" H 1850 4250 60  0000 C CNN
F 3 "" H 1850 4250 60  0000 C CNN
	1    1850 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 4100 5650 4100
Connection ~ 1850 4100
Connection ~ 6550 5500
Wire Wire Line
	1850 3000 1850 4250
Wire Wire Line
	8500 3850 8250 3850
Wire Wire Line
	8500 2050 8500 3850
Wire Wire Line
	5450 2050 8500 2050
Wire Wire Line
	3300 2450 3500 2450
Connection ~ 6600 2200
Wire Wire Line
	2450 2200 2450 1850
Wire Wire Line
	2500 2200 2450 2200
Wire Wire Line
	5150 1850 5150 1500
Connection ~ 6600 3650
Connection ~ 6600 3850
Wire Wire Line
	6600 3850 6750 3850
Connection ~ 6600 3750
Wire Wire Line
	6600 3750 6750 3750
Wire Wire Line
	6600 2200 6600 3950
Wire Wire Line
	6600 3950 6750 3950
Wire Wire Line
	6750 3650 6600 3650
Wire Wire Line
	8650 5500 8650 4100
Wire Wire Line
	5450 1500 5450 2050
Connection ~ 3500 2700
Wire Wire Line
	5750 2800 6750 2800
Wire Wire Line
	5750 1500 5750 2800
Wire Wire Line
	5250 3400 6750 3400
Wire Wire Line
	5250 1500 5250 3400
Wire Wire Line
	5550 3250 6750 3250
Wire Wire Line
	5550 1500 5550 3250
Wire Wire Line
	5650 5500 8650 5500
Wire Wire Line
	6550 5500 6550 5400
Connection ~ 8650 4200
Wire Wire Line
	8250 4200 8650 4200
Wire Wire Line
	6250 5500 6250 5400
Wire Wire Line
	6250 4100 6250 4800
Wire Wire Line
	5950 4100 6750 4100
Wire Wire Line
	6550 4400 6550 4800
Wire Wire Line
	6550 4400 6750 4400
Wire Wire Line
	5350 1500 5350 3150
Wire Wire Line
	5350 3150 6750 3150
Wire Wire Line
	9000 3500 8250 3500
Wire Wire Line
	9000 3200 9000 3500
Connection ~ 9000 2200
Wire Wire Line
	9000 2200 9000 2400
Connection ~ 8300 2200
Wire Wire Line
	9700 2200 9700 2050
Wire Wire Line
	8650 4100 8250 4100
Wire Wire Line
	8300 2200 8300 2800
Wire Wire Line
	8300 2800 8250 2800
Wire Wire Line
	3500 2700 3300 2700
Wire Wire Line
	3500 2200 3500 3250
Connection ~ 2350 2450
Wire Wire Line
	2350 2450 2350 2700
Wire Wire Line
	2350 2700 2500 2700
Connection ~ 1850 2450
Connection ~ 3500 2450
Wire Wire Line
	1850 2250 1850 2700
Wire Wire Line
	1850 3150 2150 3150
Connection ~ 6250 5500
Wire Wire Line
	5650 1500 5650 5500
Text Label 5650 1750 1    60   ~ 0
GND
$Comp
L SW_PUSH SW4
U 1 1 5533A166
P 5000 3700
F 0 "SW4" H 5150 3810 50  0000 C CNN
F 1 "SKRPACE010" H 5000 3620 50  0000 C CNN
F 2 "favorites:SKRPACE010" H 5000 3700 60  0001 C CNN
F 3 "~" H 5000 3700 60  0000 C CNN
	1    5000 3700
	0    1    1    0   
$EndComp
Connection ~ 1850 3150
Connection ~ 3500 2200
Connection ~ 5650 4100
NoConn ~ 8250 3200
Wire Wire Line
	9000 3000 9000 2700
Text Label 9000 2950 1    60   ~ 0
LED
$Comp
L C_Small C1
U 1 1 55941ACA
P 3500 3350
F 0 "C1" H 3510 3420 50  0000 L CNN
F 1 "100u" H 3510 3270 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 3500 3350 60  0001 C CNN
F 3 "" H 3500 3350 60  0000 C CNN
	1    3500 3350
	1    0    0    -1  
$EndComp
Connection ~ 3500 4100
Wire Wire Line
	3500 3450 3500 4100
Wire Wire Line
	1850 2450 2500 2450
Wire Wire Line
	3300 2200 9700 2200
Wire Wire Line
	2450 1850 5150 1850
Wire Wire Line
	6750 2900 5000 2900
Wire Wire Line
	5000 2900 5000 3400
Wire Wire Line
	5000 4000 5000 4100
Connection ~ 5000 4100
Text Label 6050 2900 0    60   ~ 0
PAIRING
$Comp
L SW_PUSH SW1
U 1 1 568D0130
P 5950 5100
F 0 "SW1" H 6100 5210 50  0000 C CNN
F 1 "SPST" H 5950 5020 50  0000 C CNN
F 2 "favorites:B3FS-4002P" H 5950 5100 60  0001 C CNN
F 3 "~" H 5950 5100 60  0000 C CNN
	1    5950 5100
	0    1    1    0   
$EndComp
Wire Wire Line
	5950 4800 5950 4100
Connection ~ 6250 4100
Wire Wire Line
	5950 5400 5950 5500
Connection ~ 5950 5500
NoConn ~ 8250 4300
NoConn ~ 8250 4400
NoConn ~ 8250 4500
$Comp
L BD45231G U3
U 1 1 56C5B5D5
P 4350 3050
F 0 "U3" H 4350 3300 60  0000 C CNN
F 1 "BD45231G" H 4350 2800 60  0000 C CNN
F 2 "favorites:SSOP5_Handsoldering" H 4350 3050 60  0001 C CNN
F 3 "" H 4350 3050 60  0000 C CNN
	1    4350 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 2950 3900 2950
Wire Wire Line
	3900 2950 3900 4100
Connection ~ 3900 4100
Wire Wire Line
	4000 3050 3900 3050
Connection ~ 3900 3050
Wire Wire Line
	4000 3150 3900 3150
Connection ~ 3900 3150
Wire Wire Line
	4700 3150 5250 3150
Connection ~ 5250 3150
Wire Wire Line
	4700 2950 4750 2950
Wire Wire Line
	4750 2950 4750 2200
Connection ~ 4750 2200
$EndSCHEMATC
