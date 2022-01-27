Preset numbers and pins

seq_num start:
Start on 1 as first command

control:
100 = oxValve, 101 = fuelValve 102 = purgeValve				 // Solenoids
200 = igniter1								 // Igniters
300 = red light, 301 = yellow light, 302 = green light, 303 = buzzer	 // Dummy tower

ports: (are we sending to different GS ports or recieving on different ports?)
8080 = solenoids
8081 = igniters
8082 = dummy tower

states:
0 = off
1 = on

Output pins to relay:      // Also corresponds to index in replyBuffer array
0 = oxValve
1 = fuelValve
2 = purgeValve
3 = igniter
4 = red light
5 = yellow light
6 = green light
7 = buzzer
