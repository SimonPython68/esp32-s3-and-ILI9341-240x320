#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("Touch the screen", 20, 10, 2);

  uint16_t calData[5];
  tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);
  Serial.printf("calData = { %u, %u, %u, %u, %u }\n",
    calData[0], calData[1], calData[2], calData[3], calData[4]);
  tft.setTouch(calData);
  tft.fillScreen(TFT_BLACK);
}

void loop() {
  uint16_t x, y;
  if (tft.getTouch(&x, &y, 200)) {
    Serial.printf("touch x=%u y=%u\n", x, y);
    tft.fillCircle(x, y, 3, TFT_GREEN);
  }
}
