/**
 * @file druckknopftest.ino
 * @brief Tests a push button and prints 0 or 1 to the serial monitor.
 *
 * The push button is connected between pin 2 and GND.
 * The internal pull-up resistor is used.
 */

const int druckknopfPin = 2; ///< Pin where the push button is connected.

/**
 * @brief Runs once when the Arduino starts.
 *
 * The push button pin is set as an input with the internal pull-up resistor.
 * The serial output is started.
 */
void setup() {
  pinMode(druckknopfPin, INPUT_PULLUP); ///< Sets the pin as input with internal pull-up.
  Serial.begin(115200);                 ///< Starts the serial connection.
}

/**
 * @brief Main program that runs repeatedly.
 *
 * Prints 1 if the push button is pressed.
 * Prints 0 if the push button is not pressed.
 */
void loop() {
  int druckknopfStatus = digitalRead(druckknopfPin); ///< Reads the state of the push button.

  if (druckknopfStatus == LOW) {
    Serial.println(1); ///< Push button is pressed.
  } else {
    Serial.println(0); ///< Push button is not pressed.
  }

  delay(200); ///< Short pause for readable output.
}