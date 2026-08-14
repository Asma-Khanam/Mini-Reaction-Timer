# Mini Reaction Timer

![Arduino](https://img.shields.io/badge/Arduino-Uno-00979D?logo=arduino&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-blue.svg)
![Status](https://img.shields.io/badge/Status-Just%20for%20fun-lightgrey)

A tiny Arduino build made for fun during a break from my MSc dissertation work. It measures human reaction time using an LED, a push button, and the Arduino's internal clock.

This is a personal side project, not a research study, and not connected to any formal academic work.

---

## Contents

- [The idea](#the-idea)
- [Hardware used](#hardware-used)
- [Wiring](#wiring)
- [How the timing works](#how-the-timing-works)
- [Sample output](#sample-output)
- [Usage](#usage)
- [License](#license)

---

## The idea

The design is loosely inspired by the **Psychomotor Vigilance Task (PVT)**, a real tool used in sleep and attention research. A light turns on after a random, unpredictable delay, the person watching presses a button the instant they notice it, and the gap between those two moments is their reaction time, measured in milliseconds (thousandths of a second).

The wait before the light turns on is randomized on purpose. If it always came after a fixed delay, the brain would start predicting it rather than genuinely reacting to it. Pressing before the light appears counts as a false start, sometimes called an anticipatory response, a guess rather than a real reaction.

---

## Hardware used

| Component | Quantity |
|---|---|
| Arduino Uno | 1 |
| LED | 1 |
| 220 ohm resistor | 1 |
| Push button (tact switch) | 1 |
| Breadboard | 1 |
| Jumper wires | a handful |
| USB cable | 1 |

---

## Wiring

| From | To |
|---|---|
| LED anode (long leg) | 220 ohm resistor, then Arduino pin 8 |
| LED cathode (short leg) | Arduino GND |
| Button pin one | Arduino pin 2 |
| Button pin two | Arduino GND |

Full wiring diagram: [`reaction_timer_wiring_diagram.mermaid`](./reaction_timer_wiring_diagram.mermaid), renders natively on GitHub.

The button uses the Arduino's built in pull up resistor (`INPUT_PULLUP`), so no extra resistor is needed for it. The pin reads HIGH normally and drops to LOW the instant it is pressed.

---

## How the timing works

The sketch uses `millis()`, a built in Arduino function that counts milliseconds since the board powered on. The moment the LED turns on, the current millisecond count is stored. The moment the button is pressed, the count is taken again, and the difference between the two is the reaction time.

---

## Sample output
