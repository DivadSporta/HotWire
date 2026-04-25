/**
 * @file MicroSwitch_LEDExample.ino
 * @brief Simple application example using a micro switch and an LED.
 
 */

const int MICRO_SWITCH_PIN = 2; /**< Digital input pin for the micro switch. */
const int LED_PIN = 13;         /**< Digital output pin for the built-in LED. */

/**
 * @brief Initializes the input and output pins.
 */
void setup()
{
  pinMode(MICRO_SWITCH_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

/**
 * @brief Switches the LED depending on the micro switch state.
 */
void loop()
{
  int switchState = digitalRead(MICRO_SWITCH_PIN);

  if (switchState == LOW)
  {
    digitalWrite(LED_PIN, HIGH);
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
  }
}