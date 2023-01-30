// Compatible with the Arduino IDE 1.0
// Library version:1.1
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C
    lcd(0x27, 16,
        2); // set the LCD address to 0x27 for a 16 chars and 2 line display
int del = 175;
void setup() {
  lcd.init(); // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("Powering up...");
  delay(2000);
  lcd.clear();
}
void loop() {
  lcd.setCursor(15, 0);
  lcd.print("W");
  delay(del);
  lcd.clear();
  lcd.setCursor(14, 0);
  lcd.print("We");
  delay(del);
  lcd.clear();
  lcd.setCursor(13, 0);
  lcd.print("Wel");
  delay(del);
  lcd.clear();
  lcd.setCursor(12, 0);
  lcd.print("Welc");
  delay(del);
  lcd.clear();
  lcd.setCursor(11, 0);
  lcd.print("Welco");
  delay(del);
  lcd.clear();
  lcd.setCursor(10, 0);
  lcd.print("Welcom");
  delay(del);
  lcd.clear();
  lcd.setCursor(9, 0);
  lcd.print("Welcome");
  delay(del);
  lcd.clear();
  lcd.setCursor(8, 0);
  lcd.print("Welcome");
  delay(del);
  lcd.clear();
  lcd.setCursor(7, 0);
  lcd.print("Welcome");
  delay(del);
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("Welcome");
  delay(del);
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("Welcome");
  delay(del);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Welcome");
  delay(del);
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Welcome");
  delay(del);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Welcome");
  delay(del);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Welcome");
  delay(del);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome");
  delay(del);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("elcome");
  delay(del);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("lcome");
  delay(del);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("come");
  delay(del);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ome");
  delay(del);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("me");
  delay(del);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("e");
  delay(del);
  lcd.clear();
}
