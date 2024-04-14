//
// Created by Lars van Duijnhoven on 18/01/24.
// Last update on 12/04/2024
//
#include <Arduino.h>
#include <iostream>

#include "Game.h"

int main() {
  Game game;
  game.setupGame();
  game.run();
  return 0;
}

// DEBUG MAIN -----------------
String checkSerialInput() {
  String commandBuffer;
  bool exitLoop = false;
  while (!exitLoop)

    if (Serial.available()) {
      char incomingChar = Serial.read(); // Read a single character from serial
      if (incomingChar == '\n') {        // If newline character is received
        if (commandBuffer == "ON") {
          Serial.println("LED is turned ON");
        } else if (commandBuffer == "OFF") {
          Serial.println("LED is turned OFF");
        } else if (commandBuffer == "") {
          Serial.println("Enter has been pressed");
        } else {
          Serial.println("Invalid command");
        }
        exitLoop = true;
      } else if (incomingChar != '\r') { 
        commandBuffer +=
            incomingChar;
      }
    }
  return commandBuffer;
}

void setup() {
  Serial.begin(115200);
  main();
}

void loop() {}
