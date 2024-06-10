#include <LiquidCrystal.h>
#include <math.h>
#define PHOTO_PIN A0
#define THERMO_PIN A1



LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
float brightness, thermoPinValue, temperature;

void setup() {
  lcd.begin(16, 2);
  lcd.print("   SMART HOME   ");
}

void setLcdInfo(String parameter, float value, String unit){
  lcd.setCursor(1, 1);
  lcd.print(parameter);
  lcd.setCursor(9, 1);
  lcd.print(value, 1);
  lcd.setCursor(14, 1);
  lcd.print(unit + " ");
  delay(3000);
}


void loop() {
  thermoPinValue = analogRead(THERMO_PIN) * 5.0 / 1024.0;
  temperature = -14.46 * log((10000.0 * thermoPinValue) / (5.0 - thermoPinValue) / 27074.0);
  brightness = (1024.0 - analogRead(PHOTO_PIN)) / 1024.0 * 100;

  setLcdInfo("TEMP:  ", temperature, "C");
  setLcdInfo("LIGHT: ", brightness, "%");
}