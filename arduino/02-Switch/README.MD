THINGS I LEARNT AFTER DOING THIS:

1. The ON and OFF operation of the LED using a push button switch.


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


Explaination of the code:

1. Instead of manually hardcoding the numbers, we use #define global macros like LED_PIN and BUTTON_PIN for scalability. Also declare a
variable called led_state which is set to LOW along with an int lastbuttonstate.
2. In the setup part of the code, we allocate the pins and using digitalRead we assign result to lastbuttonstate, which will be used to determine the 
button's ON and OFF condition during the last cycle.
3. Under the loop part of the code, by determining another variable called buttonstate, which is for comparing the current state of the switch
and the last button state using the if condition.
4. Let us assume the case that the button was OFF and then ON, 

so,

currentbuttonstate = ON, and the lastbuttonstate = OFF

5. Next step is to update the lastbuttonstate to currentbuttonstate.
6. if(buttonstate == HIGH), which is in this case
7. Toggle the LED state using the boolean expression ledstate = !ledstate;

This ensures that the LED can be turned on and off through the push operation.
