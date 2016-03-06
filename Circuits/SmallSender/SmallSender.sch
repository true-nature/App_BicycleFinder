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
P 9400 3100
F 0 "LD1" H 9400 3200 50  0000 C CNN
F 1 "SML-012WT" H 9400 3000 50  0000 C CNN
F 2 "favorites:LED-1206" H 9400 3100 60  0001 C CNN
F 3 "~" H 9400 3100 60  0000 C CNN
	1    9400 3100
	0    1    -1   0   
$EndComp
Text Label 1900 2450 0    60   ~ 0
3V
$Comp
L R R1
U 1 1 54AE44D9
P 9400 2550
F 0 "R1" V 9480 2550 40  0000 C CNN
F 1 "680" V 9407 2551 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 9330 2550 30  0001 C CNN
F 3 "~" H 9400 2550 30  0000 C CNN
	1    9400 2550
	1    0    0    -1  
$EndComp
$Comp
L HN2S01FU U2
U 1 1 54B6402D
P 2900 2450
F 0 "U2" H 2800 3000 60  0000 C CNN
F 1 "HN2S01FU" H 2900 2900 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SC-70-6_Handsoldering" H 2900 2450 60  0001 C CNN
F 3 "" H 2900 2450 60  0000 C CNN
	1    2900 2450
	-1   0    0    -1  
$EndComp
Text Label 7350 2200 0    60   ~ 0
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
P 7900 3450
F 0 "U1" H 7900 3350 50  0000 C CNN
F 1 "TWE_LITE_SMD" H 7900 4250 50  0000 C CNN
F 2 "favorites:TWE-001L-NC7" H 7650 2200 50  0001 C CNN
F 3 "DOCUMENTATION" H 8250 2200 50  0001 C CNN
	1    7900 3450
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
NoConn ~ 7150 3000
NoConn ~ 8650 2950
NoConn ~ 8650 3050
NoConn ~ 8650 3300
NoConn ~ 8650 3650
NoConn ~ 8650 3750
NoConn ~ 8650 3950
NoConn ~ 7150 4200
NoConn ~ 7150 4300
NoConn ~ 8650 3400
$Comp
L PWR_FLAG #FLG03
U 1 1 54E48789
P 9400 1950
F 0 "#FLG03" H 9400 2045 30  0001 C CNN
F 1 "PWR_FLAG" H 9400 2130 30  0000 C CNN
F 2 "" H 9400 1950 60  0000 C CNN
F 3 "" H 9400 1950 60  0000 C CNN
	1    9400 1950
	1    0    0    -1  
$EndComp
NoConn ~ 7150 3500
Text Label 9050 3500 0    60   ~ 0
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
Text Label 6700 4100 0    60   ~ 0
DI1
Text Label 6950 4400 0    60   ~ 0
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
Text Label 5650 1750 1    60   ~ 0
GND
$Comp
L SW_PUSH SW4
U 1 1 5533A166
P 5050 3750
F 0 "SW4" H 5200 3860 50  0000 C CNN
F 1 "SKRPACE010" H 5050 3670 50  0000 C CNN
F 2 "favorites:SKRPACE010" H 5050 3750 60  0001 C CNN
F 3 "~" H 5050 3750 60  0000 C CNN
	1    5050 3750
	0    1    1    0   
$EndComp
NoConn ~ 8650 3200
Text Label 9400 2950 1    60   ~ 0
LED
$Comp
L C_Small C1
U 1 1 55941ACA
P 3500 3350
F 0 "C1" H 3510 3420 50  0000 L CNN
F 1 "10u" H 3510 3270 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 3500 3350 60  0001 C CNN
F 3 "" H 3500 3350 60  0000 C CNN
	1    3500 3350
	1    0    0    -1  
$EndComp
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
NoConn ~ 8650 4300
NoConn ~ 8650 4400
NoConn ~ 8650 4500
$Comp
L BD45231G U3
U 1 1 56C5B5D5
P 4200 3050
F 0 "U3" H 4200 3300 60  0000 C CNN
F 1 "BD45231G" H 4200 2800 60  0000 C CNN
F 2 "favorites:SSOP5_Handsoldering" H 4200 3050 60  0001 C CNN
F 3 "" H 4200 3050 60  0000 C CNN
	1    4200 3050
	1    0    0    -1  
$EndComp
$Comp
L C_Small C2
U 1 1 56C6FB07
P 4600 3650
F 0 "C2" H 4610 3720 50  0000 L CNN
F 1 "1000p" H 4610 3570 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 4600 3650 60  0001 C CNN
F 3 "" H 4600 3650 60  0000 C CNN
	1    4600 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 4100 5650 4100
Connection ~ 1850 4100
Connection ~ 6550 5500
Wire Wire Line
	1850 3000 1850 4250
Wire Wire Line
	8900 3850 8650 3850
Wire Wire Line
	8900 2050 8900 3850
Wire Wire Line
	5450 2050 8900 2050
Wire Wire Line
	3300 2450 3500 2450
Connection ~ 7000 2200
Wire Wire Line
	2450 2200 2450 1850
Wire Wire Line
	2500 2200 2450 2200
Wire Wire Line
	5150 1850 5150 1500
Connection ~ 7000 3650
Connection ~ 7000 3850
Wire Wire Line
	6900 3850 7150 3850
Connection ~ 7000 3750
Wire Wire Line
	7000 3750 7150 3750
Wire Wire Line
	7000 2200 7000 3950
Wire Wire Line
	7000 3950 7150 3950
Wire Wire Line
	6800 3650 7150 3650
Wire Wire Line
	9050 5500 9050 4100
Wire Wire Line
	5450 1500 5450 2050
Connection ~ 3500 2700
Wire Wire Line
	5750 2800 7150 2800
Wire Wire Line
	5750 1500 5750 2800
Wire Wire Line
	5050 3400 7150 3400
Wire Wire Line
	5250 1500 5250 3400
Wire Wire Line
	5550 3250 7150 3250
Wire Wire Line
	5550 1500 5550 3250
Wire Wire Line
	5650 5500 9050 5500
Wire Wire Line
	6550 5500 6550 5400
Connection ~ 9050 4200
Wire Wire Line
	8650 4200 9050 4200
Wire Wire Line
	6250 5500 6250 5400
Wire Wire Line
	6250 3650 6250 4800
Wire Wire Line
	5950 4100 7150 4100
Wire Wire Line
	6550 3850 6550 4800
Wire Wire Line
	6550 4400 7150 4400
Wire Wire Line
	5350 1500 5350 3150
Wire Wire Line
	5350 3150 7150 3150
Wire Wire Line
	9400 3500 8650 3500
Wire Wire Line
	9400 3200 9400 3500
Connection ~ 9400 2200
Wire Wire Line
	9400 1950 9400 2400
Connection ~ 8700 2200
Wire Wire Line
	9050 4100 8650 4100
Wire Wire Line
	8700 2200 8700 2800
Wire Wire Line
	8700 2800 8650 2800
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
Connection ~ 1850 3150
Connection ~ 3500 2200
Connection ~ 5650 4100
Wire Wire Line
	9400 3000 9400 2700
Connection ~ 3500 4100
Wire Wire Line
	3500 3450 3500 4100
Wire Wire Line
	1850 2450 2500 2450
Wire Wire Line
	3300 2200 9400 2200
Wire Wire Line
	2450 1850 5150 1850
Wire Wire Line
	5950 4800 5950 4100
Connection ~ 6250 4100
Wire Wire Line
	5950 5400 5950 5500
Connection ~ 5950 5500
Wire Wire Line
	3850 2950 3750 2950
Wire Wire Line
	3750 2950 3750 4100
Wire Wire Line
	3850 3050 3750 3050
Connection ~ 3750 3050
Wire Wire Line
	3750 3150 3850 3150
Wire Wire Line
	4550 3150 5250 3150
Connection ~ 5250 3150
Wire Wire Line
	3750 4100 3800 4100
Connection ~ 3800 4100
Connection ~ 3750 3150
Wire Wire Line
	4550 2950 4600 2950
Wire Wire Line
	4600 2950 4600 2200
Connection ~ 4600 2200
Wire Wire Line
	4600 3550 4600 3150
Connection ~ 4600 3150
Wire Wire Line
	4600 3750 4600 4100
Connection ~ 4600 4100
Wire Wire Line
	5050 4050 5050 4100
Connection ~ 5050 4100
$Comp
L R R2
U 1 1 56D32256
P 6650 3650
F 0 "R2" V 6730 3650 40  0000 C CNN
F 1 "1M" V 6657 3651 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 6580 3650 30  0001 C CNN
F 3 "~" H 6650 3650 30  0000 C CNN
	1    6650 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	6500 3650 6250 3650
$Comp
L R R3
U 1 1 56D32961
P 6750 3850
F 0 "R3" V 6830 3850 40  0000 C CNN
F 1 "1M" V 6757 3851 40  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 6680 3850 30  0001 C CNN
F 3 "~" H 6750 3850 30  0000 C CNN
	1    6750 3850
	0    1    1    0   
$EndComp
Wire Wire Line
	6600 3850 6550 3850
Connection ~ 6550 4400
NoConn ~ 7150 2900
Connection ~ 5250 3400
Wire Wire Line
	5050 3450 5050 3400
$EndSCHEMATC
