/**
 * @file MicroSwitch_BasicRead.ino
 * @brief Basic example for reading a micro switch.
*/
const int MICRO_SWITCH_PIN = 2; /**< Digital input pin for the micro switch. */

/**
 * @brief Initializes the serial interface and the input pin.
 */
void setup()
{
  Serial.begin(9600);
  pinMode(MICRO_SWITCH_PIN, INPUT_PULLUP);
}

/**
 * @brief Reads the switch state and prints it to the serial monitor.
 */
void loop()
{
  int switchState = digitalRead(MICRO_SWITCH_PIN);

  Serial.print("Micro switch state: ");
  Serial.println(switchState);

  delay(200);
}