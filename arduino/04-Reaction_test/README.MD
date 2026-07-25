# Reflex Roulette



##### A simple game that uses the joystick's drift as the input and the servo motor's output to calculate reaction time. An ultrasonic sensor is also used to detect the presence of the player; in its absence, the game waits for the player.



### Overview:

##### 

The game uses a random seed generator to make the servo point in a random direction every iteration. The input from the joystick is then compared with the direction of the servo, and the reaction time is shown on the LCD.

Hardware Components:
---

##### 

##### Arduino (Uno)

##### HC-SR04 ultrasonic sensor

##### SG90 servo motor

##### 16x2 LCD display

##### Analog joystick module

##### Potentiometer (for LCD contrast)

##### Breadboard and jumper wires

##### 

### Code Explanation:

### 

* ##### The code uses a gamestate enumeration to handle the stage-wise logic.
* ##### As the loop begins, the ultrasonic sensor checks if the distance between the sensor and the player is less than 30 cm.
* ##### If the condition is set, the gamestate is changed.
* ##### In the next state, an array containing the integers 0, 90, and 180 is used to randomly assign an angle for the servo motor.
* ##### The gamestate is changed to waiting\_for\_input, in this stage, the input signal is read to check whether the joystick was moved from the center.
* ##### If yes, the Boolean function check is run to check if the input and the servos angle matches.
* ##### The range of the joystick values are adjusted to correspond to the acceptable values for the angles.
* ##### If the Boolean function returns true, the lcd prints correct and the reaction time is displayed.
* ##### The reaction time is calculated using the millis() function, which returns the time elapsed since the program started running.
* ##### Two variables of the unsigned long datatype are used to take a timestamp at the start and end of the input window, and their difference gives the reaction time in milliseconds.

##### 

##### 

### Challenges:

### 

* ##### This was my first time using enumerations to handle game state logic. Like in the previous Simon Says game, I tried using boolean flags to handle the game state, but realized enumerations made it far simpler, since multiple states could be named clearly.
* ##### The hardware related to the LCD was tricky to handle, since the potentiometer needed to be tuned to get an accurate, readable display.
* ##### lcd.clear() and lcd.print() are called repeatedly throughout the code, which isn't very scalable. A dedicated display-update function should
be used in later versions to fix this.

![image alt](https://github.com/Hercules5952/Learning-Embedded/blob/4fa53c217a2c44d52b4d63d51f7d570e27e5de53/arduino/04-Reaction_test/images/Screenshot%202026-07-25%20112505.png)

#### 

