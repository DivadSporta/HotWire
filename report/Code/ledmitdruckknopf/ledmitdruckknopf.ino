/**
 * @file ledmitdruckknopf.ino
 * @brief Turns an LED on while a push button is pressed.
 *
 * The push button is connected between pin 2 and GND.
 * The LED is connected to pin 13 with a 220 ohm or 330 ohm series resistor.
 * The long LED leg is the anode (+), and the short LED leg is the cathode (-).
 */

const int druckknopfPin = 2; ///< Pin where the push button is connected.
const int ledPin = 13;      ///< Pin where the LED is connected.

/**
 * @brief Runs once when the Arduino starts.
 *
 * The pins are configured as input or output here.
 */
void setup() {
  pinMode(druckknopfPin, INPUT_PULLUP); ///< Push button input with internal pull-up.
  pinMode(ledPin, OUTPUT);              ///< LED pin as output.
}

/**
 * @brief Main program that runs repeatedly.
 *
 * If the push button is pressed, the LED is turned on.
 * If the push button is released, the LED is turned off.
 */
void loop() {
  int druckknopfStatus = digitalRead(druckknopfPin); ///< Current state of the push button.

  if (druckknopfStatus == LOW) {
    digitalWrite(ledPin, HIGH); ///< Turns the LED on.
  } else {
    digitalWrite(ledPin, LOW);  ///< Turns the LED off.
  }
}