extern relay_t oxValve;         // Refrence things from another file
extern relay_t fuelValve;
extern relay_t purgeValve;
extern relay_t igniter;
extern relay_t redLight;
extern relay_t yellowLight;
extern relay_t greenLight;
extern relay_t buzzer;

void engineSafe() {
  digitalWrite(oxValve.pin, HIGH);
  digitalWrite(fuelValve.pin, HIGH);
  digitalWrite(purgeValve.pin, LOW);
  digitalWrite(igniter.pin, HIGH);
  allStates.solenoids.sol1 = 0;
  allStates.solenoids.sol2 = 0;
  allStates.solenoids.sol3 = 1;
  allStates.igniters.igniter1 = 0;

  if(Ethernet.linkStatus() == LinkON) {
    return;
  }

  digitalWrite(buzzer.pin, LOW);
  allStates.light.buzz = 1;
  
  while(true) {
    if(Ethernet.linkStatus() == LinkON) {
      digitalWrite(buzzer.pin, HIGH);
      allStates.light.buzz = 0;
      delay(1000);
      digitalWrite(purgeValve.pin, HIGH);
      allStates.solenoids.sol3 = 0;
      return;
    }
    digitalWrite(redLight.pin, LOW);
    allStates.light.LED_R = 1;
    delay(100);
    digitalWrite(redLight.pin, HIGH);
    digitalWrite(yellowLight.pin, LOW);
    allStates.light.LED_R = 0;
    allStates.light.LED_Y = 1;
    delay(100);
    digitalWrite(yellowLight.pin, HIGH);
    digitalWrite(greenLight.pin, LOW);
    allStates.light.LED_Y = 0;
    allStates.light.LED_G = 1;
    delay(100);
    digitalWrite(greenLight.pin, HIGH);
    allStates.light.LED_G = 0;
  }
  
}
