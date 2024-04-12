//
// Created by Lars van Duijnhoven on 18/01/24.
// Last update on 20/03/2024
//
#include "Game.h"
#include <Arduino.h>
#include <iostream>

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
      } else if (incomingChar != '\r') { // Ignore carriage return ('\r')
        commandBuffer +=
            incomingChar; // Append the character to the command buffer
      }
    }
  return commandBuffer;
}

void setup() {
  Serial.begin(115200);
  main();
}

void loop() {}
