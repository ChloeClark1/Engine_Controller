
// Initialization of variables
bool runOnce = true;

// pins
int igniter = 5;       // Set pin of igniter
int killSwitch = 18;    // Set pin of kill switch
int oxPressure = 2;     // Set pin of Oxygen pressure
int fuelPressure = 3;   // Set pin of fuel pressure

int oxValve = 9;        // Set pin of oxygen regulation valve                      Valve '1'
int fuelValve1 = 10;    // Set pin of fuel regulation valve 1, the first one       Valve '2'
int purgeValve = 12;    // Set pin of purge valve                                  Valve '4'

int valveStatOxV1 = 0;  // Set valve and pump states, 0 = closed, 1 = open
int valveStatFV1 = 0;
int valveStatFV2 = 0;
int valveStatPV = 0;



// Others
int startDelay = 3000;   // Delay of 3 seconds before firing
int burnTime = 7000;     // Burn for 7 seconds

String startCommand = "MES";     // Command that must be sent to start the fire sequence
String inputCommand;     // Command input by user for starting, must match startCommand to initiate start sequence


void setup() {
  // assign pins as input or output
  pinMode(killSwitch, INPUT_PULLUP);
  pinMode(oxPressure, INPUT_PULLUP);
  pinMode(fuelPressure, INPUT_PULLUP);

  // Interrupts to declare
  attachInterrupt(digitalPinToInterrupt(killSwitch), shutDownValves, LOW);
  attachInterrupt(digitalPinToInterrupt(oxPressure), shutDownValves, LOW);
  
  attachInterrupt(digitalPinToInterrupt(fuelPressure), shutDownValves, LOW);
  Serial.begin(9600);

  // Initialize closed valves
  pinMode(oxValve, OUTPUT);
  digitalWrite(oxValve, HIGH);
  pinMode(fuelValve1, OUTPUT);
  digitalWrite(fuelValve1, HIGH);
  pinMode(purgeValve, OUTPUT);
  digitalWrite(purgeValve, HIGH);
  pinMode(igniter, OUTPUT);
  digitalWrite(igniter, HIGH);
}

void loop() {
  
  shutDownValves();
  // Wait for user to send start command
  //while (inputCommand != startCommand) {
  //  inputCommand = Serial.readString();
  //}
  // Begin fire sequence once while statement is broken (start command is input)
  

  // Open solenoid 1 (Ox valve)

  valveControl('1', 'O');
  
  delay(2000);
  
  ignition();
  
  delay(2000);
  // Open solenoid 2 (fuel valve)
  valveControl('2', 'O');

  delay(burnTime);
  
  // Close fuel and ox solenoids after 7 sec firing and stop pumps
  digitalWrite(igniter, HIGH);
  valveControl('1', 'C');
  valveControl('2', 'C');
  valveControl('4', 'O');

  delay(10000); // Arbitrary delay before closing purge again

  shutDownValves();
  while (runOnce == true) {
    
  }
}
