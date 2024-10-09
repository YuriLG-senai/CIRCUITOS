void setup() {
  Serial.begin(9600);
}

void loop() {
  int xValue = analogRead(A0);
  int yValue = analogRead(A1);

  if (yValue < 341) {
    Serial.println("Para baixo");
  } else if (yValue > 682) {
    Serial.println("Para cima");
  } else {
    Serial.println("Centralizado");
  }

  if (xValue < 341) {
    Serial.println("Para esquerda");
  } else if (xValue > 682) {
    Serial.println("Para direita");
  } else {
    Serial.println("Centralizado");
  }

  delay(100);
}
