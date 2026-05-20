/**
 * @file MosfetPWMTest.ino
 * @brief Tests different PWM output values for a MOSFET PWM switching module.
 */

/// PWM-capable output pin connected to the MOSFET module signal input.
const int MOSFET_PIN = 9;

/// PWM values used for the test sequence.
const int PWM_VALUES[] = {0, 64, 128, 192, 255};

/// Number of PWM values in the test sequence.
const int NUMBER_OF_VALUES = sizeof(PWM_VALUES) / sizeof(PWM_VALUES[0]);

/// Time in milliseconds for each PWM value.
const unsigned long PWM_STEP_DELAY_MS = 5000;

/**
 * @brief Initializes the MOSFET control pin.
 */
void setup() {
  pinMode(MOSFET_PIN, OUTPUT);
  analogWrite(MOSFET_PIN, 0);
}

/**
 * @brief Cycles through predefined PWM values.
 */
void loop() {
  for (int i = 0; i < NUMBER_OF_VALUES; i++) {
    analogWrite(MOSFET_PIN, PWM_VALUES[i]);
    delay(PWM_STEP_DELAY_MS);
  }

  analogWrite(MOSFET_PIN, 0);
  delay(PWM_STEP_DELAY_MS);
}