/**
 * @file druckknoepfeledabfolge.ino
 * @brief Controls an LED sequence with three push buttons.
 *
 * The start push button starts the LED sequence.
 * The pause push button pauses or continues the sequence.
 * The stop push button stops the sequence and turns all LEDs off.
 */

const int startdruckknopf = 2; ///< Input pin for the start push button.
const int pausedruckknopf = 3; ///< Input pin for the pause push button.
const int stopdruckknopf = 4;  ///< Input pin for the stop push button.

const int ledPins[] = {8, 9, 10, 11, 12}; ///< Output pins for the LEDs.
const int anzahlLeds = 5;                 ///< Number of connected LEDs.

bool programmLaeuft = false; ///< Shows whether the LED sequence is active.
bool programmPause = false;  ///< Shows whether the LED sequence is paused.

int aktuelleLed = 0;                 ///< Number of the currently active LED.
unsigned long letzteZeit = 0;        ///< Time of the last LED change.
const unsigned long intervall = 500; ///< Time between LED changes in milliseconds.

bool letzterPauseStatus = HIGH; ///< Previous state of the pause push button.

/**
 * @brief Runs once when the Arduino starts.
 *
 * The push buttons are set as inputs with internal pull-up resistors.
 * The LED pins are set as outputs.
 */
void setup() {
  pinMode(startdruckknopf, INPUT_PULLUP); ///< Start push button as input.
  pinMode(pausedruckknopf, INPUT_PULLUP); ///< Pause push button as input.
  pinMode(stopdruckknopf, INPUT_PULLUP);  ///< Stop push button as input.

  for (int i = 0; i < anzahlLeds; i++) {
    pinMode(ledPins[i], OUTPUT); ///< Sets the LED pin as output.
  }

  alleLedsAus();
}

/**
 * @brief Main program that runs repeatedly.
 *
 * It checks the three push buttons and controls the LED sequence
 * depending on the input.
 */
void loop() {
  if (digitalRead(startdruckknopf) == LOW) {
    programmLaeuft = true;
    programmPause = false;
  }

  if (digitalRead(stopdruckknopf) == LOW) {
    programmLaeuft = false;
    programmPause = false;
    aktuelleLed = 0;
    alleLedsAus();
  }

  bool aktuellerPauseStatus = digitalRead(pausedruckknopf); ///< Current state of the pause push button.

  if (letzterPauseStatus == HIGH && aktuellerPauseStatus == LOW) {
    programmPause = !programmPause;
    delay(200); ///< Simple debounce for the push button.
  }

  letzterPauseStatus = aktuellerPauseStatus;

  if (programmLaeuft && !programmPause) {
    ledAbfolge();
  }
}

/**
 * @brief Turns all LEDs off.
 *
 * All LED pins are set to LOW.
 */
void alleLedsAus() {
  for (int i = 0; i < anzahlLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

/**
 * @brief Makes the LEDs light up one after another.
 *
 * After the defined interval has passed, the current LED is turned off
 * and the next LED is turned on.
 */
void ledAbfolge() {
  unsigned long aktuelleZeit = millis(); ///< Current runtime of the Arduino in milliseconds.

  if (aktuelleZeit - letzteZeit >= intervall) {
    letzteZeit = aktuelleZeit;

    alleLedsAus();
    digitalWrite(ledPins[aktuelleLed], HIGH);

    aktuelleLed++;

    if (aktuelleLed >= anzahlLeds) {
      aktuelleLed = 0;
    }
  }
}