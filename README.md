# esp32-s3-and-ILI9341-240x320

A simple guide to connecting a **Waveshare ESP32-S3 DEV-KIT NXRX (Espressif)** to a **2.4" ILI9341 240x320 SPI TFT LCD**.

The challenge was getting the screen working **and** being able to use the touch screen with a stylus. After trying several variations, it now works.

Code was written using **PlatformIO** in **VS Code**.

## Touch calibration

Once the display is working, it will prompt you to calibrate the touch screen. You then need to record the resulting `calData` values and swap the calibration code for a hard-coded version, so you don't have to recalibrate on every boot.

### Step 1: Run the calibration

Use the following code to run the calibration:

```cpp
uint16_t calData[5];
tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);
Serial.printf("calData = { %u, %u, %u, %u, %u }\n",
              calData[0], calData[1], calData[2], calData[3], calData[4]);
tft.setTouch(calData);
tft.fillScreen(TFT_BLACK);
```

### Step 2: Record your values

1. In VS Code / PlatformIO, click the **Serial Monitor** icon (it looks like a plug).
2. Run the calibration on the screen by touching the targets as prompted.
3. Copy the `calData` line printed in the serial monitor.

Here is mine:

```
calData = { 576, 3244, 470, 3246, 3 }
```

> Your numbers will differ, so use your own values.

### Step 3: Replace the calibration code

Remove the calibration code from Step 1 and replace it with your recorded values:

```cpp
uint16_t calData[5] = { 300, 3500, 400, 3600, 1 }; // replace with YOUR numbers
tft.setTouch(calData);
tft.fillScreen(TFT_BLACK);
```

The touch screen will now work without prompting for calibration on each startup.
