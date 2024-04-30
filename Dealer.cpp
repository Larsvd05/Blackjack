//
// Created by lars on 19/01/24.
//
#include "Dealer.h"
#include "LCD_screen.h"
#include <string>

Dealer::Dealer() {}

void Dealer::printKaarten() {
  // byte locatie = 7; // Want "Dealer:" is altijd dezelfde lengte.
  for (auto kaart : kaarten) {
    Serial.print((" " + kaart->toText() + " ").c_str());
    // ++locatie;
    // printLCD_SpecialChar(1, locatie, kaart->getLCD_Vorm());
    // ++locatie;
    // printLCD_String(1, locatie, kaart->getNaam().c_str());
    // ++locatie;
    // ++locatie;
  }
}

void Dealer::addKaart(std::shared_ptr<Card> aKaart, bool printKaart) {
  kaarten.emplace_back(aKaart);
  if (printKaart) {
        Serial.println(
        ("[Dealer] - De dealer heeft een " + aKaart->toText() +
                     " getrokken!\n").c_str());
  } else {
            Serial.println(
        ("[Dealer] - De dealer heeft een geheime kaart getrokken!\n"));
  }
  // TODO dit moet verwerkt worden zodat de tweede kaart van de dealer geheim blijft, want nu is hij niet geheim 
  LCD_addKaartDealer(aKaart);
  LCD_printKaarten();
}

void Dealer::resetKaarten() { kaarten.clear(); }

uint16_t Dealer::getWaardeKaarten() {
  uint16_t totaleWaardeKaarten = 0;
  for (auto kaart : kaarten) {
    totaleWaardeKaarten = totaleWaardeKaarten + kaart->getWaarde();
  }
  return totaleWaardeKaarten;
}

void Dealer::setWaardeKaart(std::string aNaam, uint16_t aWaarde) {
  for (auto kaart : kaarten) {
    // Set ace/ aas
    if (kaart->getNaam() == aNaam && kaart->getWaarde() == 11) {
      kaart->setWaarde(aWaarde);
      return;
    }
  }
}

bool Dealer::checkForAce() {
  for (auto kaart : kaarten) {
    if (kaart->getNaam() == "A" && kaart->getWaarde() == 11) {
      return true;
    }
  }
  return false;
}