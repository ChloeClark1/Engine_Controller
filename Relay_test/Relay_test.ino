typedef struct {
  uint16_t pin;
  uint16_t currentState;
  uint16_t controlNum;
} relay_t;


relay_t oxValve = {16, 0, 100};
relay_t fuelValve = {17, 0, 101};
relay_t purgeValve = {18, 0, 102};
relay_t igniter = {19, 0, 200};
relay_t redLight = {20, 0, 300};
relay_t yellowLight = {21, 0, 301};
relay_t greenLight = {22, 0, 302};
relay_t buzzer = {23, 0, 303};

void setup() {
  pinMode(oxValve.pin, OUTPUT);
  digitalWrite(oxValve.pin, HIGH);
  pinMode(fuelValve.pin, OUTPUT);
  digitalWrite(fuelValve.pin, HIGH);
  pinMode(purgeValve.pin, OUTPUT);
  digitalWrite(purgeValve.pin, HIGH);
  pinMode(igniter.pin, OUTPUT);
  digitalWrite(igniter.pin, HIGH);
  pinMode(redLight.pin, OUTPUT);
  digitalWrite(redLight.pin, HIGH);
  pinMode(yellowLight.pin, OUTPUT);
  digitalWrite(yellowLight.pin, HIGH);
  pinMode(greenLight.pin, OUTPUT);
  digitalWrite(greenLight.pin, HIGH);
  pinMode(buzzer.pin, OUTPUT);
  digitalWrite(buzzer.pin, HIGH);

}

void loop() {
  digitalWrite(redLight.pin, LOW);
  delay(5000);
  digitalWrite(yellowLight.pin, LOW);
  delay(5000);
  digitalWrite(greenLight.pin, LOW);
  delay(5000);
  digitalWrite(redLight.pin, HIGH);
  delay(5000);
  digitalWrite(yellowLight.pin, HIGH);
  delay(5000);
  digitalWrite(greenLight.pin, HIGH);
  delay(5000);

}
