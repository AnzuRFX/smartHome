#include <LiquidCrystal.h>
#include <math.h>
#define PHOTO_PIN A0
#define THERMO_PIN A1
#define THERMO_LED_PIN 2



LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
float brightness = 0.0, thermoPinValue, temperature, lastBrightValue;
bool thermoOn = false;

void setup() {
  lcd.begin(16, 2);
  lcd.print("  GOOD DAY      ");
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
  lastBrightValue = brightness;
  brightness = (1024.0 - analogRead(PHOTO_PIN)) / 1024.0 * 100;

  if(lastBrightValue > 25.0 && brightness > 25.0){
    lcd.setCursor(0, 0);
    lcd.print("  GOOD DAY      ");
  }else if (lastBrightValue <= 25.0 && brightness <= 25.0){
    lcd.setCursor(0, 0);
    lcd.print("  GOOD EVENING  ");
  }

  if(thermoOn && temperature <= 15.0){
    digitalWrite(THERMO_LED_PIN, LOW);
    thermoOn = !thermoOn;
  } 
  if(!thermoOn && temperature >= 17.0){
    digitalWrite(THERMO_LED_PIN, HIGH);
    thermoOn = !thermoOn;
  } 

  setLcdInfo("TEMP:  ", temperature, "C");
  setLcdInfo("LIGHT: ", brightness, "%");
}
