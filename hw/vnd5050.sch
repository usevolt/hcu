EESchema Schematic File Version 4
LIBS:hcu-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 9 15
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
SENSE
$Comp
L usevolt:VND5050AJTR-E U301
U 1 1 59D8088A
P 4600 4000
AR Path="/5A8D7860/59D8088A" Ref="U301"  Part="1" 
AR Path="/5A8D8BD2/59D8088A" Ref="U401"  Part="1" 
AR Path="/5A8D900F/59D8088A" Ref="U501"  Part="1" 
AR Path="/5A8D95F3/59D8088A" Ref="U601"  Part="1" 
AR Path="/5A8D9C64/59D8088A" Ref="U701"  Part="1" 
AR Path="/5A8DA46E/59D8088A" Ref="U801"  Part="1" 
AR Path="/5A8DB2AD/59D8088A" Ref="U901"  Part="1" 
AR Path="/5A8DBBEF/59D8088A" Ref="U1001"  Part="1" 
AR Path="/5A8DEA06/59D8088A" Ref="U1101"  Part="1" 
AR Path="/5A8DF701/59D8088A" Ref="U1201"  Part="1" 
F 0 "U1201" H 4700 4447 60  0000 C CNN
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
L power:VDD #PWR0303
U 1 1 59D808C7
P 5250 3650
AR Path="/5A8D7860/59D808C7" Ref="#PWR0303"  Part="1" 
AR Path="/5A8D8BD2/59D808C7" Ref="#PWR0403"  Part="1" 
AR Path="/5A8D900F/59D808C7" Ref="#PWR0503"  Part="1" 
AR Path="/5A8D95F3/59D808C7" Ref="#PWR0603"  Part="1" 
AR Path="/5A8D9C64/59D808C7" Ref="#PWR0703"  Part="1" 
AR Path="/5A8DA46E/59D808C7" Ref="#PWR0803"  Part="1" 
AR Path="/5A8DB2AD/59D808C7" Ref="#PWR0903"  Part="1" 
AR Path="/5A8DBBEF/59D808C7" Ref="#PWR01003"  Part="1" 
AR Path="/5A8DEA06/59D808C7" Ref="#PWR01103"  Part="1" 
AR Path="/5A8DF701/59D808C7" Ref="#PWR01203"  Part="1" 
F 0 "#PWR01203" H 5250 3500 50  0001 C CNN
F 1 "VDD" H 5267 3823 50  0000 C CNN
F 2 "" H 5250 3650 50  0000 C CNN
F 3 "" H 5250 3650 50  0000 C CNN
	1    5250 3650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0301
U 1 1 59D86DC2
P 2950 4450
AR Path="/5A8D7860/59D86DC2" Ref="#PWR0301"  Part="1" 
AR Path="/5A8D8BD2/59D86DC2" Ref="#PWR0401"  Part="1" 
AR Path="/5A8D900F/59D86DC2" Ref="#PWR0501"  Part="1" 
AR Path="/5A8D95F3/59D86DC2" Ref="#PWR0601"  Part="1" 
AR Path="/5A8D9C64/59D86DC2" Ref="#PWR0701"  Part="1" 
AR Path="/5A8DA46E/59D86DC2" Ref="#PWR0801"  Part="1" 
AR Path="/5A8DB2AD/59D86DC2" Ref="#PWR0901"  Part="1" 
AR Path="/5A8DBBEF/59D86DC2" Ref="#PWR01001"  Part="1" 
AR Path="/5A8DEA06/59D86DC2" Ref="#PWR01101"  Part="1" 
AR Path="/5A8DF701/59D86DC2" Ref="#PWR01201"  Part="1" 
F 0 "#PWR01201" H 2950 4200 50  0001 C CNN
F 1 "GND" H 2955 4277 50  0000 C CNN
F 2 "" H 2950 4450 50  0000 C CNN
F 3 "" H 2950 4450 50  0000 C CNN
	1    2950 4450
	1    0    0    -1  
$EndComp
$Comp
L yageo:1K R?
U 1 1 5A05950C
P 2750 3550
AR Path="/5A015FC0/5A05950C" Ref="R?"  Part="1" 
AR Path="/5A02A41F/5A05950C" Ref="R?"  Part="1" 
AR Path="/5A12B58E/5A05950C" Ref="R?"  Part="1" 
AR Path="/5A7B157A/5A05950C" Ref="R?"  Part="1" 
AR Path="/5A7B341B/5A05950C" Ref="R?"  Part="1" 
AR Path="/5A7B2C1B/5A05950C" Ref="R?"  Part="1" 
AR Path="/5A7B3FAD/5A05950C" Ref="R?"  Part="1" 
AR Path="/5A7B4C13/5A05950C" Ref="R?"  Part="1" 
AR Path="/5A7B577E/5A05950C" Ref="R?"  Part="1" 
AR Path="/5A7B753D/5A05950C" Ref="R?"  Part="1" 
AR Path="/5A8D7860/5A05950C" Ref="R301"  Part="1" 
AR Path="/5A8D8BD2/5A05950C" Ref="R401"  Part="1" 
AR Path="/5A8D900F/5A05950C" Ref="R501"  Part="1" 
AR Path="/5A8D95F3/5A05950C" Ref="R601"  Part="1" 
AR Path="/5A8D9C64/5A05950C" Ref="R701"  Part="1" 
AR Path="/5A8DA46E/5A05950C" Ref="R801"  Part="1" 
AR Path="/5A8DB2AD/5A05950C" Ref="R901"  Part="1" 
AR Path="/5A8DBBEF/5A05950C" Ref="R1001"  Part="1" 
AR Path="/5A8DEA06/5A05950C" Ref="R1101"  Part="1" 
AR Path="/5A8DF701/5A05950C" Ref="R1201"  Part="1" 
F 0 "R1201" H 2800 3734 45  0000 C CNN
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
L yageo:1K R?
U 1 1 5A059568
P 2750 4100
AR Path="/5A015FC0/5A059568" Ref="R?"  Part="1" 
AR Path="/5A02A41F/5A059568" Ref="R?"  Part="1" 
AR Path="/5A12B58E/5A059568" Ref="R?"  Part="1" 
AR Path="/5A7B157A/5A059568" Ref="R?"  Part="1" 
AR Path="/5A7B341B/5A059568" Ref="R?"  Part="1" 
AR Path="/5A7B2C1B/5A059568" Ref="R?"  Part="1" 
AR Path="/5A7B3FAD/5A059568" Ref="R?"  Part="1" 
AR Path="/5A7B4C13/5A059568" Ref="R?"  Part="1" 
AR Path="/5A7B577E/5A059568" Ref="R?"  Part="1" 
AR Path="/5A7B753D/5A059568" Ref="R?"  Part="1" 
AR Path="/5A8D7860/5A059568" Ref="R302"  Part="1" 
AR Path="/5A8D8BD2/5A059568" Ref="R402"  Part="1" 
AR Path="/5A8D900F/5A059568" Ref="R502"  Part="1" 
AR Path="/5A8D95F3/5A059568" Ref="R602"  Part="1" 
AR Path="/5A8D9C64/5A059568" Ref="R702"  Part="1" 
AR Path="/5A8DA46E/5A059568" Ref="R802"  Part="1" 
AR Path="/5A8DB2AD/5A059568" Ref="R902"  Part="1" 
AR Path="/5A8DBBEF/5A059568" Ref="R1002"  Part="1" 
AR Path="/5A8DEA06/5A059568" Ref="R1102"  Part="1" 
AR Path="/5A8DF701/5A059568" Ref="R1202"  Part="1" 
F 0 "R1202" H 2800 4284 45  0000 C CNN
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
L usevolt:DIODE_RS07J-GS18 D?
U 1 1 5A2AAF9E
P 5450 4750
AR Path="/5A7B157A/5A2AAF9E" Ref="D?"  Part="1" 
AR Path="/5A7B341B/5A2AAF9E" Ref="D?"  Part="1" 
AR Path="/5A7B2C1B/5A2AAF9E" Ref="D?"  Part="1" 
AR Path="/5A7B3FAD/5A2AAF9E" Ref="D?"  Part="1" 
AR Path="/5A7B4C13/5A2AAF9E" Ref="D?"  Part="1" 
AR Path="/5A7B577E/5A2AAF9E" Ref="D?"  Part="1" 
AR Path="/5A7B753D/5A2AAF9E" Ref="D?"  Part="1" 
AR Path="/5A8D7860/5A2AAF9E" Ref="D302"  Part="1" 
AR Path="/5A8D8BD2/5A2AAF9E" Ref="D402"  Part="1" 
AR Path="/5A8D900F/5A2AAF9E" Ref="D502"  Part="1" 
AR Path="/5A8D95F3/5A2AAF9E" Ref="D602"  Part="1" 
AR Path="/5A8D9C64/5A2AAF9E" Ref="D702"  Part="1" 
AR Path="/5A8DA46E/5A2AAF9E" Ref="D802"  Part="1" 
AR Path="/5A8DB2AD/5A2AAF9E" Ref="D902"  Part="1" 
AR Path="/5A8DBBEF/5A2AAF9E" Ref="D1002"  Part="1" 
AR Path="/5A8DEA06/5A2AAF9E" Ref="D1102"  Part="1" 
AR Path="/5A8DF701/5A2AAF9E" Ref="D1202"  Part="1" 
F 0 "D1202" V 5400 4652 45  0000 R CNN
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
L usevolt:DIODE_RS07J-GS18 D?
U 1 1 5A2AB087
P 5700 4750
AR Path="/5A7B157A/5A2AB087" Ref="D?"  Part="1" 
AR Path="/5A7B341B/5A2AB087" Ref="D?"  Part="1" 
AR Path="/5A7B2C1B/5A2AB087" Ref="D?"  Part="1" 
AR Path="/5A7B3FAD/5A2AB087" Ref="D?"  Part="1" 
AR Path="/5A7B4C13/5A2AB087" Ref="D?"  Part="1" 
AR Path="/5A7B577E/5A2AB087" Ref="D?"  Part="1" 
AR Path="/5A7B753D/5A2AB087" Ref="D?"  Part="1" 
AR Path="/5A8D7860/5A2AB087" Ref="D303"  Part="1" 
AR Path="/5A8D8BD2/5A2AB087" Ref="D403"  Part="1" 
AR Path="/5A8D900F/5A2AB087" Ref="D503"  Part="1" 
AR Path="/5A8D95F3/5A2AB087" Ref="D603"  Part="1" 
AR Path="/5A8D9C64/5A2AB087" Ref="D703"  Part="1" 
AR Path="/5A8DA46E/5A2AB087" Ref="D803"  Part="1" 
AR Path="/5A8DB2AD/5A2AB087" Ref="D903"  Part="1" 
AR Path="/5A8DBBEF/5A2AB087" Ref="D1003"  Part="1" 
AR Path="/5A8DEA06/5A2AB087" Ref="D1103"  Part="1" 
AR Path="/5A8DF701/5A2AB087" Ref="D1203"  Part="1" 
F 0 "D1203" V 5650 4652 45  0000 R CNN
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
L power:GND #PWR0304
U 1 1 5A2AB10F
P 5550 5150
AR Path="/5A8D7860/5A2AB10F" Ref="#PWR0304"  Part="1" 
AR Path="/5A8D8BD2/5A2AB10F" Ref="#PWR0404"  Part="1" 
AR Path="/5A8D900F/5A2AB10F" Ref="#PWR0504"  Part="1" 
AR Path="/5A8D95F3/5A2AB10F" Ref="#PWR0604"  Part="1" 
AR Path="/5A8D9C64/5A2AB10F" Ref="#PWR0704"  Part="1" 
AR Path="/5A8DA46E/5A2AB10F" Ref="#PWR0804"  Part="1" 
AR Path="/5A8DB2AD/5A2AB10F" Ref="#PWR0904"  Part="1" 
AR Path="/5A8DBBEF/5A2AB10F" Ref="#PWR01004"  Part="1" 
AR Path="/5A8DEA06/5A2AB10F" Ref="#PWR01104"  Part="1" 
AR Path="/5A8DF701/5A2AB10F" Ref="#PWR01204"  Part="1" 
F 0 "#PWR01204" H 5550 4900 50  0001 C CNN
F 1 "GND" H 5555 4977 50  0000 C CNN
F 2 "" H 5550 5150 50  0000 C CNN
F 3 "" H 5550 5150 50  0000 C CNN
	1    5550 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 3650 5250 3800
Wire Wire Line
	5250 3800 5100 3800
Wire Wire Line
	5250 3900 5100 3900
Connection ~ 5250 3800
Wire Wire Line
	5250 4000 5100 4000
Connection ~ 5250 3900
Wire Wire Line
	5100 4100 5250 4100
Wire Wire Line
	5100 4200 5250 4200
Wire Wire Line
	5250 4200 5250 4100
Connection ~ 5250 4100
Wire Wire Line
	5100 4400 5250 4400
Wire Wire Line
	5100 4300 5250 4300
Wire Wire Line
	5250 4300 5250 4400
Connection ~ 5250 4400
Wire Wire Line
	2550 3450 2650 3450
Wire Wire Line
	2550 4000 2650 4000
Wire Wire Line
	2950 3550 2950 4100
Wire Wire Line
	2950 4300 3750 4300
Wire Wire Line
	3050 3550 2950 3550
Connection ~ 2950 4300
Connection ~ 2950 4100
Wire Wire Line
	3350 3550 3500 3550
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
	5450 5050 5550 5050
Wire Wire Line
	5450 5050 5450 4950
Wire Wire Line
	5550 5150 5550 5050
Connection ~ 5550 5050
Wire Wire Line
	4300 3900 4150 3900
Wire Wire Line
	4150 3550 4150 3900
Wire Wire Line
	4300 3450 4300 3800
$Comp
L kemet:4.7uF C?
U 1 1 5A708309
P 3150 3850
AR Path="/5A7B157A/5A708309" Ref="C?"  Part="1" 
AR Path="/5A7B341B/5A708309" Ref="C?"  Part="1" 
AR Path="/5A7B2C1B/5A708309" Ref="C?"  Part="1" 
AR Path="/5A7B3FAD/5A708309" Ref="C?"  Part="1" 
AR Path="/5A7B4C13/5A708309" Ref="C?"  Part="1" 
AR Path="/5A7B577E/5A708309" Ref="C?"  Part="1" 
AR Path="/5A7B753D/5A708309" Ref="C?"  Part="1" 
AR Path="/5A8D7860/5A708309" Ref="C301"  Part="1" 
AR Path="/5A8D8BD2/5A708309" Ref="C401"  Part="1" 
AR Path="/5A8D900F/5A708309" Ref="C501"  Part="1" 
AR Path="/5A8D95F3/5A708309" Ref="C601"  Part="1" 
AR Path="/5A8D9C64/5A708309" Ref="C701"  Part="1" 
AR Path="/5A8DA46E/5A708309" Ref="C801"  Part="1" 
AR Path="/5A8DB2AD/5A708309" Ref="C901"  Part="1" 
AR Path="/5A8DBBEF/5A708309" Ref="C1001"  Part="1" 
AR Path="/5A8DEA06/5A708309" Ref="C1101"  Part="1" 
AR Path="/5A8DF701/5A708309" Ref="C1201"  Part="1" 
F 0 "C1201" H 3200 4049 45  0000 C CNN
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
	3050 3850 3050 3550
Wire Wire Line
	3350 3850 3350 3550
Wire Wire Line
	4150 4100 4300 4100
Connection ~ 4150 3900
Wire Wire Line
	5250 3800 5250 3900
Wire Wire Line
	5250 3900 5250 4000
Wire Wire Line
	5250 4100 5450 4100
Wire Wire Line
	5250 4400 5700 4400
Wire Wire Line
	2950 4300 2950 4450
Wire Wire Line
	2950 4100 2950 4300
Wire Wire Line
	3500 3550 3750 3550
Wire Wire Line
	2650 3450 4300 3450
Wire Wire Line
	2650 4000 4300 4000
Wire Wire Line
	5700 4400 5800 4400
Wire Wire Line
	5450 4100 5800 4100
Wire Wire Line
	5550 5050 5700 5050
Wire Wire Line
	4150 3900 4150 4100
Wire Wire Line
	3500 3350 3500 3550
$Comp
L yageo:1K R203
U 1 1 5B6F848F
P 3150 3550
AR Path="/5A8D7860/5B6F848F" Ref="R203"  Part="1" 
AR Path="/5A8D8BD2/5B6F848F" Ref="R303"  Part="1" 
AR Path="/5A8D900F/5B6F848F" Ref="R403"  Part="1" 
AR Path="/5A8D95F3/5B6F848F" Ref="R503"  Part="1" 
AR Path="/5A8D9C64/5B6F848F" Ref="R603"  Part="1" 
AR Path="/5A8DA46E/5B6F848F" Ref="R703"  Part="1" 
AR Path="/5A8DB2AD/5B6F848F" Ref="R803"  Part="1" 
AR Path="/5A8DBBEF/5B6F848F" Ref="R903"  Part="1" 
AR Path="/5A8DEA06/5B6F848F" Ref="R1003"  Part="1" 
AR Path="/5A8DF701/5B6F848F" Ref="R1103"  Part="1" 
F 0 "R1103" H 3200 3734 45  0000 C CNN
F 1 "1K" H 3200 3650 45  0000 C CNN
F 2 "yageo:0603" H 3180 3700 20  0001 C CNN
F 3 "" H 3119 3589 60  0001 C CNN
F 4 "" H 3519 3989 60  0001 C CNN "1st Source Part Number"
F 5 "Digikey" H 3419 3889 60  0001 C CNN "1st Source"
F 6 "RC0603FR-071KL" H 3319 3789 60  0001 C CNN "Manufacturer Part Number"
F 7 "YAGEO" H 3219 3689 60  0001 C CNN "Manufacturer"
	1    3150 3550
	1    0    0    -1  
$EndComp
Connection ~ 3350 3550
Connection ~ 3050 3550
$Comp
L usevolt:ZENER_MM3Z3V6T1G D901
U 1 1 5B701DAD
P 3750 3600
AR Path="/5A8DBBEF/5B701DAD" Ref="D901"  Part="1" 
AR Path="/5A8D7860/5B701DAD" Ref="D201"  Part="1" 
AR Path="/5A8D8BD2/5B701DAD" Ref="D301"  Part="1" 
AR Path="/5A8D900F/5B701DAD" Ref="D401"  Part="1" 
AR Path="/5A8D95F3/5B701DAD" Ref="D501"  Part="1" 
AR Path="/5A8D9C64/5B701DAD" Ref="D601"  Part="1" 
AR Path="/5A8DA46E/5B701DAD" Ref="D701"  Part="1" 
AR Path="/5A8DB2AD/5B701DAD" Ref="D801"  Part="1" 
AR Path="/5A8DEA06/5B701DAD" Ref="D1001"  Part="1" 
AR Path="/5A8DF701/5B701DAD" Ref="D1101"  Part="1" 
F 0 "D1101" V 3675 3522 45  0000 R CNN
F 1 "ZENER_MM3Z3V6T1G" H 4025 3975 45  0001 L BNN
F 2 "usevolt:SOD-323" H 3725 3975 20  0001 C CNN
F 3 "http://www.mouser.com/ds/2/308/MM3Z2V4T1-D-269162.pdf" H 4100 4175 60  0001 C CNN
F 4 "Mouser" H 4070 3920 60  0001 C CNN "1st Source"
F 5 "MM3Z3V6T1G" H 3970 3820 60  0001 C CNN "Manufacturer Part Number"
F 6 "863-MM3Z3V6T1G" H 4170 4020 60  0001 C CNN "1st Source Part Number"
F 7 "ON Semiconductor" H 4025 4075 60  0001 C CNN "Manufacturer"
	1    3750 3600
	0    -1   -1   0   
$EndComp
Connection ~ 3750 3550
Wire Wire Line
	3750 3550 4150 3550
Wire Wire Line
	3750 3800 3750 4300
Connection ~ 3750 4300
Wire Wire Line
	3750 4300 4300 4300
$EndSCHEMATC
