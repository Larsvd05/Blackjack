//
// Created by lars on 15/04/24.
//

#ifndef LCD_SCREEN_H
#define LCD_SCREEN_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;

void Init_LCD_scherm();
void Init_speciale_chars();
void clearLCD();
void printLCD_String(byte row, byte column, String string);
void printLCD_SpecialChar(byte row, byte column, byte specialChar);
// void printLCD_Integer(byte row, byte column, int64_t integer);

#endif