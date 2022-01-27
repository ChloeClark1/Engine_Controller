


void valveControl(char valve, char state) {
  //Alter state of valve when called
  //valve- 1-4
  //state- O = open, C = closed

  switch (valve) {
    case '1':
      if (state == 'O') {
        digitalWrite(oxValve, LOW);
        valveStatOxV1 = 1;
      }
      else {
        digitalWrite(oxValve, HIGH);
        valveStatOxV1  = 0;
      }
      break;
    case '2':
      if (state == 'O') {
        digitalWrite(fuelValve1, LOW);
        valveStatFV1 = 1;
      }
      else {
        digitalWrite(fuelValve1, HIGH);
        valveStatFV1 = 0;
      }
      break;

    case '4':
      if (state == 'O') {
        digitalWrite(purgeValve, LOW);
        valveStatPV = 1;
      }
      else {
        digitalWrite(purgeValve, HIGH);
        valveStatPV = 0;
      }
      break;
    default:
      break;
  }

  return;
}

void shutDownValves() {
  // Close all valves
  valveControl('1', 'C');
  valveControl('2', 'C');
  valveControl('4', 'C');
}

void ignition() {
  // Activate the Sparky boy
  // Send high signal to igniter pins to activate
  digitalWrite(igniter, LOW);

}
