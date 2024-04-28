#include "LCD_screen.h"

byte hartje[8];
byte ruit[8];
byte schoppen[8];
byte klaver[8];

LiquidCrystal_I2C lcd(0x27, 16, 4);

void Init_LCD_scherm() {
  lcd.init(); // Standaard pins zijn D21 (SDA) en D22 (SCL)
  Init_speciale_chars();
  lcd.backlight();
}

void Init_speciale_chars() {
  // Hartje
  hartje[0] = B00000;
  hartje[1] = B01010;
  hartje[2] = B11111;
  hartje[3] = B11111;
  hartje[4] = B01110;
  hartje[5] = B00100;
  hartje[6] = B00000;
  hartje[7] = B00000;
  lcd.createChar(0, hartje);

  // Ruit
  ruit[0] = B00000;
  ruit[1] = B00100;
  ruit[2] = B01110;
  ruit[3] = B11111;
  ruit[4] = B11111;
  ruit[5] = B01110;
  ruit[6] = B00100;
  ruit[7] = B00000;
  lcd.createChar(1, ruit);

  // Schoppen
  schoppen[0] = B00000;
  schoppen[1] = B00100;
  schoppen[2] = B01110;
  schoppen[3] = B11111;
  schoppen[4] = B11111;
  schoppen[5] = B10101;
  schoppen[6] = B00100;
  schoppen[7] = B00100;
  lcd.createChar(2, schoppen);

  // Klaver
  klaver[0] = B00000;
  klaver[1] = B00100;
  klaver[2] = B01110;
  klaver[3] = B10101;
  klaver[4] = B11111;
  klaver[5] = B10101;
  klaver[6] = B00100;
  klaver[7] = B11111;
  lcd.createChar(3, klaver);
}

void clearLCD() { lcd.clear(); }

void printLCD_String(byte row, byte column, String string) {
  lcd.setCursor(column, row);
  lcd.print(string);
}

void printLCD_SpecialChar(byte row, byte column, byte specialChar) {
  lcd.setCursor(column, row);
  lcd.write(specialChar);
}

// void printLCD_Integer(byte row, byte column, int64_t integer){
//     lcd.setCursor(column, row);
//     lcd.print(integer);
// }