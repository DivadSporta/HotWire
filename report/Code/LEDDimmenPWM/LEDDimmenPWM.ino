/**
 * @file LEDDimmenPWM.ino
 * @brief Dims an LED using a PWM output pin.
 *
 * The LED is connected to digital PWM output pin D9.
 * The brightness is changed with analogWrite().
 */

const int ledPin = 9; ///< Digital PWM output pin connected to the LED.

/**
 * @brief Configures the LED pin as an output.
 */
void setup()
{
  pinMode(ledPin, OUTPUT);
}

/**
 * @brief Increases and decreases the LED brightness repeatedly.
 */
void loop()
{
  for (int brightness = 0; brightness <= 255; brightness++)
  {
    analogWrite(ledPin, brightness);
    delay(10);
  }

  for (int brightness = 255; brightness >= 0; brightness--)
  {
    analogWrite(ledPin, brightness);
    delay(10);
  }
}