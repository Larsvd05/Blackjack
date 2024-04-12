//
// Created by lars on 19/01/24.
//

#ifndef BLACKJACK_DEALER_H
#define BLACKJACK_DEALER_H

#include "Card.h"
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

class Dealer {
public:
  Dealer();
  virtual ~Dealer() = default;

  const std::string &getNaam() const;
  void setNaam(const std::string &naam);

  void addKaart(std::shared_ptr<Card> aKaart, bool printKaart = false);
  void resetKaarten();
  uint16_t getWaardeKaarten();
  void setWaardeKaart(std::string aNaam, uint16_t aWaarde);
  bool checkForAce();

  uint32_t getInzet() const;
  void setInzet(uint32_t inzet);

  void printKaarten();

  std::string toString();

private:
  std::vector<std::shared_ptr<Card>> kaarten; // De kaarten van de dealer.
};

#endif // BLACKJACK_DEALER_H
