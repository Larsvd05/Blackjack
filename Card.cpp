#include "Card.h"
#include <string>

//
// Created by lars on 18/01/24.
//
Card::Card(unsigned char waarde, const std::string &naam,
           const std::string &vorm, bool alOpgegooid)
    : waarde(waarde), naam(naam), vorm(vorm), alOpgegooid(alOpgegooid) {}

uint8_t Card::getWaarde() const { return waarde; }

void Card::setWaarde(uint8_t aWaarde) { waarde = aWaarde; }

const std::string &Card::getNaam() const { return naam; }

void Card::setNaam(const std::string &aNaam) { naam = aNaam; }

const std::string &Card::getVorm() const { return vorm; }

const byte Card::getLCD_Vorm() const {
  if (Card::getVorm() == "♥") {
    return 0;
  } else if (Card::getVorm() == "♦") {
    return 1;
  } else if (Card::getVorm() == "♠") {
    return 2;
  } else if (Card::getVorm() == "♣") {
    return 3;
  }
  return 0;
}

void Card::setVorm(const std::string &aVorm) { vorm = aVorm; }

bool Card::isAlOpgegooid() const { return alOpgegooid; }

void Card::setAlOpgegooid(bool aAlOpgegooid) { alOpgegooid = aAlOpgegooid; }

std::string Card::toString() {
  return "Een " + vorm + " " + naam + " met waarde " + std::to_string(waarde) +
         ".";
}

std::string Card::toText() { return vorm + naam; }
