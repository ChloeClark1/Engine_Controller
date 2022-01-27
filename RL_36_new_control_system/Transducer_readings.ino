
// For readings of pressures and displaying them

void logPressures(int index, float OxVoltage, float FuelVoltage) {
  float OxPressure[index] = {OxVoltage};
  float FuelPressure[index] = {FuelVoltage};

  Serial.print(OxPressure[index]);
  Serial.print(FuelPressure[index]);
}
