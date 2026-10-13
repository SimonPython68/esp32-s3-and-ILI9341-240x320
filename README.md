# esp32-s3-and-ILI9341-240x320

This is a simple guide to connect a Waveshare ESP32 S3 DEV-KIT NXRX (Espressif) 
to a 2.4" ILI9341 240x320 SPI TFT LCD.

Challenge was to get the screen working and be able to use a stylus and the touch screen.

I have been through SOME variations and finally have it working.

Once it is working and asking you to calibrate the screen, we need to record the calData, and swap it for the 
 uint16_t calData[5];
  tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);
  Serial.printf("calData = { %u, %u, %u, %u, %u }\n",
    calData[0], calData[1], calData[2], calData[3], calData[4]);
  tft.setTouch(calData);
  tft.fillScreen(TFT_BLACK);

You to remove the above and replace with your calData, I used platformio on VScode to create
this code, you need to click the serial monitor (looks like a plug) and run the calibration,
here is mine: calData = { 576, 3244, 470, 3246, 3 }

Then remove the above and replace with:
uint16_t calData[5] = { 300, 3500, 400, 3600, 1 };  // replace with YOUR numbers
tft.setTouch(calData);
tft.fillScreen(TFT_BLACK);



