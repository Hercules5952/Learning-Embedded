#define LED_PIN 8
#define BUTTON_PIN 7
int lastbuttonstate;
int ledstate = LOW;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  lastbuttonstate = digitalRead(BUTTON_PIN);
}

void loop() {
  int buttonstate = digitalRead(BUTTON_PIN);
  if(buttonstate != lastbuttonstate)
  {
    lastbuttonstate = buttonstate;
    if(buttonstate == HIGH)
    {
      ledstate = !ledstate;
      digitalWrite(LED_PIN, ledstate);
    }
  }
}