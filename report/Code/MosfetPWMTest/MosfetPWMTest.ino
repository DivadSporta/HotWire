/**
 * @file MosfetHotwireTest.ino
 * @brief PWM test for controlling a hot wire with a MOSFET module.
 
 */

/// PWM-capable output pin connected to the MOSFET module signal input.
const int MOSFET_PIN = 9;

/// Conservative PWM values for a careful hot wire test.
const int PWM_VALUES[] = {0, 30, 60, 90, 120, 150};

/// Number of PWM values in the test sequence.
const int NUMBER_OF_VALUES = sizeof(PWM_VALUES) / sizeof(PWM_VALUES[0]);

/// Time in milliseconds for each PWM test step.
const unsigned long PWM_STEP_DELAY_MS = 8000;

/// Cooling pause in milliseconds after each full test cycle.
const unsigned long COOLING_DELAY_MS = 10000;

/**
 * @brief Initializes the MOSFET control pin and keeps the output off.
 */
void setup() {
  pinMode(MOSFET_PIN, OUTPUT);
  analogWrite(MOSFET_PIN, 0);
}

/**
 * @brief Applies increasing PWM values and then switches the output off.
 */
void loop() {
  for (int i = 0; i < NUMBER_OF_VALUES; i++) {
    analogWrite(MOSFET_PIN, PWM_VALUES[i]);
    delay(PWM_STEP_DELAY_MS);
  }

  analogWrite(MOSFET_PIN, 0);
  delay(COOLING_DELAY_MS);
}