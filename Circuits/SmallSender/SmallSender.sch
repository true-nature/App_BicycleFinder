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
P 5800 5100
F 0 "SW1" H 5950 5210 50  0000 C CNN
F 1 "SPST" H 5800 5020 50  0000 C CNN
F 2 "favorites:B3FS-4002P" H 5800 5100 60  0001 C CNN
F 3 "~" H 5800 5100 60  0000 C CNN
	1    5800 5100
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
P 8550 3100
F 0 "LD1" H 8550 3200 50  0000 C CNN
F 1 "SML-012WT" H 8550 3000 50  0000 C CNN
F 2 "favorites:LED-1206" H 8550 3100 60  0001 C CNN
F 3 "~" H 8550 3100 60  0000 C CNN
	1    8550 3100
	0    1    -1   0   
$EndComp
Text Label 1150 2450 0    60   ~ 0
3V
$Comp
L R R2
U 1 1 54AE44D9
P 8550 2550
F 0 "R2" V 8630 2550 40  0000 C CNN
F 1 "680" V 8557 2551 40  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 8480 2550 30  0001 C CNN
F 3 "~" H 8550 2550 30  0000 C CNN
	1    8550 2550
	1    0    0    -1  
$EndComp
$Comp
L HN2S01FU U2
U 1 1 54B6402D
P 2700 2450
F 0 "U2" H 2600 3000 60  0000 C CNN
F 1 "HN2S01FU" H 2700 2900 60  0000 C CNN
F 2 "Housings_SOT-23_SOT-143_TSOT-6:SC-70-6" H 2700 2450 60  0001 C CNN
F 3 "" H 2700 2450 60  0000 C CNN
	1    2700 2450
	-1   0    0    -1  
$EndComp
Text Label 6500 2200 0    60   ~ 0
Vcc
Text Label 2050 2450 0    60   ~ 0
CHG
$Comp
L SW_PUSH SW2
U 1 1 54E4493A
P 6100 5100
F 0 "SW2" H 6250 5210 50  0000 C CNN
F 1 "FR2S1015" H 6100 5020 50  0000 C CNN
F 2 "favorites:FR2S1015" H 6100 5100 60  0001 C CNN
F 3 "~" H 6100 5100 60  0000 C CNN
	1    6100 5100
	0    1    1    0   
$EndComp
$Comp
L TWE_LITE_SMD U1
U 1 1 54E4765F
P 7050 3450
F 0 "U1" H 7050 3350 50  0000 C CNN
F 1 "TWE_LITE_SMD" H 7050 4250 50  0000 C CNN
F 2 "favorites:TWE-001L-NC7" H 6800 2200 50  0001 C CNN
F 3 "DOCUMENTATION" H 7400 2200 50  0001 C CNN
	1    7050 3450
	1    0    0    -1  
$EndComp
$Comp
L WRITER-VCC P1
U 1 1 54E4785D
P 5250 1100
F 0 "P1" V 5350 1100 60  0000 C CNN
F 1 "WRITER-VCC" V 5450 1100 60  0000 C CNN
F 2 "favorites:WRITE-7P" H 5250 650 60  0001 C CNN
F 3 "~" H 5200 1050 60  0000 C CNN
	1    5250 1100
	0    -1   -1   0   
$EndComp
NoConn ~ 6300 2900
NoConn ~ 6300 3000
NoConn ~ 7800 2950
NoConn ~ 7800 3050
NoConn ~ 7800 3300
NoConn ~ 7800 3650
NoConn ~ 7800 3750
NoConn ~ 7800 3950
NoConn ~ 6300 4200
NoConn ~ 6300 4300
NoConn ~ 7800 3400
$Comp
L PWR_FLAG #FLG03
U 1 1 54E48789
P 9250 2050
F 0 "#FLG03" H 9250 2145 30  0001 C CNN
F 1 "PWR_FLAG" H 9250 2230 30  0000 C CNN
F 2 "" H 9250 2050 60  0000 C CNN
F 3 "" H 9250 2050 60  0000 C CNN
	1    9250 2050
	1    0    0    -1  
$EndComp
NoConn ~ 6300 3500
Text Label 8200 3500 0    60   ~ 0
DO4
Text Label 5050 1550 3    60   ~ 0
RST
Text Label 5150 1550 3    60   ~ 0
RXD
Text Label 5250 1550 3    60   ~ 0
PRG
Text Label 5550 1550 3    60   ~ 0
CFG
Text Label 5350 1550 3    60   ~ 0
TXD
Text Label 5850 4100 0    60   ~ 0
DI1
Text Label 6100 4400 0    60   ~ 0
DI4
Text Label 4950 1550 3    60   ~ 0
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
Text Label 3850 4700 0    60   ~ 0
DO1
Text Label 8550 2900 0    60   ~ 0
LED
$Comp
L R R3
U 1 1 5506FF55
P 3650 2500
F 0 "R3" V 3730 2500 50  0000 C CNN
F 1 "10M" V 3650 2500 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 3580 2500 30  0001 C CNN
F 3 "" H 3650 2500 30  0000 C CNN
	1    3650 2500
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 550D0A30
P 4750 2500
F 0 "R4" V 4830 2500 50  0000 C CNN
F 1 "10M" V 4750 2500 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 4680 2500 30  0001 C CNN
F 3 "" H 4750 2500 30  0000 C CNN
	1    4750 2500
	1    0    0    -1  
$EndComp
Text Label 6900 5500 0    60   ~ 0
TWE_GND
$Comp
L TCM809RVNB U3
U 1 1 550D6575
P 4300 2900
F 0 "U3" H 4350 3100 60  0000 C CNN
F 1 "TCM809RVNB" H 4300 3200 60  0000 C CNN
F 2 "Housings_SOT-23_SOT-143_TSOT-6:SOT-23" H 4300 2900 60  0001 C CNN
F 3 "" H 4300 2900 60  0000 C CNN
	1    4300 2900
	1    0    0    -1  
$EndComp
$Comp
L 2N7002DW U4
U 1 1 550DC11E
P 4600 3700
F 0 "U4" H 4600 4000 40  0000 R CNN
F 1 "2N7002DW" H 4750 3400 40  0000 R CNN
F 2 "Housings_SOT-23_SOT-143_TSOT-6:SC-70-6" H 4600 3350 39  0001 C CNN
F 3 "" H 5350 2850 60  0000 C CNN
	1    4600 3700
	1    0    0    -1  
$EndComp
Connection ~ 4750 2850
Wire Wire Line
	4750 3350 4350 3350
Wire Wire Line
	4350 3350 4350 3700
Wire Wire Line
	4350 3700 4400 3700
Connection ~ 3650 3250
Wire Wire Line
	4850 3250 3650 3250
Wire Wire Line
	4850 3700 4850 3250
Wire Wire Line
	4800 3700 4850 3700
Connection ~ 4200 4100
Wire Wire Line
	4200 4100 4200 3550
Wire Wire Line
	4200 3550 4400 3550
Wire Wire Line
	1100 4100 5450 4100
Wire Wire Line
	4800 4100 4800 3850
Wire Wire Line
	4300 3850 4400 3850
Wire Wire Line
	4300 3200 4300 3850
Connection ~ 3850 2200
Wire Wire Line
	3850 2200 3850 2850
Wire Wire Line
	3850 2850 3950 2850
Connection ~ 3300 4100
Connection ~ 1100 4100
Wire Wire Line
	3300 3550 3300 4100
Connection ~ 6100 5500
Wire Wire Line
	4750 2650 4750 3350
Connection ~ 4750 2200
Wire Wire Line
	4750 2200 4750 2350
Connection ~ 3650 2200
Wire Wire Line
	3650 2200 3650 2350
Wire Wire Line
	4650 2850 4750 2850
Wire Wire Line
	1100 3000 1100 4250
Wire Wire Line
	3650 4700 7950 4700
Wire Wire Line
	7950 4700 7950 3200
Wire Wire Line
	7950 3200 7800 3200
Wire Wire Line
	8050 3850 7800 3850
Wire Wire Line
	8050 2050 8050 3850
Wire Wire Line
	5250 2050 8050 2050
Wire Wire Line
	3650 2650 3650 4700
Connection ~ 3300 2200
Wire Wire Line
	3100 2450 3300 2450
Connection ~ 6150 2200
Wire Wire Line
	2250 1850 4950 1850
Wire Wire Line
	2250 2200 2250 1850
Wire Wire Line
	2300 2200 2250 2200
Wire Wire Line
	4950 1850 4950 1500
Connection ~ 6150 3650
Connection ~ 6150 3850
Wire Wire Line
	6150 3850 6300 3850
Connection ~ 6150 3750
Wire Wire Line
	6150 3750 6300 3750
Wire Wire Line
	6150 2200 6150 3950
Wire Wire Line
	6150 3950 6300 3950
Wire Wire Line
	6300 3650 6150 3650
Wire Wire Line
	8550 2700 8550 3000
Connection ~ 8200 4500
Wire Wire Line
	8200 5500 8200 4100
Wire Wire Line
	8200 4500 7800 4500
Wire Wire Line
	5250 1500 5250 2050
Connection ~ 3300 2700
Wire Wire Line
	5550 2800 6300 2800
Wire Wire Line
	5550 1500 5550 2800
Wire Wire Line
	5050 3400 6300 3400
Wire Wire Line
	5050 1500 5050 3400
Wire Wire Line
	5350 3250 6300 3250
Wire Wire Line
	5350 1500 5350 3250
Wire Wire Line
	4950 5500 8200 5500
Wire Wire Line
	6100 5500 6100 5400
Connection ~ 8200 4400
Wire Wire Line
	8200 4400 7800 4400
Connection ~ 8200 4300
Wire Wire Line
	7800 4300 8400 4300
Connection ~ 8200 4200
Wire Wire Line
	7800 4200 8200 4200
Wire Wire Line
	5800 5500 5800 5400
Wire Wire Line
	5800 4100 5800 4800
Wire Wire Line
	5800 4100 6300 4100
Wire Wire Line
	6100 4400 6100 4800
Wire Wire Line
	6100 4400 6300 4400
Wire Wire Line
	5150 1500 5150 3150
Wire Wire Line
	5150 3150 6300 3150
Wire Wire Line
	8550 3500 7800 3500
Wire Wire Line
	8550 3200 8550 3500
Connection ~ 8550 2200
Wire Wire Line
	8550 2200 8550 2400
Connection ~ 7850 2200
Wire Wire Line
	9250 2200 9250 2050
Wire Wire Line
	8200 4100 7800 4100
Wire Wire Line
	7850 2200 7850 2800
Wire Wire Line
	7850 2800 7800 2800
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
	3100 2200 9250 2200
Connection ~ 3300 2450
Wire Wire Line
	1100 2250 1100 2700
Wire Wire Line
	1100 3150 1400 3150
Text Label 4750 3200 1    60   ~ 0
RESET#
Text Label 4300 3750 1    60   ~ 0
TCM_GND
Connection ~ 5800 5500
Wire Wire Line
	4800 3550 4950 3550
Wire Wire Line
	4950 3550 4950 5500
Wire Wire Line
	5450 4100 5450 1500
Connection ~ 4800 4100
Text Label 5450 1750 1    60   ~ 0
GND
$Comp
L SW_PUSH SW3
U 1 1 5533A166
P 5200 5100
F 0 "SW3" H 5350 5210 50  0000 C CNN
F 1 "SKRPACE010" H 5200 5020 50  0000 C CNN
F 2 "favorites:SKRPACE010" H 5200 5100 60  0001 C CNN
F 3 "~" H 5200 5100 60  0000 C CNN
	1    5200 5100
	0    1    1    0   
$EndComp
Wire Wire Line
	5200 5400 5200 5500
Connection ~ 5200 5500
Wire Wire Line
	5200 4800 5200 3400
Connection ~ 5200 3400
$Comp
L PWR_FLAG #FLG05
U 1 1 5533B378
P 8400 4150
F 0 "#FLG05" H 8400 4245 50  0001 C CNN
F 1 "PWR_FLAG" H 8400 4330 50  0000 C CNN
F 2 "" H 8400 4150 60  0000 C CNN
F 3 "" H 8400 4150 60  0000 C CNN
	1    8400 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 4300 8400 4150
Connection ~ 1100 3150
$EndSCHEMATC
