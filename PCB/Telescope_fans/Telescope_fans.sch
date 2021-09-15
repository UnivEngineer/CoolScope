EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
NoConn ~ 5250 2450
Wire Wire Line
	2900 3250 4650 3250
Wire Wire Line
	3750 3750 4650 3750
Wire Wire Line
	4050 3850 4650 3850
NoConn ~ 4650 2950
NoConn ~ 4650 2850
NoConn ~ 5650 2950
NoConn ~ 5650 2850
NoConn ~ 5650 3250
Wire Wire Line
	4350 5700 8150 5700
NoConn ~ 6650 3550
NoConn ~ 6650 3450
NoConn ~ 6650 3350
NoConn ~ 6650 3650
Wire Wire Line
	6050 4050 6050 3450
Wire Wire Line
	6050 3450 5650 3450
Wire Wire Line
	6050 4050 6650 4050
Wire Wire Line
	6650 3850 6250 3850
Wire Wire Line
	6250 3850 6250 3650
Wire Wire Line
	5850 2850 5850 3850
Wire Wire Line
	5850 3850 5650 3850
Wire Wire Line
	5850 2850 6650 2850
Wire Wire Line
	5650 3950 5950 3950
Wire Wire Line
	5950 3950 5950 3050
Wire Wire Line
	5950 3050 6650 3050
Wire Wire Line
	5650 3650 6250 3650
Wire Wire Line
	5650 3550 6150 3550
Wire Wire Line
	6150 3550 6150 3950
Wire Wire Line
	6150 3950 6650 3950
Wire Wire Line
	5650 3750 6650 3750
Wire Wire Line
	7450 3150 7550 3150
NoConn ~ 4650 4150
$Comp
L power:PWR_FLAG #FLG03
U 1 1 6153661B
P 7550 3100
F 0 "#FLG03" H 7550 3175 50  0001 C CNN
F 1 "PWR_FLAG" H 7550 3273 50  0000 C CNN
F 2 "" H 7550 3100 50  0001 C CNN
F 3 "~" H 7550 3100 50  0001 C CNN
	1    7550 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 3100 7550 3150
Connection ~ 7550 3150
Wire Wire Line
	3900 3050 3900 6550
Wire Wire Line
	4200 3150 4200 7150
Wire Wire Line
	4200 7150 2400 7150
Wire Wire Line
	3750 3750 3750 6450
Wire Wire Line
	4050 3850 4050 7050
Wire Wire Line
	4050 7050 2400 7050
$Comp
L power:GND #PWR022
U 1 1 61638967
P 6550 2950
F 0 "#PWR022" H 6550 2700 50  0001 C CNN
F 1 "GND" H 6555 2777 50  0000 C CNN
F 2 "" H 6550 2950 50  0001 C CNN
F 3 "" H 6550 2950 50  0001 C CNN
	1    6550 2950
	0    1    1    0   
$EndComp
Wire Wire Line
	6550 2950 6650 2950
$Comp
L power:GND #PWR018
U 1 1 6165D9F6
P 5650 4450
F 0 "#PWR018" H 5650 4200 50  0001 C CNN
F 1 "GND" H 5655 4277 50  0000 C CNN
F 2 "" H 5650 4450 50  0001 C CNN
F 3 "" H 5650 4450 50  0001 C CNN
	1    5650 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR025
U 1 1 6167281E
P 7550 3350
F 0 "#PWR025" H 7550 3100 50  0001 C CNN
F 1 "GND" H 7555 3177 50  0000 C CNN
F 2 "" H 7550 3350 50  0001 C CNN
F 3 "" H 7550 3350 50  0001 C CNN
	1    7550 3350
	1    0    0    -1  
$EndComp
$Comp
L Display_Character:WC1602A DS1
U 1 1 61144E8E
P 7050 3450
F 0 "DS1" H 7050 4431 50  0000 C CNN
F 1 "WC1602A" H 7050 4340 50  0000 C CNN
F 2 "Display:WC1602A" H 7050 2550 50  0001 C CIN
F 3 "http://www.wincomlcd.com/pdf/WC1602A-SFYLYHTC06.pdf" H 7750 3450 50  0001 C CNN
	1    7050 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 3250 7550 3250
Wire Wire Line
	7550 3250 7550 3350
Wire Wire Line
	7450 2850 8150 2850
Wire Wire Line
	8150 2850 8150 5700
Wire Wire Line
	4650 3950 2600 3950
Wire Wire Line
	2750 3550 4650 3550
$Comp
L Jumper:Jumper_3_Bridged12 JP1
U 1 1 619A1805
P 5850 5100
F 0 "JP1" H 5850 5211 50  0000 C CNN
F 1 "OLED/LCD" H 5850 5302 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 5850 5100 50  0001 C CNN
F 3 "~" H 5850 5100 50  0001 C CNN
	1    5850 5100
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR024
U 1 1 61365FEA
P 7050 4500
F 0 "#PWR024" H 7050 4250 50  0001 C CNN
F 1 "GND" H 7055 4327 50  0000 C CNN
F 2 "" H 7050 4500 50  0001 C CNN
F 3 "" H 7050 4500 50  0001 C CNN
	1    7050 4500
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR017
U 1 1 619B8938
P 5600 5100
F 0 "#PWR017" H 5600 4950 50  0001 C CNN
F 1 "+5V" V 5615 5228 50  0000 L CNN
F 2 "" H 5600 5100 50  0001 C CNN
F 3 "" H 5600 5100 50  0001 C CNN
	1    5600 5100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5650 4150 5850 4150
Wire Wire Line
	7050 4250 7050 4500
Wire Wire Line
	5850 4150 5850 4950
$Comp
L power:GND #PWR021
U 1 1 619D86F4
P 6200 5200
F 0 "#PWR021" H 6200 4950 50  0001 C CNN
F 1 "GND" H 6205 5027 50  0000 C CNN
F 2 "" H 6200 5200 50  0001 C CNN
F 3 "" H 6200 5200 50  0001 C CNN
	1    6200 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 5200 6200 5100
Wire Wire Line
	6200 5100 6100 5100
$Comp
L Device:R R5
U 1 1 619EE533
P 6200 4600
F 0 "R5" H 6270 4646 50  0000 L CNN
F 1 "47k" H 6270 4555 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 6130 4600 50  0001 C CNN
F 3 "~" H 6200 4600 50  0001 C CNN
	1    6200 4600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 619EF2BB
P 6200 4900
F 0 "R6" H 6270 4946 50  0000 L CNN
F 1 "20k" H 6270 4855 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 6130 4900 50  0001 C CNN
F 3 "~" H 6200 4900 50  0001 C CNN
	1    6200 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 4750 5950 4750
Wire Wire Line
	5950 4750 5950 4050
Wire Wire Line
	5950 4050 5650 4050
Connection ~ 6200 4750
$Comp
L power:+12V #PWR020
U 1 1 619F8452
P 6200 4450
F 0 "#PWR020" H 6200 4300 50  0001 C CNN
F 1 "+12V" V 6215 4578 50  0000 L CNN
F 2 "" H 6200 4450 50  0001 C CNN
F 3 "" H 6200 4450 50  0001 C CNN
	1    6200 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 5050 6200 5100
Connection ~ 6200 5100
Wire Wire Line
	3900 6550 2400 6550
Wire Wire Line
	3750 6450 2400 6450
Wire Wire Line
	3900 1050 3900 950 
$Comp
L Device:C C2
U 1 1 61893592
P 4350 1350
F 0 "C2" H 4465 1396 50  0000 L CNN
F 1 "100n" H 4465 1305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 4388 1200 50  0001 C CNN
F 3 "~" H 4350 1350 50  0001 C CNN
	1    4350 1350
	1    0    0    -1  
$EndComp
Connection ~ 3900 1050
$Comp
L Device:CP C1
U 1 1 6180E443
P 3900 1350
F 0 "C1" H 4018 1396 50  0000 L CNN
F 1 "47u" H 4018 1305 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 3938 1200 50  0001 C CNN
F 3 "~" H 3900 1350 50  0001 C CNN
	1    3900 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 1500 3900 1700
$Comp
L power:PWR_FLAG #FLG02
U 1 1 6151DB94
P 3900 1800
F 0 "#FLG02" H 3900 1875 50  0001 C CNN
F 1 "PWR_FLAG" H 3900 1973 50  0000 C CNN
F 2 "" H 3900 1800 50  0001 C CNN
F 3 "~" H 3900 1800 50  0001 C CNN
	1    3900 1800
	-1   0    0    1   
$EndComp
$Comp
L power:PWR_FLAG #FLG01
U 1 1 615236F4
P 3900 950
F 0 "#FLG01" H 3900 1025 50  0001 C CNN
F 1 "PWR_FLAG" H 3900 1123 50  0000 C CNN
F 2 "" H 3900 950 50  0001 C CNN
F 3 "~" H 3900 950 50  0001 C CNN
	1    3900 950 
	1    0    0    -1  
$EndComp
$Comp
L Connector:Barrel_Jack_Switch J1
U 1 1 61148C69
P 1800 1350
F 0 "J1" H 1857 1667 50  0000 C CNN
F 1 "12V" H 1857 1576 50  0000 C CNN
F 2 "Connector_BarrelJack:BarrelJack_Horizontal" H 1850 1310 50  0001 C CNN
F 3 "~" H 1850 1310 50  0001 C CNN
	1    1800 1350
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J3
U 1 1 61146796
P 2200 6650
F 0 "J3" H 2308 6931 50  0000 C CNN
F 1 "Front fan" H 2308 6840 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 2200 6650 50  0001 C CNN
F 3 "~" H 2200 6650 50  0001 C CNN
	1    2200 6650
	1    0    0    1   
$EndComp
$Comp
L Connector:Conn_01x04_Male J4
U 1 1 61146FA9
P 2200 7250
F 0 "J4" H 2308 7531 50  0000 C CNN
F 1 "Rear fan" H 2308 7440 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 2200 7250 50  0001 C CNN
F 3 "~" H 2200 7250 50  0001 C CNN
	1    2200 7250
	1    0    0    1   
$EndComp
Wire Wire Line
	4350 5700 4350 3450
Wire Wire Line
	4500 3350 4500 5550
Wire Wire Line
	4350 3450 4650 3450
Wire Wire Line
	4650 3350 4500 3350
Wire Wire Line
	2100 1250 2200 1250
Wire Wire Line
	2200 1250 2200 1050
Wire Wire Line
	3200 1050 3300 1050
Wire Wire Line
	2100 1350 2200 1350
$Comp
L Diode:BZX84Cxx D2
U 1 1 615591C1
P 3300 1200
F 0 "D2" V 3254 1280 50  0000 L CNN
F 1 "BZX84C10" V 3345 1280 50  0000 L CNN
F 2 "Diode_SMD:D_SOT-23_ANK" H 3300 1025 50  0001 C CNN
F 3 "https://diotec.com/tl_files/diotec/files/pdf/datasheets/bzx84c2v4.pdf" H 3300 1200 50  0001 C CNN
	1    3300 1200
	0    1    1    0   
$EndComp
$Comp
L Transistor_FET:FDS9435A Q1
U 1 1 6151F7B4
P 3000 1150
F 0 "Q1" V 3342 1150 50  0000 C CNN
F 1 "FDS9435A" V 3251 1150 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 3200 1075 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/FDS9435A-D.PDF" V 3000 1150 50  0001 L CNN
	1    3000 1150
	0    -1   -1   0   
$EndComp
Connection ~ 3300 1050
Wire Wire Line
	3300 1050 3900 1050
$Comp
L Device:R R1
U 1 1 615DC088
P 3150 1500
F 0 "R1" H 3220 1546 50  0000 L CNN
F 1 "100k" H 3220 1455 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3080 1500 50  0001 C CNN
F 3 "~" H 3150 1500 50  0001 C CNN
	1    3150 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 1350 3150 1350
Connection ~ 3150 1350
Wire Wire Line
	3150 1350 3300 1350
Wire Wire Line
	2200 1350 2200 1700
Wire Wire Line
	3150 1700 3150 1650
Wire Wire Line
	3900 1050 4350 1050
Wire Wire Line
	3900 1050 3900 1200
Wire Wire Line
	4350 1200 4350 1050
Connection ~ 4350 1050
Wire Wire Line
	4350 1050 4600 1050
Wire Wire Line
	3150 1700 3900 1700
Connection ~ 3900 1700
Wire Wire Line
	3900 1700 3900 1800
Wire Wire Line
	3900 1700 4350 1700
Wire Wire Line
	4350 1500 4350 1700
Connection ~ 4350 1700
Wire Wire Line
	2100 1450 2100 1700
Wire Wire Line
	2100 1700 2200 1700
Connection ~ 2200 1700
Wire Wire Line
	2500 1200 2500 1050
Wire Wire Line
	2200 1050 2500 1050
Wire Wire Line
	2500 1050 2800 1050
Connection ~ 2500 1050
Wire Wire Line
	2200 1700 2500 1700
Connection ~ 3150 1700
Wire Wire Line
	2500 1500 2500 1700
Connection ~ 2500 1700
Wire Wire Line
	2500 1700 3150 1700
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 616A7213
P 2500 950
F 0 "#FLG0101" H 2500 1025 50  0001 C CNN
F 1 "PWR_FLAG" H 2500 1123 50  0000 C CNN
F 2 "" H 2500 950 50  0001 C CNN
F 3 "~" H 2500 950 50  0001 C CNN
	1    2500 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 950  2500 1050
$Comp
L power:+12P #PWR0101
U 1 1 61195137
P 2200 950
F 0 "#PWR0101" H 2200 800 50  0001 C CNN
F 1 "+12P" H 2215 1123 50  0000 C CNN
F 2 "" H 2200 950 50  0001 C CNN
F 3 "" H 2200 950 50  0001 C CNN
	1    2200 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 950  2200 1050
Connection ~ 2200 1050
$Comp
L Diode:SD12_SOD323 D1
U 1 1 611ACA2F
P 2500 1350
F 0 "D1" V 2454 1429 50  0000 L CNN
F 1 "SM6T12CA" V 2545 1429 50  0000 L CNN
F 2 "Diode_SMD:D_SMB_Handsoldering" H 2500 1150 50  0001 C CNN
F 3 "https://www.littelfuse.com/~/media/electronics/datasheets/tvs_diode_arrays/littelfuse_tvs_diode_array_sd_c_datasheet.pdf.pdf" H 2500 1350 50  0001 C CNN
	1    2500 1350
	0    1    1    0   
$EndComp
Wire Wire Line
	5650 4450 5250 4450
Wire Wire Line
	5250 4450 5150 4450
Connection ~ 5250 4450
$Comp
L MCU_Module:Arduino_Nano_v3.x A1
U 1 1 61141ED5
P 5150 3450
F 0 "A1" H 5150 2361 50  0000 C CNN
F 1 "Arduino Nano v3" H 5150 2270 50  0000 C CNN
F 2 "Telescope_fans:Arduino_Nano_Chinese" H 5150 3450 50  0001 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 5150 3450 50  0001 C CNN
	1    5150 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 1700 4550 1700
Wire Wire Line
	4550 1700 4550 1800
$Comp
L power:GND #PWR012
U 1 1 61876BEC
P 4550 1800
F 0 "#PWR012" H 4550 1550 50  0001 C CNN
F 1 "GND" H 4555 1627 50  0000 C CNN
F 2 "" H 4550 1800 50  0001 C CNN
F 3 "" H 4550 1800 50  0001 C CNN
	1    4550 1800
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR016
U 1 1 6176FE14
P 5350 2100
F 0 "#PWR016" H 5350 1950 50  0001 C CNN
F 1 "+5V" V 5365 2228 50  0000 L CNN
F 2 "" H 5350 2100 50  0001 C CNN
F 3 "" H 5350 2100 50  0001 C CNN
	1    5350 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 2100 5350 2200
Connection ~ 5800 2200
Wire Wire Line
	6250 2200 6250 2250
Wire Wire Line
	5800 2200 6250 2200
Connection ~ 5800 2550
Wire Wire Line
	5800 2600 5800 2550
Wire Wire Line
	5800 2550 6250 2550
$Comp
L Device:C C4
U 1 1 6182ECE9
P 6250 2400
F 0 "C4" H 6365 2446 50  0000 L CNN
F 1 "100n" H 6365 2355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 6288 2250 50  0001 C CNN
F 3 "~" H 6250 2400 50  0001 C CNN
	1    6250 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR019
U 1 1 616380C8
P 5800 2600
F 0 "#PWR019" H 5800 2350 50  0001 C CNN
F 1 "GND" H 5805 2427 50  0000 C CNN
F 2 "" H 5800 2600 50  0001 C CNN
F 3 "" H 5800 2600 50  0001 C CNN
	1    5800 2600
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C3
U 1 1 6115CE3B
P 5800 2400
F 0 "C3" H 5918 2446 50  0000 L CNN
F 1 "220u" H 5918 2355 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 5838 2250 50  0001 C CNN
F 3 "~" H 5800 2400 50  0001 C CNN
	1    5800 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 2250 5800 2200
Wire Wire Line
	5050 2450 5050 2100
$Comp
L power:+12V #PWR015
U 1 1 61765FD8
P 5050 2100
F 0 "#PWR015" H 5050 1950 50  0001 C CNN
F 1 "+12V" V 5065 2228 50  0000 L CNN
F 2 "" H 5050 2100 50  0001 C CNN
F 3 "" H 5050 2100 50  0001 C CNN
	1    5050 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 2200 5800 2200
Connection ~ 5350 2200
Wire Wire Line
	5350 2450 5350 2200
$Comp
L power:+12V #PWR013
U 1 1 61369B6D
P 4600 1050
F 0 "#PWR013" H 4600 900 50  0001 C CNN
F 1 "+12V" V 4615 1178 50  0000 L CNN
F 2 "" H 4600 1050 50  0001 C CNN
F 3 "" H 4600 1050 50  0001 C CNN
	1    4600 1050
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR014
U 1 1 6172BBFF
P 4200 2500
F 0 "#PWR014" H 4200 2350 50  0001 C CNN
F 1 "+5V" V 4215 2628 50  0000 L CNN
F 2 "" H 4200 2500 50  0001 C CNN
F 3 "" H 4200 2500 50  0001 C CNN
	1    4200 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 2600 4200 2500
Connection ~ 4200 2600
Connection ~ 3900 2600
Wire Wire Line
	4200 2600 3900 2600
Wire Wire Line
	4200 2600 4200 2650
Wire Wire Line
	3600 2950 3600 3650
Wire Wire Line
	3900 2950 3900 3050
Wire Wire Line
	4200 2950 4200 3150
Wire Wire Line
	3900 2600 3600 2600
Wire Wire Line
	3900 2650 3900 2600
Wire Wire Line
	3600 2650 3600 2600
$Comp
L Device:R R2
U 1 1 6119E62D
P 3600 2800
F 0 "R2" H 3670 2846 50  0000 L CNN
F 1 "4,7k" H 3670 2755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3530 2800 50  0001 C CNN
F 3 "~" H 3600 2800 50  0001 C CNN
	1    3600 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 6119A500
P 3900 2800
F 0 "R3" H 3970 2846 50  0000 L CNN
F 1 "2,7k" H 3970 2755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3830 2800 50  0001 C CNN
F 3 "~" H 3900 2800 50  0001 C CNN
	1    3900 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 61199D12
P 4200 2800
F 0 "R4" H 4270 2846 50  0000 L CNN
F 1 "2,7k" H 4270 2755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 4130 2800 50  0001 C CNN
F 3 "~" H 4200 2800 50  0001 C CNN
	1    4200 2800
	1    0    0    -1  
$EndComp
Connection ~ 3600 3650
Wire Wire Line
	3600 3650 4650 3650
Connection ~ 3900 3050
Wire Wire Line
	3900 3050 4650 3050
Connection ~ 4200 3150
Wire Wire Line
	4200 3150 4650 3150
$Comp
L power:GND #PWR01
U 1 1 615F1B3A
P 2050 4150
F 0 "#PWR01" H 2050 3900 50  0001 C CNN
F 1 "GND" H 2055 3977 50  0000 C CNN
F 2 "" H 2050 4150 50  0001 C CNN
F 3 "" H 2050 4150 50  0001 C CNN
	1    2050 4150
	1    0    0    -1  
$EndComp
Connection ~ 2050 4050
Wire Wire Line
	2050 4150 2050 4050
Wire Wire Line
	2500 4050 4650 4050
Wire Wire Line
	2050 4050 2100 4050
$Comp
L Switch:SW_Push SW4
U 1 1 6114C6F1
P 2300 4050
F 0 "SW4" H 2300 4335 50  0000 C CNN
F 1 "Enter" H 2300 4244 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm_H13mm" H 2300 4250 50  0001 C CNN
F 3 "~" H 2300 4250 50  0001 C CNN
	1    2300 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 3950 2600 3650
Wire Wire Line
	2050 3650 2050 4050
Connection ~ 2050 3650
Wire Wire Line
	2600 3650 2500 3650
Wire Wire Line
	2100 3650 2050 3650
$Comp
L Switch:SW_Push SW3
U 1 1 6114BBF5
P 2300 3650
F 0 "SW3" H 2300 3935 50  0000 C CNN
F 1 "Next" H 2300 3844 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm_H13mm" H 2300 3850 50  0001 C CNN
F 3 "~" H 2300 3850 50  0001 C CNN
	1    2300 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 3250 2750 3550
Wire Wire Line
	2050 3250 2050 3650
Connection ~ 2050 3250
Wire Wire Line
	2750 3250 2500 3250
Wire Wire Line
	2100 3250 2050 3250
$Comp
L Switch:SW_Push SW2
U 1 1 6114B5C6
P 2300 3250
F 0 "SW2" H 2300 3535 50  0000 C CNN
F 1 "Prev" H 2300 3444 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm_H13mm" H 2300 3450 50  0001 C CNN
F 3 "~" H 2300 3450 50  0001 C CNN
	1    2300 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 2850 2900 3250
Wire Wire Line
	2050 2850 2050 3250
Wire Wire Line
	2500 2850 2900 2850
Wire Wire Line
	2050 2850 2100 2850
$Comp
L Switch:SW_Push SW1
U 1 1 6114A492
P 2300 2850
F 0 "SW1" H 2300 3135 50  0000 C CNN
F 1 "Back" H 2300 3044 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm_H13mm" H 2300 3050 50  0001 C CNN
F 3 "~" H 2300 3050 50  0001 C CNN
	1    2300 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 7350 2550 7350
$Comp
L power:GND #PWR07
U 1 1 61546B4F
P 2550 7350
F 0 "#PWR07" H 2550 7100 50  0001 C CNN
F 1 "GND" H 2555 7177 50  0000 C CNN
F 2 "" H 2550 7350 50  0001 C CNN
F 3 "" H 2550 7350 50  0001 C CNN
	1    2550 7350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 7250 2550 7250
$Comp
L power:+12V #PWR06
U 1 1 6153D727
P 2550 7250
F 0 "#PWR06" H 2550 7100 50  0001 C CNN
F 1 "+12V" V 2565 7378 50  0000 L CNN
F 2 "" H 2550 7250 50  0001 C CNN
F 3 "" H 2550 7250 50  0001 C CNN
	1    2550 7250
	0    1    1    0   
$EndComp
Wire Wire Line
	2400 6650 2550 6650
$Comp
L power:+12V #PWR04
U 1 1 6153BCF9
P 2550 6650
F 0 "#PWR04" H 2550 6500 50  0001 C CNN
F 1 "+12V" V 2565 6778 50  0000 L CNN
F 2 "" H 2550 6650 50  0001 C CNN
F 3 "" H 2550 6650 50  0001 C CNN
	1    2550 6650
	0    1    1    0   
$EndComp
Wire Wire Line
	2400 6750 2550 6750
$Comp
L power:GND #PWR05
U 1 1 615A4AD2
P 2550 6750
F 0 "#PWR05" H 2550 6500 50  0001 C CNN
F 1 "GND" H 2555 6577 50  0000 C CNN
F 2 "" H 2550 6750 50  0001 C CNN
F 3 "" H 2550 6750 50  0001 C CNN
	1    2550 6750
	1    0    0    -1  
$EndComp
Connection ~ 2600 5300
Wire Wire Line
	2900 4400 2900 5050
Wire Wire Line
	2300 5000 2600 5000
Wire Wire Line
	2550 5400 2750 5400
Wire Wire Line
	2600 5300 2550 5300
$Comp
L Sensor_Temperature:DS18B20 U1
U 1 1 6138A4BF
P 2300 4700
F 0 "U1" H 2070 4746 50  0000 R CNN
F 1 "DS18B20" H 2070 4655 50  0000 R CNN
F 2 "Package_TO_SOT_THT:TO-92L_Inline_Wide" H 1300 4450 50  0001 C CNN
F 3 "http://datasheets.maximintegrated.com/en/ds/DS18B20.pdf" H 2150 4950 50  0001 C CNN
	1    2300 4700
	1    0    0    -1  
$EndComp
$Comp
L Connector:AudioJack3 J5
U 1 1 611494B6
P 2350 5400
F 0 "J5" H 2332 5725 50  0000 C CNN
F 1 "Temp sensor" H 2332 5634 50  0000 C CNN
F 2 "Connector_Audio:Jack_3.5mm_CUI_SJ1-3533NG_Horizontal" H 2350 5400 50  0001 C CNN
F 3 "~" H 2350 5400 50  0001 C CNN
	1    2350 5400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR010
U 1 1 61613080
P 3200 4400
F 0 "#PWR010" H 3200 4250 50  0001 C CNN
F 1 "+5V" V 3215 4528 50  0000 L CNN
F 2 "" H 3200 4400 50  0001 C CNN
F 3 "" H 3200 4400 50  0001 C CNN
	1    3200 4400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 616907EB
P 3200 5600
F 0 "#PWR0102" H 3200 5350 50  0001 C CNN
F 1 "GND" H 3205 5427 50  0000 C CNN
F 2 "" H 3200 5600 50  0001 C CNN
F 3 "" H 3200 5600 50  0001 C CNN
	1    3200 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 611E69FF
P 3200 5450
F 0 "C5" H 3315 5496 50  0000 L CNN
F 1 "680n" H 3315 5405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 3238 5300 50  0001 C CNN
F 3 "~" H 3200 5450 50  0001 C CNN
	1    3200 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 5300 2600 5000
$Comp
L Connector:Conn_01x03_Male J2
U 1 1 61147C02
P 2200 6050
F 0 "J2" H 2308 6331 50  0000 C CNN
F 1 "Temp sensor" H 2308 6240 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 2200 6050 50  0001 C CNN
F 3 "~" H 2200 6050 50  0001 C CNN
	1    2200 6050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 614FDB8B
P 3200 4700
F 0 "R8" H 3270 4746 50  0000 L CNN
F 1 "100" H 3270 4655 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3130 4700 50  0001 C CNN
F 3 "~" H 3200 4700 50  0001 C CNN
	1    3200 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 5050 3200 4850
Wire Wire Line
	2550 5500 2900 5500
Wire Wire Line
	2600 4700 2750 4700
Wire Wire Line
	2750 4700 2750 5400
Connection ~ 2750 5400
Wire Wire Line
	2750 5400 2750 5950
Wire Wire Line
	2750 5950 3600 5950
Wire Wire Line
	3600 3650 3600 5950
Wire Wire Line
	2900 5050 3200 5050
Connection ~ 2900 5050
Wire Wire Line
	2900 5050 2900 5500
Wire Wire Line
	3200 5050 3200 5300
Connection ~ 3200 5050
Wire Wire Line
	8000 5550 8000 3150
Wire Wire Line
	7550 3150 7650 3150
Wire Wire Line
	7950 3150 8000 3150
$Comp
L Device:R R7
U 1 1 611A839E
P 7800 3150
F 0 "R7" V 7593 3150 50  0000 C CNN
F 1 "220" V 7684 3150 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 7730 3150 50  0001 C CNN
F 3 "~" H 7800 3150 50  0001 C CNN
	1    7800 3150
	0    1    1    0   
$EndComp
Wire Wire Line
	2400 5950 2750 5950
Connection ~ 2750 5950
Connection ~ 2900 5500
Wire Wire Line
	2600 5300 2600 6050
$Comp
L power:GND #PWR0104
U 1 1 6122C353
P 2600 6200
F 0 "#PWR0104" H 2600 5950 50  0001 C CNN
F 1 "GND" H 2605 6027 50  0000 C CNN
F 2 "" H 2600 6200 50  0001 C CNN
F 3 "" H 2600 6200 50  0001 C CNN
	1    2600 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 6050 2600 6050
Connection ~ 2600 6050
Wire Wire Line
	2600 6050 2600 6200
Wire Wire Line
	2400 6150 2900 6150
Wire Wire Line
	2900 5500 2900 6150
$Comp
L power:+5VL #PWR0103
U 1 1 618528E1
P 2900 4400
F 0 "#PWR0103" H 2900 4250 50  0001 C CNN
F 1 "+5VL" V 2915 4528 50  0000 L CNN
F 2 "" H 2900 4400 50  0001 C CNN
F 3 "" H 2900 4400 50  0001 C CNN
	1    2900 4400
	1    0    0    -1  
$EndComp
Connection ~ 2900 4400
Wire Wire Line
	3200 4400 3200 4550
Wire Wire Line
	6250 2200 7050 2200
Wire Wire Line
	7050 2200 7050 2650
Connection ~ 6250 2200
Wire Wire Line
	2300 4400 2600 4400
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 612B3D3C
P 2600 4400
F 0 "#FLG0102" H 2600 4475 50  0001 C CNN
F 1 "PWR_FLAG" H 2600 4573 50  0000 C CNN
F 2 "" H 2600 4400 50  0001 C CNN
F 3 "~" H 2600 4400 50  0001 C CNN
	1    2600 4400
	1    0    0    -1  
$EndComp
Connection ~ 2600 4400
Wire Wire Line
	2600 4400 2900 4400
Wire Wire Line
	4500 5550 8000 5550
$EndSCHEMATC
