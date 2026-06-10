# Blink

Hi, this is the first hardware project that I made on my own and my first time documenting it. 
Yayy :)

Here is what I learnt from building it:

1. What a microcontroller is.
2. How the code works
3. How does the lights blink the sequence?
4. Which microcontroller does arduino use?

1. A microcontroller is a microelectronic device that has the ability to store precompiled information in the flash memory and use it to control ouputs like pin voltages.
   
2. The code has 2 parts, the setup function which is used to declare the pins that are going to be used for the operation using the pinMode function.
-> It also specifies the type of the operation (input/ output)
The next part is the loop which is where the operation takes place, for this operation we used the digitalWrite function.
-> digitalWrite(12, HIGH);
delay(t);
means to set the voltage to high ie 5V and low means 0v because that is the rating of the pin and the delay states to wait for the specific t ms and go to the next line on the code.

3. This C code is converted into binary to be interpretted by the arduino and create the blinking operation

4. The arduino UNO uses atmega328p.
