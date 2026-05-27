\**
 * Used libraries:
 * - Wire.h
 * - Adafruit_GFX.h
 * - Adafruit_SSD1306.h
 *\

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/**
 * @brief Width of the OLED display in pixels.
 */
#define SCREEN_WIDTH 128

/**
 * @brief Height of the OLED display in pixels.
 */
#define SCREEN_HEIGHT 64

/**
 * @brief Reset pin of the OLED display.
 *
 * A value of -1 is used if the display does not use a separate reset pin.
 */
#define OLED_RESET -1

/**
 * @brief I2C address of the OLED display.
 *
 * Most SSD1306 OLED displays use either 0x3C or 0x3D.
 */
#define OLED_ADDRESS 0x3C

/**
 * @brief OLED display object.
 *
 * This object is used to control the SSD1306 OLED display via the I2C bus.
 */
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/**
 * @brief Initializes the serial interface and the OLED display.
 *
 * The function starts the serial communication, initializes the OLED display
 * and clears the display at startup. If the display cannot be initialized,
 * an error message is printed to the serial monitor and the program stops.
 */
void setup()
{
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS))
  {
    Serial.println("OLED initialization failed!");
    while (true)
    {
      // Stop program if display initialization fails.
    }
  }

  display.clearDisplay();
  display.display();

  Serial.println("OLED function test started.");
}

/**
 * @brief Main program loop for the OLED function test.
 *
 * All pixels are switched on for two seconds and then switched off for two
 * seconds. This blinking pattern is repeated continuously to make defective
 * or dead pixels visible.
 */
void loop()
{
  // Switch all pixels on.
  display.clearDisplay();
  display.fillScreen(SSD1306_WHITE);
  display.display();
  delay(2000);

  // Switch all pixels off.
  display.clearDisplay();
  display.display();
  delay(2000);
}
