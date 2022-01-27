
//Valve Pins
// As of 10/17/2020, these were arbitrarily set to 9,10,11,12
// oxValve1 is the pin controlling the oxidizer solenoid valve
// fuelValve1Pin is the First of the two Fuel Regulation Valve
// fuelValve2Pin is the Second of the two Fuel Regulation Valve
// purgeValvePin is the pin corresponding the purge valve

// Basic Outline
// Initialize variables and whatnot
// Wait for user input
// Firing procedure
// Wait until done firing
// Purge Procedure
// End


// Pins and whatnot
//1 = COM
int oxValve1 = 9; //2
int fuelValve1Pin = 10; //3
int fuelValve2Pin = 11; //4
int purgeValvePin = 12; //5
int igniterPin = 13;
//6 = GROUND
//

//kill switch Pin 
// As of 10/17/2020, this was arbitrarily set to pin 1

int killSwitch = 18;

//Pressure Transducer
//2020 Fall Prop using Honeywell MLH03KPSL01A
//Sensor Ranges from 0 to 3000 psi
//Voltage Ranges from 0.5 to 4.5 Volts


int oxPressPin = 2;
int fuelPressPin = 3;

// variables
int startdelay = 3000;
int burnTime = 7000;

String startCommand = "MosquitoStart";
String inCommand = "OOPS";

void setup() {
  // Killswitch
pinMode(killSwitch,INPUT);
pinMode(oxPressPin,INPUT);
pinMode(fuelPressPin,INPUT);
pinMode(killSwitch,INPUT);
//attachInterrupt(digitalPinToInterrupt(killSwitch),shutDownValves,HIGH);
//attachInterrupt(digitalPinToInterrupt(oxPressPin),shutDownValves,HIGH);
//attachInterrupt(digitalPinToInterrupt(fuelPressPin),shutDownValves,HIGH);
Serial.begin(9600);

  // Initialize Closed Valves

  pinMode(oxValve1, OUTPUT);
  digitalWrite(oxValve1, LOW);
  pinMode(fuelValve1Pin, OUTPUT);
  digitalWrite(fuelValve1Pin, LOW);
  pinMode(fuelValve2Pin, OUTPUT);
  digitalWrite(fuelValve2Pin, LOW);
  pinMode(purgeValvePin, OUTPUT);
  digitalWrite(purgeValvePin, LOW);

shutDownValves();

}

int valveStatOxV1 = 0;
int valveStatFV1 = 0;
int valveStatFV2 = 0;
int valveStatPV = 0;


void loop() {
//shutDownValves();
// Wait for user to send Mosquito Start to the controller
//while(inCommand != startCommand){
 // inCommand = Serial.readString();
//}
//Open Solenoid 1 (o2 valve)
valvecontrol('1','O');

//Open Solenoids 2 and 3 (Fuel Supply)
valvecontrol('2','O');
valvecontrol('3','O');


SENDIT();
// Wait for stuff to burn - 7 seconds
delay(burnTime);

// Close Solenoids 1 2 3 (Cut off Oxygen and Fuel)
valvecontrol('1','C');
valvecontrol('2','C');
valvecontrol('3','C');

delay(3000);
// Wait 3 Seconds - Arbitrary

// Open Solenoid 4 (Purge Valve)
valvecontrol('1','C');
valvecontrol('2','C');
valvecontrol('3','C');
valvecontrol('4','O');
// Wait 3 Seconds - Arbitrary
delay(3000);

valvecontrol('4','C');
// Close Solenoid 4 (Purge Valve)


shutDownValves();
while(1==1){
  
valvecontrol('1','O');
valvecontrol('2','O');
valvecontrol('3','O');
valvecontrol('4','O');
}
}
void SENDIT(){
  //Activate the Sparky boy
  digitalWrite(igniterPin,HIGH);
  delay(5);
  digitalWrite(igniterPin,LOW);
  
}
void valvecontrol(char valve, char stat){
  //Valve controller function borrowed from P18102 MainFunc()
  switch(valve){
    case '1':
    if (stat == 'O'){
      digitalWrite(oxValve1, LOW);
      valveStatOxV1 = 1;
    }
    else{
      digitalWrite(oxValve1, HIGH);
      valveStatOxV1  = 0;
    }
    break;
    case '2':
        if (stat == 'O'){
      digitalWrite(fuelValve1Pin, LOW);
      valveStatFV1 = 1;
    }
    else{
      digitalWrite(fuelValve1Pin, HIGH);
      valveStatFV1 = 0;
    }
    break;
    case '3':
        if (stat == 'O'){
      digitalWrite(fuelValve2Pin, LOW);
      valveStatFV2 = 1;
    }
    else{
      digitalWrite(fuelValve2Pin, HIGH);
      valveStatFV2 = 0;
    }
    break;
    case '4':
         if (stat == 'O'){
      digitalWrite(purgeValvePin, LOW);
      valveStatPV = 1;
    }
    else{
      digitalWrite(purgeValvePin, HIGH);
      valveStatPV= 0;
    }
    break;
    default:
    break;
  }
  
  return;
}

void shutDownValves(){
valvecontrol('1','C');
valvecontrol('2','C');
valvecontrol('3','C');
valvecontrol('4','C');
}
