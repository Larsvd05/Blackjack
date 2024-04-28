#include "Player.h"
#include "LCD_screen.h"
#include <Arduino.h>
#include <string>

//
// Created by lars on 18/01/24.
//
Player::Player(std::string &naam, uint32_t inzet) : inzet(inzet), naam(naam) {}

uint32_t Player::getInzet() const { return inzet; }

void Player::setInzet(uint32_t aInzet) { inzet = aInzet; }

const std::string &Player::getNaam() const { return naam; }

void Player::setNaam(std::string &aNaam) { naam = aNaam; }

void Player::printKaarten() {
  byte locatie = naam.length() + 1;
  for (auto kaart : kaarten) {
    Serial.print((" " + kaart->toText() + " ").c_str());
    ++locatie;
    printLCD_SpecialChar(1, locatie, kaart->getLCD_Vorm());
    ++locatie;
    printLCD_String(1, locatie, kaart->getNaam().c_str());
    ++locatie;
  }
}

bool Player::checkFor21() {
  uint16_t totaleWaardeKaarten = 0;
  bool result = false;

  for (auto kaart : kaarten) {
    totaleWaardeKaarten = totaleWaardeKaarten + kaart->getWaarde();
  }
  if (totaleWaardeKaarten == 21) {
    result = true;
  }
  return result;
}

std::string Player::toString() {
  return "Een speler met naam " + naam + " en een huidige inzet van " +
         std::to_string(inzet) + ".";
}

void Player::addKaart(std::shared_ptr<Card> aKaart, bool print) {
  kaarten.emplace_back(aKaart);
  if (print) {
    Serial.println(
        ("[" + naam + "] - Je hebt een " + aKaart->toText() + " getrokken!\n")
            .c_str());
  }
}

void Player::resetKaarten() { kaarten.clear(); }

uint16_t Player::getWaardeKaarten() {
  uint16_t totaleWaardeKaarten = 0;
  for (auto kaart : kaarten) {
    totaleWaardeKaarten = totaleWaardeKaarten + kaart->getWaarde();
  }
  return totaleWaardeKaarten;
}

void Player::setWaardeKaart(std::string aNaam, uint16_t aWaarde) {
  for (auto kaart : kaarten) {
    // Set ace/ aas
    if (kaart->getNaam() == aNaam && kaart->getWaarde() == 11) {
      kaart->setWaarde(aWaarde);
      return;
    }
  }
}

bool Player::checkForAce() {
  for (auto kaart : kaarten) {
    if (kaart->getNaam() == "A" && kaart->getWaarde() == 11) {
      return true;
    }
  }
  return false;
}

uint64_t Player::getTotaleInzet() const { return totaleInzet; }

void Player::setTotaleInzet(uint64_t totaleInzet) {
  Player::totaleInzet = totaleInzet;
}
