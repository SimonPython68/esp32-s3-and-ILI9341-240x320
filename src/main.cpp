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

 uint16_t calData[5] = { 498, 3329, 436, 3312, 3 };  // replace with YOUR numbers
  tft.setTouch(calData);
  tft.fillScreen(TFT_BLACK);;  // replace with YOUR numbers
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