/**
 * @file CNCShieldSimpleStep.ino
 * @brief Basic function test for one axis on a CNC Shield V3.
 
 * @date 2026-05-25
 */

const uint8_t ENABLE_PIN = 8;     /**< Enable pin for all stepper drivers, active LOW. */
const uint8_t X_STEP_PIN = 2;     /**< STEP pin for the X-axis driver. */
const uint8_t X_DIR_PIN  = 5;     /**< DIR pin for the X-axis driver. */

const unsigned int STEP_DELAY_US = 1000; /**< Delay between step edges in microseconds. */

/**
 * @brief Initializes the CNC Shield pins and enables the stepper drivers.
 */
void setup()
{
    pinMode(ENABLE_PIN, OUTPUT);
    pinMode(X_STEP_PIN, OUTPUT);
    pinMode(X_DIR_PIN, OUTPUT);

    digitalWrite(ENABLE_PIN, LOW);
    digitalWrite(X_DIR_PIN, HIGH);
}

/**
 * @brief Generates continuous step pulses on the X-axis.
 */
void loop()
{
    digitalWrite(X_STEP_PIN, HIGH);
    delayMicroseconds(STEP_DELAY_US);
    digitalWrite(X_STEP_PIN, LOW);
    delayMicroseconds(STEP_DELAY_US);
}
