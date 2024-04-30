//
// Created by lars on 15/04/24.
//

#ifndef LCD_SCREEN_H
#define LCD_SCREEN_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <memory>
#include "Card.h"

extern LiquidCrystal_I2C lcd;

void Init_LCD_scherm();
void Init_speciale_chars();
void clearLCD();
void printLCD_String(byte row, byte column, String string);
void printLCD_Char(byte row, byte column, char aChar);
void printLCD_SpecialChar(byte row, byte column, byte specialChar);
void LCD_printKaarten();
void LCD_setLengteSpelerNaam(uint8_t lengteSpelerNaam);
void LCD_addKaartSpeler(std::shared_ptr<Card> aKaart);
void LCD_addKaartDealer(std::shared_ptr<Card> aKaart);
byte LCD_getAchtersteLocatieDealer();
byte LCD_getAchtersteLocatieSpeler();
void LCD_clearSpeler();
void LCD_clearDealer();

#endif