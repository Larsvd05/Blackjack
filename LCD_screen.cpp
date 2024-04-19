#include "LCD_screen.h"

byte hartje[8];
byte ruit[8];
byte schoppen[8];
byte klaver[8];

LiquidCrystal_I2C lcd(0x27, 16, 4);

void Init_LCD_scherm(){
    Init_speciale_chars();
    lcd.init(); // Standaard pins zijn D21 (SDA) en D22 (SCL)
    lcd.backlight();
	// lcd.setCursor(0,0);
	// lcd.print("Dealer:");
    // lcd.setCursor(0,1);
	// lcd.print("Speler:");
	// lcd.setCursor(7,3);
	// lcd.print("Inzet:");

    // lcd.createChar(0, hartje);
    // lcd.setCursor(0, 0);
    // lcd.write(0); // Hartje

    // lcd.createChar(1, ruit);
    // lcd.setCursor(0, 1);
    // lcd.write(1); // Ruit

    // lcd.createChar(2, schoppen);
    // lcd.setCursor(0, 2);
    // lcd.write(2); // Schoppen

    // lcd.createChar(3, klaver);
    // lcd.setCursor(0, 3);
    // lcd.write(3); // Klaver

    // lcd.clear();
}


void Init_speciale_chars(){
    // Hartje
    hartje[0] = B00000;
    hartje[1] = B01010;
    hartje[2] = B11111;
    hartje[3] = B11111;
    hartje[4] = B01110;
    hartje[5] = B00100;
    hartje[6] = B00000;
    hartje[7] = B00000;

    // Ruit
    ruit[0] = B00000;
    ruit[1] = B00100;
    ruit[2] = B01110;
    ruit[3] = B11111;
    ruit[4] = B11111;
    ruit[5] = B01110;
    ruit[6] = B00100;
    ruit[7] = B00000;

    // Schoppen
    schoppen[0] = B00000;
    schoppen[1] = B00100;
    schoppen[2] = B01110;
    schoppen[3] = B11111;
    schoppen[4] = B11111;
    schoppen[5] = B10101;
    schoppen[6] = B00100;
    schoppen[7] = B11111;

    // Klaver
    klaver[0] = B00000;
    klaver[1] = B00100;
    klaver[2] = B01110;
    klaver[3] = B10101;
    klaver[4] = B11111;
    klaver[5] = B10101;
    klaver[6] = B00100;
    klaver[7] = B11111;

    lcd.createChar(0, hartje);
    // lcd.createChar(1, ruit);
    // lcd.createChar(2, schoppen);
    // lcd.createChar(3, klaver);
}

void clearLCD(){
    lcd.clear();
}

void printLCD_String(byte row, byte column, String string){
    lcd.setCursor(column, row);
    lcd.print(string);
}

void printLCD_Integer(byte row, byte column, int64_t integer){

}