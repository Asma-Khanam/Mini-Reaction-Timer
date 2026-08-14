/*
  Mini Reaction Timer
  A tiny Arduino build inspired by the Psychomotor Vigilance Task (PVT),
  a real tool used in sleep and attention research.

  An LED lights up after a random delay, you press a button the instant
  you see it, and the sketch reports how many milliseconds passed in
  between. That gap is your reaction time.

  Hardware:
    - 1x LED (any color)
    - 1x 220 ohm resistor
    - 1x push button (tact switch)
    - Breadboard and jumper wires
    - Arduino Uno (or compatible board)

  Wiring:
    - LED anode (long leg) -> 220 ohm resistor -> Arduino pin 8
    - LED cathode (short leg) -> Arduino GND
    - Button pin one -> Arduino pin 2
    - Button pin two -> Arduino GND
    (Full wiring diagram included in this repo)

  Built as a fun side project, not part of any formal research study.
*/

const int LED_PIN = 8;
const int BUTTON_PIN = 2;
const int SERIAL_BAUD_RATE = 9600;

const unsigned long MIN_WAIT_MS = 2000;   // shortest possible wait before the light turns on
const unsigned long MAX_WAIT_MS = 6000;   // longest possible wait before the light turns on
const unsigned long FALSE_START_PAUSE_MS = 1500; // pause shown after a false start message

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // button reads HIGH normally, LOW when pressed

  Serial.begin(SERIAL_BAUD_RATE);
  randomSeed(analogRead(A0)); // seeds the random generator using electrical noise on an unused pin
}

void loop() {
  Serial.println("Get ready...");
  digitalWrite(LED_PIN, LOW);

  if (waitAndCheckFalseStart()) {
    Serial.println("Too soon! Wait for the light next time.");
    delay(FALSE_START_PAUSE_MS);
    return; // skip the rest of this round, start a fresh one
  }

  unsigned long reactionTime = measureReactionTime();

  Serial.print("Reaction time: ");
  Serial.print(reactionTime);
  Serial.println(" ms");

  delay(2000); // brief pause before the next round begins
}

// Waits a random amount of time before the light turns on.
// Returns true if the button was pressed early (a false start).
bool waitAndCheckFalseStart() {
  unsigned long waitTime = random(MIN_WAIT_MS, MAX_WAIT_MS);
  unsigned long waitStart = millis();

  while (millis() - waitStart < waitTime) {
    if (digitalRead(BUTTON_PIN) == LOW) {
      return true;
    }
  }
  return false;
}

// Turns the LED on, waits for the button press, and returns the elapsed time in milliseconds.
unsigned long measureReactionTime() {
  digitalWrite(LED_PIN, HIGH);
  unsigned long startTime = millis();

  while (digitalRead(BUTTON_PIN) == HIGH) {
    // waiting for the press, nothing else happens here on purpose
  }

  digitalWrite(LED_PIN, LOW);
  return millis() - startTime;
}
