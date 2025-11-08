#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <DHT_U.h>

// LCD I2C address (try 0x27 or 0x3F if not working)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// DHT sensor setup
#define DHTPIN 2       // DHT11 data pin connected to D2
#define DHTTYPE DHT11  // Sensor type
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);   // Start Serial Monitor
  lcd.init();           // Initialize LCD
  lcd.backlight();      // Turn on LCD backlight
  dht.begin();          // Start DHT11 sensor

  lcd.setCursor(0, 0);
  lcd.print("Temp & Humidity");
  delay(2000);
  lcd.clear();

  Serial.println("DHT11 Temperature & Humidity Monitor");
  Serial.println("--------------------------------------");
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius by default

  // Check for read errors
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
    delay(2000);
    return;
  }

  // --- Print to Serial Monitor ---
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C   ");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // --- Display on LCD ---
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print((char)223); // Degree symbol
  lcd.print("C  ");

  lcd.setCursor(0, 1);
  lcd.print("Hum:  ");
  lcd.print(humidity);
  lcd.print("%   ");

  delay(2000); // Wait 2 seconds before next reading
}