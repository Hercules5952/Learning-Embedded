#define LED1 6 //  LED A
#define LED2 7 //  LED B
#define LED3 8 //  LED C
#define LED4 9 //  LED D

#define buzzer 10 // for the buzzer to work

#define switch_A 2 // switch A
#define switch_B 3 // switch B 
#define switch_C 4 // switch C
#define switch_D 5 // switch D

int lastbuttonstate1; // the button state for A
int lastbuttonstate2; // the button state for B 
int lastbuttonstate3; // the button state for C
int lastbuttonstate4; // the button state for D

int del = 350;
int sequence[100];          // the sequential array for comparision
int seqlength = 1;          // length of the sequence array
bool sequenceshown = false; // to prevent infinite loop
int player_step = 0;        // global so it persists across calls

int arr[4];        // array for LEDs 1 2 3 and 4 
int switch_op[4]; // array for switches A and B 

bool wrongpress = false; // boolean expression for the wrong case 

void setup() {
  // declaring all the pins requiered for the operation 
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  pinMode(switch_A, INPUT_PULLUP);
  pinMode(switch_B, INPUT_PULLUP);
  pinMode(switch_C, INPUT_PULLUP);
  pinMode(switch_D, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);

  // input pullup is used as an alternative to the pullup resistors

  sequence[0] = random(0, 4); // taking sequence [0] = 1 as an example. Which means LED 2 is stored, as arr[1] is indexed as LED2
  arr[0] = LED1;
  arr[1] = LED2;  // LED arrays
  arr[2] = LED3;
  arr[3] = LED4;

  switch_op[0] = switch_A;
  switch_op[1] = switch_B; //swithc arrays 
  switch_op[2] = switch_C;
  switch_op[3] = switch_D;

  lastbuttonstate1 = digitalRead(switch_A); // used to read 
  lastbuttonstate2 = digitalRead(switch_B); // the last states of the switches
  lastbuttonstate3 = digitalRead(switch_C);
  lastbuttonstate4 = digitalRead(switch_D);
}

void loop()
{
  if (!sequenceshown) // if true
  {
    for (int i = 0; i < seqlength; i++)
    {      
      digitalWrite(arr[sequence[i]], HIGH); // set random LED as ON 
      delay(del);
      digitalWrite(arr[sequence[i]], LOW); // OFF
      delay(del);    
    }
    sequenceshown = true; // update to true 
  }

  bool player = switch_correct(); // check if the player is correct 

  if (player) // if correct do the below part
  { 
    delay(500); // after a delay of 500 ms
    sequence[seqlength] = random(0, 4); // start with the first new entry as a random
    seqlength++; // change seq length (it becomes to 2 here)
    sequenceshown = false; // re run the void

    if(del > 100)
    {
    del = del - 20;
    }
  }
  else if (wrongpress) // if not true 
{
  for (int i = 0; i < 4; i++)   // blink both LEDs 4 times
  {
    digitalWrite(buzzer,HIGH);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    delay(200);
  }
  delay(500); // pause before the new sequence starts replaying

  wrongpress = false; // reset the counter
  del = 350;

}
}

bool switch_correct() //operation for checking if the player was right 
{
  int buttonstate1 = digitalRead(switch_A); /// POINT A
  if (buttonstate1 != lastbuttonstate1)
  {
    lastbuttonstate1 = buttonstate1;
    if (buttonstate1 == LOW)
    {
      delay(50);
      
      digitalWrite(buzzer, HIGH);
      digitalWrite(LED1, HIGH);
      delay(350);
      digitalWrite(buzzer, LOW);
      digitalWrite(LED1, LOW);               /// POINT B, point a to b was the basic switch operation

      // to compare the input of the switch and the led sequence, we use the values inside the sequence array,
      // lets say sequence[0] = 1, which means LED 2 is fed
      // to get it right we need to check if seq[0] = 1 again but here 1 would be switch B

      if (sequence[player_step] != 0) // player_state is set to 0, meaning equal to 1, ie switch B is pressed, req to return false
      {
        player_step = 0; // reset the steps
        seqlength = 1;   // set the seq length back to 1
        sequence[0] = random(0, 4);  // resetting everything 
        sequenceshown = false;// ..
        wrongpress = true; // for triggering the lEds
        return false;
      }
      player_step++; // run if the above part isnt true

      // assuming in the first step that sequence[0] = 0;
      // seq length = 1, and the player_step is incremented to 1, so the the next part is run

      if (player_step == seqlength) 
      {
        player_step = 0; // reset it back and return true 
        return true;
      }
    }
  }

  int buttonstate2 = digitalRead(switch_B); // same thing is implemented here
  if (buttonstate2 != lastbuttonstate2)
  {
    delay(50);
    lastbuttonstate2 = buttonstate2;
    if (buttonstate2 == LOW)
    {
      digitalWrite(buzzer, HIGH);
      digitalWrite(LED2, HIGH);
      delay(350);
      digitalWrite(buzzer, LOW);
      digitalWrite(LED2, LOW);

      if (sequence[player_step] != 1)
      {
        player_step = 0;
        seqlength = 1;
        sequence[0] = random(0, 4);
        sequenceshown = false;
        wrongpress = true;
        return false;
      }
      player_step++;
      if (seqlength == player_step)
      {
        player_step = 0;
        return true;
      }
    }
  }

  int buttonstate3 = digitalRead(switch_C); // same thing is implemented here
  if (buttonstate3 != lastbuttonstate3)
  {
    delay(50);
    lastbuttonstate3 = buttonstate3;
    if (buttonstate3 == LOW)
    {
      digitalWrite(buzzer, HIGH);
      digitalWrite(LED3, HIGH);
      delay(350);
      digitalWrite(buzzer, LOW);
      digitalWrite(LED3, LOW); 

      if (sequence[player_step] != 2)
      {
        player_step = 0;
        seqlength = 1;
        sequence[0] = random(0, 4);
        sequenceshown = false;
        wrongpress = true;
        return false;
      }
      player_step++;
      if (seqlength == player_step)
      {
        player_step = 0;
        return true;
      }
    }
  }

  int buttonstate4 = digitalRead(switch_D); // same thing is implemented here
  if (buttonstate4 != lastbuttonstate4)
  {
    delay(50);
    lastbuttonstate4 = buttonstate4;
    if (buttonstate4 == LOW)
    {
      digitalWrite(buzzer, HIGH);
      digitalWrite(LED4, HIGH);
      delay(350);
      digitalWrite(buzzer, LOW);
      digitalWrite(LED4, LOW); 

      if (sequence[player_step] != 3)
      {
        player_step = 0;
        seqlength = 1;
        sequence[0] = random(0, 4);
        sequenceshown = false;
        wrongpress = true;
        return false;
      }
      player_step++;
      if (seqlength == player_step)
      {
        player_step = 0;
        return true;
      }
    }
  }

  return false; // and we return false if none of the above cases are happening
}