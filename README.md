# esp32-s3-and-ILI9341-240x320

A simple guide to connecting a **Waveshare ESP32-S3 DEV-KIT NXRX (Espressif)** to a **2.4" ILI9341 240x320 SPI TFT LCD**.

The challenge was getting the screen working **and** being able to use the touch screen with a stylus. After trying several variations, it now works.

Code was written using **PlatformIO** in **VS Code**.

## Pin IO data

| Display pin | ESP32-S3 | Notes |
|---|---|---|
| VCC | 3V3 | These modules have an onboard regulator, but 3V3 keeps the logic levels safe |
| GND | GND | |
| CS | IO10 | Display chip select |
| RESET | IO14 | |
| DC | IO13 | |
| SDI (MOSI) | IO11 | |
| SCK | IO12 | |
| LED | 3V3 | Backlight always on. Use a GPIO (e.g. IO9) for PWM dimming |
| SDO (MISO) | IO8 | |
| T_CLK | IO12 | Shared with SCK |
| T_DIN | IO11 | Shared with MOSI |
| T_DO | IO8 | Shared with MISO |
| T_CS | IO7 | Touch chip select |
| T_IRQ | IO6 | Optional. Only needed for interrupt-driven touch, I did not use it.|

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

<img width="234" height="143" alt="PXL_20261012_091931679~2" src="https://github.com/user-attachments/assets/41376cdc-76d9-4099-bff2-5c6e5e2ab7e3" />
<img width="236" height="189" alt="PXL_20261013_105815637 MACRO_FOCUS~2" src="https://github.com/user-attachments/assets/eab54651-c6d8-44ea-88a0-bbb945b5ce7d" />
<img width="263" height="339" alt="PXL_20261013_094907215~2" src="https://github.com/user-attachments/assets/d5282cba-a809-4b2b-8c62-2c3255e15fde" />



