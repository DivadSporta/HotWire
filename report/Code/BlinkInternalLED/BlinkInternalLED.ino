/**
 * @file BlinkInternalLED.ino
 * @brief Blinks the built-in LED on the Arduino Uno.
 *
 * The Arduino Uno has a built-in LED connected to digital pin D13.
 * No external LED or resistor is required for this test.
 * The LED is switched on and off with a fixed delay.
 */

const int ledPin = 13;  ///< Digital output pin connected to the built-in LED.

/**
 * @brief Configures the built-in LED pin as an output.
 */
void setup() {
  pinMode(ledPin, OUTPUT);
}

/**
 * @brief Switches the built-in LED on and off repeatedly.
 */
void loop() {
  digitalWrite(ledPin, HIGH);
  delay(1000);

  digitalWrite(ledPin, LOW);
  delay(1000);
}