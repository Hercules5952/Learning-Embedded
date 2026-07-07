#include <LiquidCrystal.h> // the library for including the lcd syntaxes 

const int trig = 13;  
const int echo = 9;  
#include <Servo.h> // the library for including the servo syntaxes 

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); 

// lcd(rs, en, d4, d5, d6, d7)
// rs - register select, to compare between the incoming text or the command
// en - enable pin
// d4, d5... - digital pins

long totaltime;
int distance, angle, x, y, jStick, i;
unsigned long t0, t1, response;

enum gamestate // the enumeration used to check the current state of the game for clarity
{
  waiting_for_player,
  waiting_for_input,
  check_result,
  waiting_for_leave
};

gamestate state = waiting_for_player;

Servo myservo;

void setup()
{
  myservo.attach(8);

  pinMode(trig, OUTPUT); // powering the trigger pin which sends the ultrasonic pulses 
  pinMode(echo, INPUT);  // powers the echo pin which is the output pin


  Serial.begin(9600);
  randomSeed(analogRead(A2)); // to generate a random seed used for the pattern of the servo motor

  lcd.begin(16,2);
  lcd.clear();
}

bool check()
{
  jStick = -1;

  // LEFT
  if (y >= 800)
  {
    jStick = 0;
  }

  // RIGHT
  else if (y <= 200)
  {
    jStick = 180;
  }

  // DOWN
  else if (x >= 800)
  {
    jStick = 90;
  }

  Serial.print("Comparing ");
  Serial.print(angle);
  Serial.print(" with ");
  Serial.println(jStick);

  return (angle == jStick);
}

void loop()
{
  // -------- Ultrasonic --------
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(trig, LOW);

  totaltime = pulseIn(echo, HIGH); // measures the length of the pulse used for calculating time 
  distance = totaltime * 0.034 / 2; // speed of sound is roughly 340 m/s
  // -------- WAITING FOR PLAYER --------
  if (state == waiting_for_player)
  {
    lcd.setCursor(3,0);
    lcd.print("waiting for");

    lcd.setCursor(5,1);
    lcd.print("player");

    if (distance <= 30)
    {      
      int arr[3] = {0, 90, 180};
      int n = random(0,3); // the operation that is used to make the servo rotate in a random direction 
      angle = arr[n];
      
      Serial.print("Servo Angle: ");
      i = 5;
      
      while(i > 0)
      {
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("Be ready in");

        lcd.setCursor(8,1);
        lcd.print(i);

        delay(1000);     // Wait 1 second

        i--;
      }

      myservo.write(angle); // servo performs the operation 

      Serial.println(angle);

      t0 = millis();

      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("waiting for");
      lcd.setCursor(5,1);
      lcd.print("input");

      state = waiting_for_input;
    }
  }

  // -------- WAITING FOR INPUT --------

  if (state == waiting_for_input)
  {
    x = analogRead(A0);
    y = analogRead(A1);

    // Wait until joystick leaves center
    if (!(x >= 480 && x <= 540 && y >= 500 && y <= 550))
    {
      state = check_result;
      t1 = millis();
    }

    delay(100);
  }

  // -------- CHECK RESULT --------
  if (state == check_result)
  {
    bool player = check();

    Serial.print("Player: ");
    Serial.println(player);

    if (player)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Correct");
      lcd.setCursor(9, 0);
      lcd.print("(^__^)");
      response = t1 - t0;
      lcd.setCursor(0, 1);
      lcd.print("Reaction= ");
      lcd.setCursor(10,1);
      lcd.print(response); 
      lcd.setCursor(14, 1);
      lcd.print("ms");
      delay(4000);
      // Stay here until player leaves
      state = waiting_for_leave;
    }
    else
    {
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print("wrong");
      lcd.setCursor(5,1);
      lcd.print("(X_X)");
      delay(1000);
      state = waiting_for_leave;
    }
  }

  // -------- WAIT FOR PLAYER TO LEAVE --------
  if (state == waiting_for_leave)
  {
    if (distance > 30)
    {
      Serial.println("Player Left");
      lcd.clear();
      state = waiting_for_player;
    }
  }
}