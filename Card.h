//
// Created by lars on 18/01/24.
//

#ifndef BLACKJACK_CARD_H
#define BLACKJACK_CARD_H

#include <Arduino.h>
#include <cstdint>
#include <string>

class Card {
public:
  Card(uint8_t waarde, const std::string &naam, const std::string &vorm,
       bool alOpgegooid = false);

  uint8_t getWaarde() const;
  void setWaarde(uint8_t aWaarde);
  const std::string &getNaam() const;
  void setNaam(const std::string &aNaam);
  const std::string &getVorm() const;
  const byte getLCD_Vorm() const;
  void setVorm(const std::string &aVorm);
  bool isAlOpgegooid() const;
  void setAlOpgegooid(bool aAlOpgegooid);
  std::string toString();
  std::string toText();

private:
  uint8_t waarde;
  std::string naam;
  std::string vorm;
  bool alOpgegooid = false;
};

#endif // BLACKJACK_CARD_H
