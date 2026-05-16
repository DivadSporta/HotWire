#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BUTTON_PIN 2

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {

    for (int i = 0; i <= 10; i++) {

      int percent = i * 10;

      display.clearDisplay();

      display.setCursor(0, 0);
      display.print("Fortschritt:");

      display.setCursor(90, 0);
      display.print(percent);
      display.print("%");

      display.drawRect(10, 30, 108, 10, SSD1306_WHITE);

      int barWidth = (108 * percent) / 100;
      display.fillRect(10, 30, barWidth, 10, SSD1306_WHITE);

      display.display();

      delay(300);
    }

    delay(1000);
  }
}
