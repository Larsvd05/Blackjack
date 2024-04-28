//
// Created by Lars van Duijnhoven on 18/01/24.
// Last update on 12/04/2024
//
#include <Arduino.h>
#include <Wire.h>
#include <iostream>

#include "Game.h"
#include "LCD_screen.h"

/* Pinnen voor de LCD display: GND -> GND, VCC -> VIN, SDA -> D21 en SCL ->
 * D22.*/

int main() {
  Game game;
  game.setupGame();
  game.run();
  return 0;
}

void setup() {
  Serial.begin(115200);
  Init_LCD_scherm();
  clearLCD();
  main();
}

void loop() {}
