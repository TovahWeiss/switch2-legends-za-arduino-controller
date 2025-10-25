Pokémon Legends ZA automation
===============================

**Note:** This is designed for the switch 2. If you want to use this on the switch 1, you will need to set up the arduino with the initialization methods found in [VinDuv's original repo](https://github.com/VinDuv/switch-arduino-controller) and adjust timing to be about tripple for loading zones and animations.

This module automates shiny rolling in legends ZA.

Requirements
------------

You will need an Arduino UNO R3, an external Arduino programmer, and a
pushbutton inserted in the Arduino board, between pins 13 and GND (on the top
row).

You can additionally install a buzzer between pins 2 and GND.

See [the main README](../../README.md#required-hardware) for details.

Installation
------------

Use `make` to build the `usb-iface.hex` and `za.hex` files. Flash
`usb-iface.hex` to the USB interface microcontroller (ATmega16U2), and
`za.hex` to the main microcontroller (ATmega328P).

See the main README for the
[required software](../../README.md#required-software), the
[build procedure](../../README.md#building), and the
[programming procedure](../../README.md#programming).

Usage
-----

Plug the Arduino to the Switch; the L LED on the Arduino board should start
blinking rapidly, and the TX/RX LEDs should be off.

To start the automation process, start Pokémon Sword/Shield (if it is not
already), and put the game in the required state (which depends on the task to
be automated; see below for details).

Press Home to get to the Switch main menu (the selection should be on
the game icon) and press the pushbutton on the Arduino board. The emulated
controller will get auto-registered as controller 2.

Once it’s ready, the Arduino L LED will blink once per second, and both the
RX and TX LEDs will be lit up. You are in the “main menu”, which allows you
to select which automation feature to perform. Press the pushbutton on the
board once to activate feature 1; twice to activate feature 2; etc.

The different automation features are described below.

### Reroll wild area [Feature 1 — one button press]

**Pre-requisites:** Warp to the wild area you will be working rerolling via its main icon.

Sub menu one:
Select your grouping of areas (see table)

Sub menu two: Select your area (see table)

|Presses in sub menu 1 | Presses in sub menu 2 | Resulting Zone |
| --- | --- | --- |
| 1	| 1	|1|
| 1	| 2	|2|
| 1	| 3	|3|
| 1	| 4	|4|
| 1	| 5	|5|
| 2	| 1	|6*|
| 2	| 2	|7|
| 2	| 3	|8|
| 2	| 4	|9|
| 2	| 5	|10|
| 3	| 1	|11|
| 3	| 2	|12|
| 3	| 3	|13|
| 3	| 4	|14|
| 3	| 5	|15|
| 4	| 1	|16|
| 4	| 2	|17|
| 4	| 3	|18|
| 4	| 4	|19|
| 4	| 5	|20|

**Note** Zone 6 requies Cafe Bataille to be accessable. The reroll will drop you there to increase spawn radius after the intial set up and orientation.

### Tower Rerolling [Feature 2 - two button presses]

**Pre-requisites:** Be at the top of the tower in area 3, directly after exiting the stairs up, facing away from the zone 

### Teleporter Rerolling [Feature 3 - three button presses]

**Pre-requisites:** Stand on a teleporter pad in Lysandre Labs

### Honedge Resetting [Feature 4 - four button presses]

**Pre-requisites:** Go through the first teleporter pad in Lysandre Labs directly in front of the elevator at the enterance.

This command will run far enough into the room with Duoblade and two Honedge to reroll them, then return to the teleporter pad and reset the process.

