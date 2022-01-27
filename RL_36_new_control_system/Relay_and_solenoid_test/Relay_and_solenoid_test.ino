int relay = A1; // Set pin of relay control

void setup() {
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);

}

void loop() {
  delay(3000);
  digitalWrite(relay, HIGH);
  delay(3000);
  digitalWrite(relay, LOW);
  delay(3000);
}
