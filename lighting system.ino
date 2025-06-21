#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pirEntry = 2;
const int pirExit = 3;
const int ledPin = 13;

int count = 0;
bool entryDetected = false;
bool exitDetected = false;

void setup() {
  pinMode(pirEntry, INPUT);
  pinMode(pirExit, INPUT);
  pinMode(ledPin, OUTPUT);
  
  lcd.init();         // Initialize the LCD
lcd.backlight();    // Turn on the backlight
delay(500);
  lcd.setCursor(0, 0);
  lcd.print("Room Lighting");
  delay(1000);
  lcd.clear();
}

void loop() {
  int entryVal = digitalRead(pirEntry);
  int exitVal = digitalRead(pirExit);

  if (entryVal == HIGH && !entryDetected) {
    count++;
    entryDetected = true;
    updateDisplay();
  }
  if (entryVal == LOW) entryDetected = false;

  if (exitVal == HIGH && !exitDetected && count > 0) {
    count--;
    exitDetected = true;
    updateDisplay();
  }
  if (exitVal == LOW) exitDetected = false;

  digitalWrite(ledPin, count > 0 ? HIGH : LOW);
  delay(100);
}

void updateDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  if (count > 0) {
    lcd.print("Room Occupied");
    lcd.setCursor(0, 1);
    lcd.print("Count: ");
    lcd.print(count);
  } else {
    lcd.print("Room Empty");
    lcd.setCursor(0, 1);
    lcd.print("Light OFF");
  }
}

