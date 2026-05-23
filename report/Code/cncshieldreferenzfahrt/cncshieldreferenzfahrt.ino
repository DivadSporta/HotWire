/**
 * @file cncshieldreferenzfahrt.ino
 * @brief Performs a simple homing movement with a stepper motor and an endstop.
 *
 * The stepper motor is connected to the X-axis driver of the CNC Shield V3.
 * The endstop is connected to the X-endstop input.
 * The motor moves until the endstop is pressed.
 * When the endstop is reached, the motor stops.
 */

const int stepPin = 2;     ///< STEP pin for the X-axis driver.
const int dirPin = 5;      ///< DIR pin for the X-axis driver.
const int enablePin = 8;   ///< Enable pin for the stepper drivers.
const int endstopPin = 9;  ///< Input pin for the X-endstop.

const int stepDelay = 1000; ///< Delay between steps in microseconds.

/**
 * @brief Runs once when the Arduino starts.
 *
 * The motor control pins are configured as outputs.
 * The endstop pin is configured as an input with internal pull-up.
 * The stepper driver is enabled.
 */
void setup() {
  pinMode(stepPin, OUTPUT);          ///< Sets the STEP pin as output.
  pinMode(dirPin, OUTPUT);           ///< Sets the DIR pin as output.
  pinMode(enablePin, OUTPUT);        ///< Sets the ENABLE pin as output.
  pinMode(endstopPin, INPUT_PULLUP); ///< Endstop input with internal pull-up.

  digitalWrite(enablePin, LOW); ///< Enables the stepper driver.
  digitalWrite(dirPin, LOW);    ///< Sets the homing direction.
}

/**
 * @brief Main program that runs repeatedly.
 *
 * The motor moves step by step until the endstop is pressed.
 * When the endstop is pressed, no more step pulses are created.
 */
void loop() {
  if (digitalRead(endstopPin) == HIGH) {
    digitalWrite(stepPin, HIGH); ///< Starts one step pulse.
    delayMicroseconds(stepDelay);

    digitalWrite(stepPin, LOW); ///< Ends one step pulse.
    delayMicroseconds(stepDelay);
  }
}