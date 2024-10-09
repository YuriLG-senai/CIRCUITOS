void setup() {
  Serial.begin(9600);
}

void loop() {
  int xValue = analogRead(A0);
  int yValue = analogRead(A1);
  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print(" Y: ");
  Serial.println(yValue);
  delay(100);
}
