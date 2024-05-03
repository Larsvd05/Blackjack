//
// Created by lars on 15/04/24.
//

#include "LCD_screen.h"

byte hartje[8];
byte ruit[8];
byte schoppen[8];
byte klaver[8];

char seperatorChar = ' ';
uint16_t delayPrint;
byte lengteSpelerNaam;
char dealerKaartenArray[50]; // 50, want 1 deck heeft 52 en de speler heeft al 2
                             // kaarten gepakt.
char spelerKaartenArray[50]; // 50, want 1 deck heeft 52 en de dealer heeft al 2
                             // kaarten gepakt.

byte minimaleLengte = lengteSpelerNaam + 1;
byte ruimteKaartenSpeler = 20 - minimaleLengte;

bool scrollDealer = false;
bool scrollSpeler = false;

LiquidCrystal_I2C lcd(0x27, 20, 4);

void Init_LCD_scherm() {
  lcd.init();      // Standaard pins zijn D21 (SDA) en D22 (SCL)
  delayPrint = 50; // Pas dit aan om de delay tussen het printen aan te passen
                   // tijdens het printen van de kaarten.
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

void printLCD_Char(byte row, byte column, char aChar) {
  lcd.setCursor(column, row);
  lcd.print(aChar);
}

void LCD_printKaarten(bool verberg2eKaartDealer) {
  byte fase = 1; // Fase 1 = seperator + specialChar, Fase 2 = waarde kaart.
  byte count = 0;
  char temp;
  LCD_checkOfScrollNodigIs();
  if (scrollDealer) {
    for (byte offset = 0; offset < (LCD_getAchtersteLocatieDealer() - 13 + 4);
         offset++) {
      if (dealerKaartenArray[offset] != seperatorChar) {

      } else {
        LCD_resetRow(13, 0, 7, ' ');
        count = 0;
        for (int i = 0; i < 13; i++) {
          temp = dealerKaartenArray[i + offset];
          if (temp == '\0') {
            break;
          } else {
            if (temp == seperatorChar) {
              printLCD_Char(0, 7 + count, temp);
              ++count;
              printLCD_SpecialChar(0, 7 + count,
                                   dealerKaartenArray[i + 1 + offset] - 48);
              ++count;
              ++i;
              fase = 2;
            } else if (fase == 2) {
              printLCD_Char(0, 7 + count, temp);
              ++count;
              if (dealerKaartenArray[i + 1 + offset] == '0') {
                printLCD_Char(0, 7 + count, '0');
                ++count;
                ++i;
              }
              fase = 1;
            }
          }
        }
        delay(2000);
      }
    }
  } else {
    for (int i = 0; i < 13; i++) {
      if (verberg2eKaartDealer && i > 2) {
        break;
      } else {
        temp = dealerKaartenArray[i];
        if (temp == '\0') {
          break;
        } else {
          if (temp == seperatorChar) {
            printLCD_Char(0, 7 + count, temp);
            ++count;
            printLCD_SpecialChar(0, 7 + count, dealerKaartenArray[i + 1] - 48);
            ++count;
            ++i;
            fase = 2;
          } else if (fase == 2) {
            printLCD_Char(0, 7 + count, temp);
            ++count;
            if (dealerKaartenArray[i + 1] == '0') {
              printLCD_Char(0, 7 + count, '0');
              ++count;
              ++i;
            }
            fase = 1;
          }
        }
      }
    }
  }
  if (scrollSpeler) {
    for (byte offset = 0;
         offset < (LCD_getAchtersteLocatieSpeler() - ruimteKaartenSpeler + 4);
         offset++) {
      if (spelerKaartenArray[offset] != seperatorChar) {

      } else {
        LCD_resetRow(ruimteKaartenSpeler, 1, minimaleLengte, ' ');
        count = 0;
        for (int i = 0; i < ruimteKaartenSpeler; i++) {
          temp = spelerKaartenArray[i + offset];
          if (temp == '\0') {
            break;
          } else {
            if (temp == seperatorChar) {
              printLCD_Char(1, minimaleLengte + count, temp);
              ++count;
              printLCD_SpecialChar(1, minimaleLengte + count,
                                   spelerKaartenArray[i + 1 + offset] - 48);
              ++count;
              ++i;
              fase = 2;
            } else if (fase == 2) {
              printLCD_Char(1, minimaleLengte + count, temp);
              ++count;
              if (spelerKaartenArray[i + 1 + offset] == '0') {
                printLCD_Char(1, minimaleLengte + count, '0');
                ++count;
                ++i;
              }
              fase = 1;
            }
          }
        }
        delay(2000);
      }
    }
  } else {
    count = 0;
    for (int i = 0; i < ruimteKaartenSpeler; i++) {
      temp = spelerKaartenArray[i];
      if (temp == '\0') {
        break;
      } else {
        if (temp == seperatorChar) {
          printLCD_Char(1, minimaleLengte + count, temp);
          ++count;
          printLCD_SpecialChar(1, minimaleLengte + count,
                               spelerKaartenArray[i + 1] - 48);
          ++count;
          ++i;
          fase = 2;
        } else if (fase == 2) {
          printLCD_Char(1, minimaleLengte + count, temp);
          ++count;
          if (spelerKaartenArray[i + 1] == '0') {
            printLCD_Char(1, minimaleLengte + count, '0');
            ++count;
            ++i;
          }
          fase = 1;
        }
      }
    }
  }
}

void LCD_setLengteSpelerNaam(byte aLengteSpelerNaam) {
  lengteSpelerNaam = aLengteSpelerNaam;
  minimaleLengte = lengteSpelerNaam + 1;
  ruimteKaartenSpeler = 20 - minimaleLengte;
}

void LCD_addKaartSpeler(std::shared_ptr<Card> aKaart) {
  byte locatie = LCD_getAchtersteLocatieSpeler();
  spelerKaartenArray[locatie] = seperatorChar;
  spelerKaartenArray[locatie + 1] = aKaart->getLCD_Vorm() + 48;
  std::string temp = aKaart->getNaam();
  if (temp == "10") {
    spelerKaartenArray[locatie + 2] = '1';
    spelerKaartenArray[locatie + 3] = '0';
  } else {
    spelerKaartenArray[locatie + 2] = temp[0];
  }
}

void LCD_addKaartDealer(std::shared_ptr<Card> aKaart) {
  byte locatie = LCD_getAchtersteLocatieDealer();
  dealerKaartenArray[locatie] = seperatorChar;
  dealerKaartenArray[locatie + 1] = aKaart->getLCD_Vorm() + 48;
  std::string temp = aKaart->getNaam();
  if (temp == "10") {
    dealerKaartenArray[locatie + 2] = '1';
    dealerKaartenArray[locatie + 3] = '0';
  } else {
    dealerKaartenArray[locatie + 2] = temp[0];
  }
}

byte LCD_getAchtersteLocatieDealer() {
  byte temp;
  for (byte i = 0; i < 50; i++) {
    temp = dealerKaartenArray[i];
    if (temp == '\0') {
      return i;
    }
  }
  return 0;
}

byte LCD_getAchtersteLocatieSpeler() {
  byte temp;
  for (byte i = 0; i < 50; i++) {
    temp = spelerKaartenArray[i];
    if (temp == '\0') {
      return i;
    }
  }
  return 0;
}

void LCD_clearSpeler() {
  for (int i = 0; i < sizeof(spelerKaartenArray); ++i) {
    spelerKaartenArray[i] = '\0';
  }
}

void LCD_clearDealer() {
  for (int i = 0; i < sizeof(dealerKaartenArray); ++i) {
    dealerKaartenArray[i] = '\0';
  }
}

void LCD_printGewonnen() { printLCD_String(2, 0, "---|Gewonnen :D|----"); }

void LCD_printVerloren() { printLCD_String(2, 0, "---|Verloren :(|----"); }

void LCD_printGelijkspel() { printLCD_String(2, 0, "--|Gelijkspel :/|---"); }

void LCD_checkOfScrollNodigIs() {
  if (LCD_getAchtersteLocatieDealer() >= 20) {
    scrollDealer = true;
  } else {
    scrollDealer = false;
  }
  if (LCD_getAchtersteLocatieSpeler() > ruimteKaartenSpeler) {
    scrollSpeler = true;
  } else {
    scrollSpeler = false;
  }
}

void LCD_resetRow(byte amount, byte row, byte startColumn,
                  char replacementChar) {
  for (int i = 0; i < amount; i++) {
    printLCD_Char(row, startColumn + i, replacementChar);
  }
}