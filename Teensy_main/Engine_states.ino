extern relay_t oxValve;         // Refrence things from another file
extern relay_t fuelValve;
extern relay_t purgeValve;
extern relay_t igniter;
extern relay_t redLight;
extern relay_t yellowLight;
extern relay_t greenLight;
extern relay_t buzzer;



void disabled() {           // Lock controls, all valves must be shut first, end state of safe states
  if (allBuffer.solenoids.sol1 != 0 || allBuffer.solenoids.sol2 != 0 || allBuffer.solenoids.sol3 != 0) {
    return;  
  }
  digitalWrite(redLight.pin, HIGH);
  digitalWrite(yellowLight.pin, HIGH);
  digitalWrite(greenLight.pin, LOW);
  allBuffer.light.LED_G = 1;
  allBuffer.light.LED_Y = 0;
  allBuffer.light.LED_R = 0;
  packetReadSafe();
}


void hot() {                // Close fuel and ox and open purge, 
  digitalWrite(fuelValve.pin, HIGH);
  digitalWrite(oxValve.pin, HIGH);
  digitalWrite(purgeValve.pin, LOW);
  digitalWrite(redLight.pin, LOW);
  allBuffer.solenoids.sol1 = 0;
  allBuffer.solenoids.sol2 = 0;
  allBuffer.solenoids.sol3 = 1;
  allBuffer.light.LED_R = 1;
  
  delay(2000);
  
}


void cold() {
  
}
