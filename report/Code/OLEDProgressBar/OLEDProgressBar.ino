
#include <Wire.h>              ///< Library for I2C communication.
#include <Adafruit_GFX.h>      ///< Graphics library for drawing functions.
#include <Adafruit_SSD1306.h>  ///< Library for controlling the SSD1306 OLED display.

/**
 * @def SCREEN_WIDTH
 * @brief Width of the OLED display in pixels.
 */
#define SCREEN_WIDTH 128

/**
 * @def SCREEN_HEIGHT
 * @brief Height of the OLED display in pixels.
 */
#define SCREEN_HEIGHT 64

/**
 * @def OLED_RESET
 * @brief Reset pin of the OLED display.
 *
 * A value of -1 means that no separate reset pin is used.
 */
#define OLED_RESET -1

/**
 * @brief Object for controlling the OLED display.
 *
 * The display is initialized with a resolution of 128 x 64 pixels
 * via the I2C interface.
 */
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/**
 * @def BUTTON_PIN
 * @brief Pin connected to the push button.
 *
 * The input uses the internal pull-up resistor.
 * Therefore, the input is HIGH in idle state and LOW when pressed.
 */
#define BUTTON_PIN 2

/**
 * @brief Initializes the button and OLED display.
 *
 * In this function, the button pin is configured as an input with
 * an internal pull-up resistor. Afterwards, the OLED display is
 * started, cleared, and prepared for text output.
 *
 * @return void
 */
void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

/**
 * @brief Main program loop.
 *
 * The function continuously checks whether the button is pressed.
 * If the button is pressed, a progress bar from 0% to 100%
 * is displayed on the OLED display in steps of 10%.
 *
 * @return void
 */
void loop() {

  /**
   * @brief Checks whether the button is pressed.
   *
   * Since the button uses INPUT_PULLUP, LOW means the button is pressed.
   */
  if (digitalRead(BUTTON_PIN) == LOW) {

    /**
     * @brief Loop for displaying the progress.
     *
     * The loop runs from 0 to 10. The current loop value is converted
     * into a percentage and displayed on the screen.
     */
    for (int i = 0; i <= 10; i++) {

      /**
       * @brief Current progress in percent.
       *
       * The value is calculated from the loop counter.
       */
      int percent = i * 10;

      display.clearDisplay();

      display.setCursor(0, 0);
      display.print("Progress:");

      display.setCursor(90, 0);
      display.print(percent);
      display.print("%");

      /**
       * @brief Draws the frame of the progress bar.
       *
       * Position: x = 10, y = 30.
       * Size: width = 108 pixels, height = 10 pixels.
       */
      display.drawRect(10, 30, 108, 10, SSD1306_WHITE);

      /**
       * @brief Calculates the current width of the filled bar.
       *
       * The width is calculated proportionally to the progress.
       */
      int barWidth = (108 * percent) / 100;

      /**
       * @brief Draws the filled part of the progress bar.
       */
      display.fillRect(10, 30, barWidth, 10, SSD1306_WHITE);

      /**
       * @brief Updates the OLED display.
       */
      display.display();

      delay(300);
    }

    delay(1000);
  }
}
