#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Configured for Arduino Uno boards

#define DHTPIN 2
#define DHTTYPE DHT11  // Change to DHT22 if using a white sensor

// Initialize components
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  dht.begin();

  lcd.setCursor(0, 0);
  lcd.print("Climate Station");
  lcd.setCursor(0, 1);
  lcd.print("Waking up sensor");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Pull values from DHT sensor
  float temp = dht.readTemperature();  // Celsius
  float hum = dht.readHumidity();      // Percentage

  // Double-check if readings succeeded
  if (isnan(temp) || isnan(hum)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!   ");
    lcd.setCursor(0, 1);
    lcd.print("Check wires...  ");
    return;
  }

  // Output details onto the LCD matrix
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp, 1);  // 1 Decimal place precision
  lcd.print("C   ");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print((int)hum);
  lcd.print("%   ");

  delay(2000);  // DHT11 handles reads best at 2-second intervals
}