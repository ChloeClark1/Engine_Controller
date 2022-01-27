

// Initialization of variables

// pins

int killSwitch = 18;    // Set pin of kill switch

int oxValve = 9;        // Set pin of oxygen regulation valve                      Valve '1'
int fuelValve1 = 10;    // Set pin of fuel regulation valve 1, the first one       Valve '2'
int purgeValve = 12;    // Set pin of purge valve                                  Valve '4'

int valveStatOxV1 = 0;  // Set valve and pump states, 0 = closed, 1 = open
int valveStatFV1 = 0;
int valveStatPV = 0;

// Others
int startDelay = 3000;   // Delay of 3 seconds before firing
int burnTime = 7000;     // Burn for 7 seconds

String startCommand;     // Command that must be sent to start the fire sequence
String inputCommand;     // Command input by user for starting, must match startCommand to initiate start sequence


void setup() {
  // assign pins as input or output
  pinMode(killSwitch, INPUT);

  // Interrupts to declare
  attachInterrupt(digitalPinToInterrupt(killSwitch), shutDownValves, HIGH);
  Serial.begin(9600);

  // Initialize closed valves
  pinMode(oxValve, OUTPUT);
  digitalWrite(oxValve, LOW);
  pinMode(fuelValve1, OUTPUT);
  digitalWrite(fuelValve1, LOW);
  pinMode(purgeValve, OUTPUT);
  digitalWrite(purgeValve, LOW);
}


void loop() {
  Serial.begin(9600);
  // Wait for user to send start command
  //while (inputCommand != startCommand) {
  //  inputCommand = Serial.readString();
  //}
  // Begin fire sequence once while statement is broken (start command is input)

  shutDownValves();
  // Open solenoid 1 (Ox valve)
  valveControl('1', 'O');
  Serial.println(valveStatOxV1);
    
  // Open solenoid 2 (fuel valves)
  valveControl('2', 'O');

  delay(burnTime);
  
  // Close fuel and ox solenoids after 7 sec firing and stop pumps
  valveControl('1', 'C');
  valveControl('2', 'C');
  Serial.println(valveStatOxV1);

  delay(3000); // Arbitrary delay before opening purge

  // Open purge valve, is it necessary to repeat other valve commands? (like that in old code)
  valveControl('1', 'C');
  valveControl('2', 'C');
  valveControl('4', 'O');
  Serial.println(valveStatOxV1);

  delay(3000); // Arbitrary delay before closing purge again

  shutDownValves();
}
