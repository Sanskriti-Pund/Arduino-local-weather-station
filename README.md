# Arduino Local Weather Station

A simple, compact desktop weather station built with an Arduino. The system reads the data from a 4-pin climate sensor and displays real-time data updates directly onto an I2C-enabled 1602 LCD screen. 


---

## Features
* **Live Environmental Tracking:** Constantly samples the environment for accurate climate metrics.
* **Smart Display Refresh:** Updates the LCD grid only when sensor values fluctuate, preventing screen flicker.
* **Clean 4-Wire I2C Setup:** Uses an I2C communication bus to run the entire project with minimal, clutter-free wiring.

---

## Hardware Components
* **Arduino Board** (Uno R3, Uno R4, or similar)(I used UNO R4 lite)
* **1602 Character LCD Display** (with I2C Backpack module)
* **4-Pin Climate Sensor** DHT11
* Breadboard and standard jumper wires

---

## Wiring Configuration

### 1. I2C LCD Screen Connection
* **VCC** -> Arduino **5V**
* **GND** -> Arduino **GND**
* **SDA** -> Arduino **A4**
* **SCL** -> Arduino **A5**

### 2. Climate Sensor Setup (4-Pin Layout)
*(- Note: Pin 1 starts from the left side when looking directly at the front of your sensor.)*

* **Pin 1 (VCC):** -> Arduino **5V**
* **Pin 2 (Data/SDA):** -> Arduino Digital Pin **2**
* **Pin 3 (Null/SCL):** -> Leave unconnected
* **Pin 4 (GND):** -> Arduino **GND**

---

## Libraries required

Install the libraries `DHT sensor library` by Adafruit and `LiquidCrystal_I2C` module.

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 2     
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  dht.begin();
  
  lcd.setCursor(0, 0);
  lcd.print("Weather Station");
  lcd.setCursor(0, 1);
  lcd.print("Starting up...");
  delay(2000);
  lcd.clear();
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Basic check to see if the sensor is acting up or unplugged
  if (isnan(humidity) || isnan(temperature)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!   ");
    return;
  }

  // Top Row: Temperature
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1); 
  lcd.print((char)223);      // Degree symbol (°)
  lcd.print("C   ");

  // Bottom Row: Humidity
  lcd.setCursor(0, 1);
  lcd.print("Humid: ");
  lcd.print(humidity, 1);
  lcd.print("%   ");

  // The DHT11 updates slowly, so checking every 2 seconds is perfect
  delay(2000); 
}
