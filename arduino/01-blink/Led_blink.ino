void setup() {
  pinMode(12, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop()
{
  digitalWrite(12, HIGH);
  delay(350);
  digitalWrite(12, LOW);
  delay(350);

  
  digitalWrite(8, HIGH);
  delay(350);
  digitalWrite(8, LOW);
  delay(350);
}