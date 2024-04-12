//
// Created by lars on 18/01/24.
//

#ifndef BLACKJACK_PLAYER_H
#define BLACKJACK_PLAYER_H

#include "Card.h"
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

class Player {
public:
  Player(std::string &naam, uint32_t inzet = 0);
  virtual ~Player() = default;

  const std::string &getNaam() const;
  void setNaam(std::string &naam);

  void addKaart(std::shared_ptr<Card> aKaart, bool print);
  void
  setWaardeKaart(std::string aNaam,
                 uint16_t); // Deze functie wordt vooral gebruikt om de ace/ aas
                            // te veranderen van 11 naar 1, andere
                            // functionaliteiten hiervan kan ik niet garanderen.
  void resetKaarten();
  bool checkFor21();
  bool checkForAce();
  uint16_t getWaardeKaarten();

  uint32_t getInzet() const;
  void setInzet(uint32_t inzet);

  void printKaarten();

  std::string toString();

private:
  std::vector<std::shared_ptr<Card>> kaarten; // De kaarten van de speler.
  uint32_t inzet = 0; // Inzet van de speler voor 1 potje in euro's.
  uint64_t totaleInzet =
      0; // Totale inzet van de speler voor het gehele spel in euro's.
public:
  uint64_t getTotaleInzet() const;

  void setTotaleInzet(uint64_t totaleInzet);

private:
  std::string naam; // Naam van de speler.
};

#endif // BLACKJACK_PLAYER_H
