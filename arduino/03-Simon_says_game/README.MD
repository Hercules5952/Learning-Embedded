# Simon Says Memory Game

A hardware recreation of the classic Simon Says memory game, built with an Arduino, 4 LEDs, 4 push buttons, and an active buzzer. Made to apply and document the basics of digital I/O, debouncing, timing, and state tracking on a microcontroller.

## Overview

The game generates a random sequence of LED blinks that becomes faster each round. The player has to repeat the sequence by pressing the matching buttons in order. On getting it right, and the game adds a new step and speeds up. On getting it wrong, and all LEDs flash to indicate the mistake before the game resets.

## How It Works

1. The game starts by picking a random LED (0-3) using random() and storing it to a sequence[] array.

2. The full sequence so far is played back to the player via LED blinks.

3. The player then has to replay the sequence by pressing the corresponding buttons.

4. Each correct press is checked against sequence[player_step]. On being right, player_step increments by 1.

5. Once player_step reaches seq_length, the round is won, a new random step is put, and the sequence plays again (now one step longer).

6. Every successful round decreases the blink delay (del) by 20ms, until the del becomes 100ms, making the game progressively faster.

7. Any incorrect press immediately flashes all LEDs, resets player_step and seq_length, and starts a new sequence from scratch.

## Hardware

LEDs, 4 Each in series with a 220Ω resistor

Push buttons 4 Using Arduino's internal pull-up resistors (`INPUT_PULLUP`)

Active buzzer 1 Connected to digital pin 10

Arduino board 1

### Circuit Connections

* LEDs: Each LED's resistor-side lead connects to its assigned digital pin; the other side goes to GND.

* Buttons: Each button connects a digital pin to GND. Since INPUT_PULLUP is used, no external pullup resistors are needed. Pins read HIGH by default and LOW when pressed.

* Buzzer: Positive lead to digital pin 10, negative to GND. Beeps on every button press and on incorrect input.

## Code Structure

* sequence[] — stores the full LED pattern generated so far.

* seq_length — current length of the sequence the player must repeat.

* player_step — used to track how far into the sequence the player has correctly progressed.

* sequenceShown — boolean expression that is used to check whether a new pattern needs to be displayed before accepting input.

* del — controls blink/playback speed; decreases by 20ms per round to ramp up difficulty.

* checkInput() (function referred to as switch_correct() during development) checks button states against the expected sequence step, updates player_step, and returns true once the whole sequence is matched correctly.

## Key Concepts Applied

* Array-based sequence generation and comparison

* Global state tracking across loop iterations

* INPUT_PULLUP for button wiring without external resistors

* Progressive difficulty scaling via a decrementing delay variable

* Basic game-loop structure on a microcontroller (generate → display → capture input → validate → reset/advance)

## Possible Improvements

* Use an LCD display to track the score and improve the code structure to reduce time taken to compute.

## Demo

---

Part of my self-directed embedded systems learning roadmap.
