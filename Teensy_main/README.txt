Preset numbers and pins

seq_num start:
Start on 1 as first command

control:
100 = oxValve, 101 = fuelValve 102 = purgeValve				 // Solenoids
200 = igniter1								 // Igniters
300 = red light, 301 = yellow light, 302 = green light, 303 = buzzer	 // Dummy tower
900 = mode change, 901 = safing change to 1				 // Safe modes

ports: 
8080 = seqNum
8081 = solenoids
8082 = igniters
8083 = dummy tower
8084 = All states + seqNum

states:
0 = off
1 = on

Output pins to relay:  
16 = oxValve
17 = fuelValve
18 = purgeValve
19 = igniter
20 = red light
21 = yellow light
22 = green light
23 = buzzer
