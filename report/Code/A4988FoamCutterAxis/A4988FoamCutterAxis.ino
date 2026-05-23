/**
 * @file A4988FoamCutterAxis.ino
 * @brief Simple CNC axis movement for a hot wire foam cutter.
 
 */

const uint8_t STEP_PIN = 2;
const uint8_t DIR_PIN  = 5;
const uint8_t EN_PIN   = 8;

const unsigned long AXIS_TRAVEL_STEPS = 1600;

const unsigned int CUTTING_FEED_DELAY_US = 1500;
const unsigned int RETURN_FEED_DELAY_US  = 700;

/**
 * @brief Moves the axis with a defined speed.
 *
 * @param steps Number of steps.
 * @param delayUs Delay between step edges in microseconds.
 */
void moveAxis(unsigned long steps, unsigned int delayUs)
{
    for (unsigned long i = 0; i < steps; i++)
    {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(delayUs);

        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(delayUs);
    }
}

/**
 * @brief Initializes the driver pins.
 */
void setup()
{
    pinMode(STEP_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);

    digitalWrite(EN_PIN, LOW);
}

/**
 * @brief Simulates a simple CNC axis movement.
 */
void loop()
{
    digitalWrite(DIR_PIN, HIGH);
    moveAxis(AXIS_TRAVEL_STEPS, CUTTING_FEED_DELAY_US);

    delay(1500);

    digitalWrite(DIR_PIN, LOW);
    moveAxis(AXIS_TRAVEL_STEPS, RETURN_FEED_DELAY_US);

    delay(1500);
}