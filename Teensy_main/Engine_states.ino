extern relay_t oxValve;         // Refrence things from another file
extern relay_t fuelValve;
extern relay_t purgeValve;
extern relay_t igniter;
extern relay_t redLight;
extern relay_t yellowLight;
extern relay_t greenLight;
extern relay_t buzzer;
extern stateBuffer allStates;


void disabled() {           // Lock controls, all valves must be shut first, end state of safe states
  if (allStates.solenoids.sol1 != 0 || allStates.solenoids.sol2 != 0 || allStates.solenoids.sol3 != 0) {
    return;
  }
  digitalWrite(redLight.pin, HIGH);
  digitalWrite(yellowLight.pin, HIGH);
  digitalWrite(greenLight.pin, LOW);
  allStates.light.LED_G = 1;
  allStates.light.LED_Y = 0;
  allStates.light.LED_R = 0;
  packetReadSafe();
}


void hotFail() {                // Close fuel and ox and open purge,
  digitalWrite(fuelValve.pin, HIGH);
  digitalWrite(oxValve.pin, HIGH);
  digitalWrite(purgeValve.pin, LOW);
  digitalWrite(redLight.pin, LOW);
  allStates.solenoids.sol1 = 0;
  allStates.solenoids.sol2 = 0;
  allStates.solenoids.sol3 = 1;
  allStates.light.LED_R = 1;

  delay(2000);

  digitalWrite(purgeValve.pin, HIGH);
  allStates.solenoids.sol3 = 0;
  disabled();
  }


void coldFail() {       // Close everything, go to disabled
  digitalWrite(fuelValve.pin, HIGH);
  digitalWrite(oxValve.pin, HIGH);
  digitalWrite(purgeValve.pin, HIGH);
  digitalWrite(yellowLight.pin, LOW);
  allStates.solenoids.sol1 = 0;
  allStates.solenoids.sol2 = 0;
  allStates.solenoids.sol3 = 0;
  allStates.light.LED_Y = 1;
  disabled();
}
