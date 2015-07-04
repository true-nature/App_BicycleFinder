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
P 1100 2850
F 0 "BATTERY1" H 900 2950 50  0000 C CNN
F 1 "CR1220" H 900 2750 50  0000 C CNN
F 2 "favorites:BK-885" H 1100 2850 60  0001 C CNN
F 3 "" H 1100 2850 60  0000 C CNN
	1    1100 2850
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW1
U 1 1 549BC4AC
P 6000 5100
F 0 "SW1" H 6150 5210 50  0000 C CNN
F 1 "SPST" H 6000 5020 50  0000 C CNN
F 2 "favorites:B3FS-4002P" H 6000 5100 60  0001 C CNN
F 3 "~" H 6000 5100 60  0000 C CNN
	1    6000 5100
	0    1    1    0   
$EndComp
$Comp
L CP1 C1
U 1 1 549BC5A8
P 3300 3400
F 0 "C1" H 3350 3500 50  0000 L CNN
F 1 "1F" H 3350 3300 50  0000 L CNN
F 2 "favorites:SE-5R5-D105VYV" H 3300 3400 60  0001 C CNN
F 3 "~" H 3300 3400 60  0000 C CNN
	1    3300 3400
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 54ACCB34
P 1750 2450
F 0 "R1" V 1830 2450 40  0000 C CNN
F 1 "1k" V 1757 2451 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 1680 2450 30  0001 C CNN
F 3 "~" H 1750 2450 30  0000 C CNN
	1    1750 2450
	0    -1   -1   0   
$EndComp
$Comp
L PWR_FLAG #FLG01
U 1 1 54ACCF53
P 1100 2250
F 0 "#FLG01" H 1100 2345 30  0001 C CNN
F 1 "PWR_FLAG" H 1100 2430 30  0000 C CNN
F 2 "" H 1100 2250 60  0000 C CNN
F 3 "" H 1100 2250 60  0000 C CNN
	1    1100 2250
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG02
U 1 1 54ACCF62
P 1400 3150
F 0 "#FLG02" H 1400 3245 30  0001 C CNN
F 1 "PWR_FLAG" H 1400 3330 30  0000 C CNN
F 2 "" H 1400 3150 60  0000 C CNN
F 3 "" H 1400 3150 60  0000 C CNN
	1    1400 3150
	1    0    0    -1  
$EndComp
$Comp
L Led_Small LD1
U 1 1 54AD1F8E
P 8750 3100
F 0 "LD1" H 8750 3200 50  0000 C CNN
F 1 "SML-012WT" H 8750 3000 50  0000 C CNN
F 2 "favorites:LED-1206" H 8750 3100 60  0001 C CNN
F 3 "~" H 8750 3100 60  0000 C CNN
	1    8750 3100
	0    1    -1   0   
$EndComp
Text Label 1150 2450 0    60   ~ 0
3V
$Comp
L R R2
U 1 1 54AE44D9
P 8750 2550
F 0 "R2" V 8830 2550 40  0000 C CNN
F 1 "680" V 8757 2551 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 8680 2550 30  0001 C CNN
F 3 "~" H 8750 2550 30  0000 C CNN
	1    8750 2550
	1    0    0    -1  
$EndComp
$Comp
L HN2S01FU U2
U 1 1 54B6402D
P 2700 2450
F 0 "U2" H 2600 3000 60  0000 C CNN
F 1 "HN2S01FU" H 2700 2900 60  0000 C CNN
F 2 "Housings_SOT-23_SOT-143_TSOT-6:SC-70-6_Handsoldering" H 2700 2450 60  0001 C CNN
F 3 "" H 2700 2450 60  0000 C CNN
	1    2700 2450
	-1   0    0    -1  
$EndComp
Text Label 6700 2200 0    60   ~ 0
Vcc
Text Label 2050 2450 0    60   ~ 0
CHG
$Comp
L SW_PUSH SW2
U 1 1 54E4493A
P 6300 5100
F 0 "SW2" H 6450 5210 50  0000 C CNN
F 1 "FR2S1015" H 6300 5020 50  0000 C CNN
F 2 "favorites:FR2S1015" H 6300 5100 60  0001 C CNN
F 3 "~" H 6300 5100 60  0000 C CNN
	1    6300 5100
	0    1    1    0   
$EndComp
$Comp
L TWE_LITE_SMD U1
U 1 1 54E4765F
P 7250 3450
F 0 "U1" H 7250 3350 50  0000 C CNN
F 1 "TWE_LITE_SMD" H 7250 4250 50  0000 C CNN
F 2 "favorites:TWE-001L-NC7" H 7000 2200 50  0001 C CNN
F 3 "DOCUMENTATION" H 7600 2200 50  0001 C CNN
	1    7250 3450
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
NoConn ~ 6500 2900
NoConn ~ 6500 3000
NoConn ~ 8000 2950
NoConn ~ 8000 3050
NoConn ~ 8000 3300
NoConn ~ 8000 3650
NoConn ~ 8000 3750
NoConn ~ 8000 3950
NoConn ~ 6500 4200
NoConn ~ 6500 4300
NoConn ~ 8000 3400
$Comp
L PWR_FLAG #FLG03
U 1 1 54E48789
P 9450 2050
F 0 "#FLG03" H 9450 2145 30  0001 C CNN
F 1 "PWR_FLAG" H 9450 2230 30  0000 C CNN
F 2 "" H 9450 2050 60  0000 C CNN
F 3 "" H 9450 2050 60  0000 C CNN
	1    9450 2050
	1    0    0    -1  
$EndComp
NoConn ~ 6500 3500
Text Label 8400 3500 0    60   ~ 0
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
Text Label 6050 4100 0    60   ~ 0
DI1
Text Label 6300 4400 0    60   ~ 0
DI4
Text Label 5150 1550 3    60   ~ 0
ExVcc
Text Label 1100 3850 1    60   ~ 0
GND
$Comp
L GND #PWR04
U 1 1 54F3DF41
P 1100 4250
F 0 "#PWR04" H 1100 4250 30  0001 C CNN
F 1 "GND" H 1100 4180 30  0001 C CNN
F 2 "" H 1100 4250 60  0000 C CNN
F 3 "" H 1100 4250 60  0000 C CNN
	1    1100 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 4100 5650 4100
Connection ~ 3300 4100
Connection ~ 1100 4100
Wire Wire Line
	3300 3550 3300 4100
Connection ~ 6300 5500
Wire Wire Line
	1100 3000 1100 4250
Wire Wire Line
	8250 3850 8000 3850
Wire Wire Line
	8250 2050 8250 3850
Wire Wire Line
	5450 2050 8250 2050
Wire Wire Line
	3100 2450 3300 2450
Connection ~ 6350 2200
Wire Wire Line
	2250 1850 5150 1850
Wire Wire Line
	2250 2200 2250 1850
Wire Wire Line
	2300 2200 2250 2200
Wire Wire Line
	5150 1850 5150 1500
Connection ~ 6350 3650
Connection ~ 6350 3850
Wire Wire Line
	6350 3850 6500 3850
Connection ~ 6350 3750
Wire Wire Line
	6350 3750 6500 3750
Wire Wire Line
	6350 2200 6350 3950
Wire Wire Line
	6350 3950 6500 3950
Wire Wire Line
	6500 3650 6350 3650
Connection ~ 8400 4500
Wire Wire Line
	8400 5500 8400 4100
Wire Wire Line
	8400 4500 8000 4500
Wire Wire Line
	5450 1500 5450 2050
Connection ~ 3300 2700
Wire Wire Line
	5750 2800 6500 2800
Wire Wire Line
	5750 1500 5750 2800
Wire Wire Line
	4750 3400 6500 3400
Wire Wire Line
	5250 1500 5250 3650
Wire Wire Line
	5550 3250 6500 3250
Wire Wire Line
	5550 1500 5550 3250
Wire Wire Line
	5650 5500 8400 5500
Wire Wire Line
	6300 5500 6300 5400
Connection ~ 8400 4400
Wire Wire Line
	8400 4400 8000 4400
Connection ~ 8400 4300
Wire Wire Line
	8000 4300 8400 4300
Connection ~ 8400 4200
Wire Wire Line
	8000 4200 8400 4200
Wire Wire Line
	6000 5500 6000 5400
Wire Wire Line
	6000 4100 6000 4800
Wire Wire Line
	6000 4100 6500 4100
Wire Wire Line
	6300 4400 6300 4800
Wire Wire Line
	6300 4400 6500 4400
Wire Wire Line
	5350 1500 5350 3150
Wire Wire Line
	5350 3150 6500 3150
Wire Wire Line
	8750 3500 8000 3500
Wire Wire Line
	8750 3200 8750 3500
Connection ~ 8750 2200
Wire Wire Line
	8750 2200 8750 2400
Connection ~ 8050 2200
Wire Wire Line
	9450 2200 9450 2050
Wire Wire Line
	8400 4100 8000 4100
Wire Wire Line
	8050 2200 8050 2800
Wire Wire Line
	8050 2800 8000 2800
Wire Wire Line
	3300 2700 3100 2700
Wire Wire Line
	3300 2200 3300 3250
Connection ~ 2150 2450
Wire Wire Line
	2150 2450 2150 2700
Wire Wire Line
	2150 2700 2300 2700
Wire Wire Line
	1100 2450 1200 2450
Wire Wire Line
	1150 2450 1600 2450
Wire Wire Line
	1900 2450 2300 2450
Connection ~ 1100 2450
Wire Wire Line
	3100 2200 9450 2200
Connection ~ 3300 2450
Wire Wire Line
	1100 2250 1100 2700
Wire Wire Line
	1100 3150 1400 3150
Connection ~ 6000 5500
Wire Wire Line
	5650 1500 5650 5500
Text Label 5650 1750 1    60   ~ 0
GND
$Comp
L SW_PUSH SW3
U 1 1 5533A166
P 3700 2650
F 0 "SW3" H 3850 2760 50  0000 C CNN
F 1 "SKRPACE010" H 3700 2570 50  0000 C CNN
F 2 "favorites:SKRPACE010" H 3700 2650 60  0001 C CNN
F 3 "~" H 3700 2650 60  0000 C CNN
	1    3700 2650
	0    1    1    0   
$EndComp
Connection ~ 5250 3400
Connection ~ 1100 3150
Connection ~ 3300 2200
Connection ~ 5650 4100
NoConn ~ 8000 3200
$Comp
L BD45231G U3
U 1 1 5593DCBA
P 4400 3300
F 0 "U3" H 4400 3550 60  0000 C CNN
F 1 "BD45231G" H 4400 3050 60  0000 C CNN
F 2 "favorites:SSOP5_Handsoldering" H 4400 3300 60  0001 C CNN
F 3 "" H 4400 3300 60  0000 C CNN
	1    4400 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 3200 4800 3200
Wire Wire Line
	4800 3200 4800 2200
Connection ~ 4800 2200
Wire Wire Line
	4050 3400 3950 3400
Wire Wire Line
	3950 3300 3950 4100
Connection ~ 3950 4100
Wire Wire Line
	4050 3300 3950 3300
Connection ~ 3950 3400
Wire Wire Line
	3700 2950 3700 3450
Wire Wire Line
	3700 3200 4050 3200
Wire Wire Line
	3700 2350 3700 2200
Connection ~ 3700 2200
Text Label 3700 3100 1    60   ~ 0
ER
Wire Wire Line
	8750 3000 8750 2700
Text Label 8750 2950 1    60   ~ 0
LED
$Comp
L R R3
U 1 1 55940F83
P 3700 3600
F 0 "R3" V 3780 3600 40  0000 C CNN
F 1 "1M" V 3707 3601 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 3630 3600 30  0001 C CNN
F 3 "~" H 3700 3600 30  0000 C CNN
	1    3700 3600
	1    0    0    -1  
$EndComp
Connection ~ 3700 3200
Wire Wire Line
	3700 3750 3700 4100
Connection ~ 3700 4100
$Comp
L C_Small C2
U 1 1 55941ACA
P 5250 3750
F 0 "C2" H 5260 3820 50  0000 L CNN
F 1 "100p" H 5260 3670 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 5250 3750 60  0001 C CNN
F 3 "" H 5250 3750 60  0000 C CNN
	1    5250 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 3850 5250 4100
Connection ~ 5250 4100
$Comp
L R R4
U 1 1 5596B3D3
P 5050 2750
F 0 "R4" V 5130 2750 40  0000 C CNN
F 1 "1M" V 5057 2751 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4980 2750 30  0001 C CNN
F 3 "~" H 5050 2750 30  0000 C CNN
	1    5050 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 2600 5050 2200
Connection ~ 5050 2200
Wire Wire Line
	5050 2900 5050 3400
Connection ~ 5050 3400
$EndSCHEMATC
