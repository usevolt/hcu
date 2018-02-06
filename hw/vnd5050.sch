EESchema Schematic File Version 2
LIBS:esb-rescue
LIBS:kemet
LIBS:usevolt
LIBS:wurth_elektronik_LED
LIBS:power
LIBS:yageo
LIBS:esb-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 13
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 5800 4100 2    60   Output ~ 0
OUT1
Text HLabel 5800 4400 2    60   Output ~ 0
OUT2
Text HLabel 2550 3450 0    60   Input ~ 0
IN1
Text HLabel 2550 4000 0    60   Input ~ 0
IN2
Text HLabel 2550 3350 0    60   Output ~ 0
SENSE1
Text HLabel 2550 4200 0    60   Output ~ 0
SENSE2
$Comp
L VND5050AJTR-E U401
U 1 1 59D8088A
P 4600 4000
AR Path="/5A015FC0/59D8088A" Ref="U401"  Part="1" 
AR Path="/5A02A41F/59D8088A" Ref="U901"  Part="1" 
AR Path="/5A12B58E/59D8088A" Ref="U401"  Part="1" 
F 0 "U401" H 4700 4447 60  0000 C CNN
F 1 "VND5050AJTR-E" H 4700 4341 60  0000 C CNN
F 2 "usevolt:PowerSSO-12" H 4600 4400 60  0001 C CNN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/group2/a5/e5/14/55/09/93/43/94/CD00103333/files/CD00103333.pdf/jcr:content/translations/en.CD00103333.pdf" H 4600 4400 60  0001 C CNN
F 4 "497-11474-1-ND" H 5000 4800 60  0001 C CNN "1st Source Part Number"
F 5 "Digikey" H 4900 4700 60  0001 C CNN "1st Source"
F 6 "STMicroelectronics" H 4700 4500 60  0001 C CNN "Manufacturer"
F 7 "VND5050AJTR-E" H 4800 4600 60  0001 C CNN "Manufacturer Part Number"
	1    4600 4000
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR402
U 1 1 59D808C7
P 5250 3650
AR Path="/5A015FC0/59D808C7" Ref="#PWR402"  Part="1" 
AR Path="/5A02A41F/59D808C7" Ref="#PWR902"  Part="1" 
AR Path="/5A12B58E/59D808C7" Ref="#PWR033"  Part="1" 
F 0 "#PWR033" H 5250 3500 50  0001 C CNN
F 1 "VDD" H 5267 3823 50  0000 C CNN
F 2 "" H 5250 3650 50  0000 C CNN
F 3 "" H 5250 3650 50  0000 C CNN
	1    5250 3650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR401
U 1 1 59D86DC2
P 2950 4450
AR Path="/5A015FC0/59D86DC2" Ref="#PWR401"  Part="1" 
AR Path="/5A02A41F/59D86DC2" Ref="#PWR901"  Part="1" 
AR Path="/5A12B58E/59D86DC2" Ref="#PWR034"  Part="1" 
F 0 "#PWR034" H 2950 4200 50  0001 C CNN
F 1 "GND" H 2955 4277 50  0000 C CNN
F 2 "" H 2950 4450 50  0000 C CNN
F 3 "" H 2950 4450 50  0000 C CNN
	1    2950 4450
	1    0    0    -1  
$EndComp
$Comp
L 390 R402
U 1 1 59D88771
P 3150 4100
AR Path="/5A015FC0/59D88771" Ref="R402"  Part="1" 
AR Path="/5A02A41F/59D88771" Ref="R902"  Part="1" 
AR Path="/5A12B58E/59D88771" Ref="R402"  Part="1" 
F 0 "R402" H 3200 4284 45  0000 C CNN
F 1 "390" H 3200 4200 45  0000 C CNN
F 2 "yageo:0603" H 3180 4250 20  0001 C CNN
F 3 "" H 3119 4139 60  0001 C CNN
F 4 "" H 3519 4539 60  0001 C CNN "1st Source Part Number"
F 5 "Digikey" H 3419 4439 60  0001 C CNN "1st Source"
F 6 "RC0603FR-07390RL" H 3319 4339 60  0001 C CNN "Manufacturer Part Number"
F 7 "YAGEO" H 3219 4239 60  0001 C CNN "Manufacturer"
	1    3150 4100
	1    0    0    -1  
$EndComp
$Comp
L 390 R401
U 1 1 59D88845
P 3150 3550
AR Path="/5A015FC0/59D88845" Ref="R401"  Part="1" 
AR Path="/5A02A41F/59D88845" Ref="R901"  Part="1" 
AR Path="/5A12B58E/59D88845" Ref="R401"  Part="1" 
F 0 "R401" H 3200 3734 45  0000 C CNN
F 1 "390" H 3200 3650 45  0000 C CNN
F 2 "yageo:0603" H 3180 3700 20  0001 C CNN
F 3 "" H 3119 3589 60  0001 C CNN
F 4 "" H 3519 3989 60  0001 C CNN "1st Source Part Number"
F 5 "Digikey" H 3419 3889 60  0001 C CNN "1st Source"
F 6 "RC0603FR-07390RL" H 3319 3789 60  0001 C CNN "Manufacturer Part Number"
F 7 "YAGEO" H 3219 3689 60  0001 C CNN "Manufacturer"
	1    3150 3550
	1    0    0    -1  
$EndComp
$Comp
L 1K R403
U 1 1 5A05950C
P 2750 3550
AR Path="/5A015FC0/5A05950C" Ref="R403"  Part="1" 
AR Path="/5A02A41F/5A05950C" Ref="R903"  Part="1" 
AR Path="/5A12B58E/5A05950C" Ref="R403"  Part="1" 
F 0 "R403" H 2800 3734 45  0000 C CNN
F 1 "1K" H 2800 3650 45  0000 C CNN
F 2 "yageo:0603" H 2780 3700 20  0001 C CNN
F 3 "" H 2719 3589 60  0001 C CNN
F 4 "" H 3119 3989 60  0001 C CNN "1st Source Part Number"
F 5 "Digikey" H 3019 3889 60  0001 C CNN "1st Source"
F 6 "RC0603FR-071KL" H 2919 3789 60  0001 C CNN "Manufacturer Part Number"
F 7 "YAGEO" H 2819 3689 60  0001 C CNN "Manufacturer"
	1    2750 3550
	1    0    0    -1  
$EndComp
$Comp
L 1K R404
U 1 1 5A059568
P 2750 4100
AR Path="/5A015FC0/5A059568" Ref="R404"  Part="1" 
AR Path="/5A02A41F/5A059568" Ref="R904"  Part="1" 
AR Path="/5A12B58E/5A059568" Ref="R404"  Part="1" 
F 0 "R404" H 2800 4284 45  0000 C CNN
F 1 "1K" H 2800 4200 45  0000 C CNN
F 2 "yageo:0603" H 2780 4250 20  0001 C CNN
F 3 "" H 2719 4139 60  0001 C CNN
F 4 "" H 3119 4539 60  0001 C CNN "1st Source Part Number"
F 5 "Digikey" H 3019 4439 60  0001 C CNN "1st Source"
F 6 "RC0603FR-071KL" H 2919 4339 60  0001 C CNN "Manufacturer Part Number"
F 7 "YAGEO" H 2819 4239 60  0001 C CNN "Manufacturer"
	1    2750 4100
	1    0    0    -1  
$EndComp
$Comp
L DIODE_RS07J-GS18 D701
U 1 1 5A2AAF9E
P 5450 4750
F 0 "D701" V 5400 4652 45  0000 R CNN
F 1 "DIODE_RS07J-GS18" H 5470 4690 45  0001 L BNN
F 2 "usevolt:DO219AB" H 5480 4900 20  0001 C CNN
F 3 "http://www.vishay.com/docs/85742/rs07b.pdf" H 5470 4770 60  0001 C CNN
F 4 "1864882" H 6070 5370 60  0001 C CNN "2nd Source Part Number"
F 5 "Digi-Key" H 5770 5070 60  0001 C CNN "1st Source"
F 6 "Farnell" H 5970 5270 60  0001 C CNN "2nd Source"
F 7 "RS07J-GS18" H 5670 4970 60  0001 C CNN "Manufacturer Part Number"
F 8 "RS07J-GS18-ND" H 5870 5170 60  0001 C CNN "1st Source Part Number"
F 9 "Vishay Semiconductor Diodes Division" H 5570 4870 60  0001 C CNN "Manufacturer"
	1    5450 4750
	0    -1   -1   0   
$EndComp
$Comp
L DIODE_RS07J-GS18 D702
U 1 1 5A2AB087
P 5700 4750
F 0 "D702" V 5650 4652 45  0000 R CNN
F 1 "DIODE_RS07J-GS18" H 5720 4690 45  0001 L BNN
F 2 "usevolt:DO219AB" H 5730 4900 20  0001 C CNN
F 3 "http://www.vishay.com/docs/85742/rs07b.pdf" H 5720 4770 60  0001 C CNN
F 4 "1864882" H 6320 5370 60  0001 C CNN "2nd Source Part Number"
F 5 "Digi-Key" H 6020 5070 60  0001 C CNN "1st Source"
F 6 "Farnell" H 6220 5270 60  0001 C CNN "2nd Source"
F 7 "RS07J-GS18" H 5920 4970 60  0001 C CNN "Manufacturer Part Number"
F 8 "RS07J-GS18-ND" H 6120 5170 60  0001 C CNN "1st Source Part Number"
F 9 "Vishay Semiconductor Diodes Division" H 5820 4870 60  0001 C CNN "Manufacturer"
	1    5700 4750
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR035
U 1 1 5A2AB10F
P 5550 5150
F 0 "#PWR035" H 5550 4900 50  0001 C CNN
F 1 "GND" H 5555 4977 50  0000 C CNN
F 2 "" H 5550 5150 50  0000 C CNN
F 3 "" H 5550 5150 50  0000 C CNN
	1    5550 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 3650 5250 4000
Wire Wire Line
	5250 3800 5100 3800
Wire Wire Line
	5250 3900 5100 3900
Connection ~ 5250 3800
Wire Wire Line
	5250 4000 5100 4000
Connection ~ 5250 3900
Wire Wire Line
	5100 4100 5800 4100
Wire Wire Line
	5100 4200 5250 4200
Wire Wire Line
	5250 4200 5250 4100
Connection ~ 5250 4100
Wire Wire Line
	5100 4400 5800 4400
Wire Wire Line
	5100 4300 5250 4300
Wire Wire Line
	5250 4300 5250 4400
Connection ~ 5250 4400
Wire Wire Line
	2550 3450 4300 3450
Wire Wire Line
	2550 4000 4300 4000
Wire Wire Line
	2950 3550 2950 4450
Wire Wire Line
	2950 4300 4300 4300
Wire Wire Line
	3050 3550 2950 3550
Connection ~ 2950 4300
Wire Wire Line
	3050 4100 2950 4100
Connection ~ 2950 4100
Wire Wire Line
	3350 4100 4300 4100
Wire Wire Line
	3350 3550 4150 3550
Wire Wire Line
	2550 4200 3500 4200
Wire Wire Line
	3500 4200 3500 4100
Connection ~ 3500 4100
Wire Wire Line
	3500 3550 3500 3350
Wire Wire Line
	3500 3350 2550 3350
Connection ~ 3500 3550
Wire Wire Line
	2650 3450 2650 3550
Connection ~ 2650 3450
Wire Wire Line
	2650 4000 2650 4100
Connection ~ 2650 4000
Connection ~ 2950 3550
Wire Wire Line
	5700 4650 5700 4400
Connection ~ 5700 4400
Wire Wire Line
	5450 4650 5450 4100
Connection ~ 5450 4100
Wire Wire Line
	5700 5050 5700 4950
Wire Wire Line
	5450 5050 5700 5050
Wire Wire Line
	5450 5050 5450 4950
Wire Wire Line
	5550 5150 5550 5050
Connection ~ 5550 5050
Wire Wire Line
	4300 3900 4150 3900
Wire Wire Line
	4150 3900 4150 3550
Wire Wire Line
	4300 3450 4300 3800
$Comp
L 4.7uF C702
U 1 1 5A708309
P 3150 3700
F 0 "C702" H 3200 3899 45  0000 C CNN
F 1 "4.7uF" H 3200 3815 45  0000 C CNN
F 2 "kemet:0603" H 3180 3850 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2062994.pdf?_ga=1.180651367.1948984246.1460023966" H 3054 3709 60  0001 C CNN
F 4 "1572625" H 3454 4109 60  0001 C CNN "1st Source Part Number"
F 5 "C0603C475K8PACTU" H 3254 3909 60  0001 C CNN "Manufacturer Part Number"
F 6 "Farnell" H 3354 4009 60  0001 C CNN "1st Source"
F 7 "KEMET" H 3154 3809 60  0001 C CNN "Manufacturer"
	1    3150 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 3700 3050 3550
Connection ~ 3050 3550
Wire Wire Line
	3350 3700 3350 3550
Connection ~ 3350 3550
$Comp
L 4.7uF C703
U 1 1 5A7083E2
P 3150 3850
F 0 "C703" H 3200 4049 45  0000 C CNN
F 1 "4.7uF" H 3200 3965 45  0000 C CNN
F 2 "kemet:0603" H 3180 4000 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2062994.pdf?_ga=1.180651367.1948984246.1460023966" H 3054 3859 60  0001 C CNN
F 4 "1572625" H 3454 4259 60  0001 C CNN "1st Source Part Number"
F 5 "C0603C475K8PACTU" H 3254 4059 60  0001 C CNN "Manufacturer Part Number"
F 6 "Farnell" H 3354 4159 60  0001 C CNN "1st Source"
F 7 "KEMET" H 3154 3959 60  0001 C CNN "Manufacturer"
	1    3150 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 3850 3050 4100
Connection ~ 3050 4100
Wire Wire Line
	3350 3850 3350 4100
Connection ~ 3350 4100
$EndSCHEMATC
