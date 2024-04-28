//
// Created by lars on 18/01/24.
//
#include "Game.h"
#include "Player.h"
#include <Arduino.h>
#include <chrono>
#include <cmath>
#include <memory>

Game::Game() {
  auto currentTime = std::chrono::high_resolution_clock::now();
  auto seed = std::chrono::duration_cast<std::chrono::milliseconds>(
                  currentTime.time_since_epoch())
                  .count();
  srand(
      seed); // Seed de random generator met de huidige tijd van milli secondes.
}

void Game::run() {
  vraagInput(0);
  while (!stopGame) {
    startGame();
    generateSpeelkaarten();
    resetGame();
  }
}

void Game::startGame() {
  clearLCD();
  printLCD_String(0, 0, "Dealer:");
  printLCD_String(1, 0, (spelers.front()->getNaam() + ":").c_str());
  printLCD_String(
      3, 0,
      ("Inzet: " + std::to_string(spelers.front()->getTotaleInzet()))
          .c_str()); // Convert de inzet van een int naar een std::string en
                     // daarna naar een String.
  vraagInput(1);
  if (!gameFinished) {
    clearLCD();
    printLCD_String(0, 0, "Dealer:");
    printLCD_String(1, 0, (spelers.front()->getNaam() + ":").c_str());
    printLCD_String(3, 0,
                    ("Inzet: " + std::to_string(spelers.front()->getInzet()))
                        .c_str()); // Convert de inzet van een int naar een
                                   // std::string en daarna naar een String.

    std::shared_ptr<Card> kaart;
    kaart = trekKaart();
    spelers.front()->addKaart(kaart, true);
    kaart = trekKaart();
    dealer->addKaart(kaart, true);
    kaart = trekKaart();
    spelers.front()->addKaart(kaart, true);
    if (spelers.front()->getWaardeKaarten() > 21 &&
        spelers.front()->checkForAce()) {
      spelers.front()->setWaardeKaart("A", 1);
    }
    if (dealer->getWaardeKaarten() > 21 && dealer->checkForAce()) {
      dealer->setWaardeKaart("A", 1);
    }
    //          TODO-TEST zorg dat ook bij de dealer de Ace tussen 1 en 11 kan
    //          switchen.
    if (spelers.front()->checkFor21()) {
      Serial.println(
          "[Game] - Je hebt gelijk 21 gegooid en hebt 2x je inzet gekregen!");
      gameFinished = true;
      spelers.front()->setTotaleInzet(spelers.front()->getTotaleInzet() +
                                      spelers.front()->getInzet() * 2);
      Serial.println(("[" + spelers.front()->getNaam() +
                      "] - Jouw totale inzetpot bestaat nu uit €" +
                      std::to_string(spelers.front()->getTotaleInzet()) + ".\n")
                         .c_str());
    } else {
      kaart = trekKaart();
      dealer->addKaart(kaart);
          kaart = trekKaart();
    spelers.front()->addKaart(kaart, true);
        kaart = trekKaart();
    spelers.front()->addKaart(kaart, true);
        kaart = trekKaart();
    spelers.front()->addKaart(kaart, true);
        kaart = trekKaart();
    spelers.front()->addKaart(kaart, true);
        kaart = trekKaart();
    spelers.front()->addKaart(kaart, true);
        kaart = trekKaart();
    spelers.front()->addKaart(kaart, true);
        kaart = trekKaart();
    spelers.front()->addKaart(kaart, true);
        kaart = trekKaart();
    spelers.front()->addKaart(kaart, true);
      Serial.print(
          ("[" + spelers.front()->getNaam() + "] - Jouw kaarten zijn: ")
              .c_str());
      spelers.front()->printKaarten();
      Serial.println((" met een totale waarde van " +
                      std::to_string(spelers.front()->getWaardeKaarten()) + ".")
                         .c_str());

      while (!gameFinished && !stopGame) {
        vraagVoorInput();
      }
    }
  }
}

void Game::stop() {
  Serial.println(("[" + spelers.front()->getNaam() +
                  "] - Het spel is beëindigd en jouw totale inzet is nu " +
                  std::to_string(spelers.front()->getTotaleInzet()) + ".")
                     .c_str());
  stopGame = true;
}

void Game::addSpeler(std::string aNaam) {
  spelers.emplace_back(std::make_shared<Player>(Player(aNaam)));
}

void Game::addKaart(const uint8_t waarde, std::string naam, std::string vorm) {
  speelkaarten.emplace_back(std::make_shared<Card>(Card(waarde, naam, vorm)));
}

uint8_t Game::getRonde() const { return ronde; }

void Game::setRonde(uint8_t aRonde) { ronde = aRonde; }

void Game::setupGame() {
  generateSpeelkaarten();
  setSpeler();
  setDealer();
}

const std::vector<std::shared_ptr<Card>> &Game::getSpeelkaarten() const {
  return speelkaarten;
}

void Game::printKaarten() {
  for (auto kaart : speelkaarten) {
    Serial.println(kaart->toString().c_str());
  }
}

void Game::resetGame() {
  for (auto kaart : speelkaarten) {
    kaart->setAlOpgegooid(false);
  }
  for (auto speler : spelers) {
    speler->resetKaarten();
  }
  dealer->resetKaarten();
  gameFinished = false;
}

void Game::printSpelers() {
  for (auto speler : spelers) {
    Serial.println(speler->toString().c_str());
  }
}

std::shared_ptr<Card> Game::trekKaart() {
  if (getTotalPlayingCards() == 0) {
    Serial.println("[Game-Error] - Er zijn geen kaarten meer in de pot!");
    return nullptr; // Geen kaarten meer om te trekken
  }
  uint16_t randomNummer;
  randomNummer = rand() % getTotalPlayingCards();
  std::shared_ptr<Card> gekozenKaart;
  gekozenKaart = speelkaarten.at(randomNummer);

  while (gekozenKaart->isAlOpgegooid()) { // Ga door tot je een kaart vindt die
    // nog niet opgegooid is.
    randomNummer = rand() % getTotalPlayingCards();
    gekozenKaart = speelkaarten[randomNummer];
  }

  return gekozenKaart;
}

uint16_t Game::getTotalPlayingCards() {
  uint16_t totalPlayingCards = 0;
  for (auto kaart : speelkaarten) {
    if (!kaart->isAlOpgegooid()) {
      ++totalPlayingCards;
    }
  }
  return totalPlayingCards;
}

void Game::setDealer() {
  Dealer dealer1;
  dealer = std::make_shared<Dealer>(dealer1);
}

void Game::generateSpeelkaarten() {
  std::string vorm = "♥";
  std::string naam = "J";
  uint8_t waarde = 1;
  uint8_t iterator = 0;
  for (int i = 0; i < 52; i++) {
    uint8_t colorNumber = std::floor((i + 1) / 14);
    switch (colorNumber) {
    case 0:
      vorm = "♥";
      if (waarde == 11) {
        naam = "A";
        addKaart(waarde, naam, vorm);
        waarde = 1;
      } else if (waarde <= 9) {
        ++waarde;
        naam = std::to_string(waarde);
        addKaart(waarde, naam, vorm);
      } else if (waarde == 10) {
        switch (iterator) {
        case 0:
          naam = "J";
          ++iterator;
          addKaart(waarde, naam, vorm);
          break;
        case 1:
          naam = "Q";
          ++iterator;
          addKaart(waarde, naam, vorm);
          break;
        case 2:
          naam = "K";
          iterator = 0;
          addKaart(waarde, naam, vorm);
          ++waarde;
          break;
        }
      }
      break;
    case 1:
      vorm = "♦";
      if (waarde == 11) {
        naam = "A";
        addKaart(waarde, naam, vorm);
        waarde = 1;
      } else if (waarde <= 9) {
        ++waarde;
        naam = std::to_string(waarde);
        addKaart(waarde, naam, vorm);
      } else if (waarde == 10) {
        switch (iterator) {
        case 0:
          naam = "J";
          ++iterator;
          addKaart(waarde, naam, vorm);
          break;
        case 1:
          naam = "Q";
          ++iterator;
          addKaart(waarde, naam, vorm);
          break;
        case 2:
          naam = "K";
          iterator = 0;
          addKaart(waarde, naam, vorm);
          ++waarde;
          break;
        }
      }
      break;
    case 2:
      vorm = "♠";
      if (waarde == 11) {
        naam = "A";
        addKaart(waarde, naam, vorm);
        waarde = 1;
      } else if (waarde <= 9) {
        ++waarde;
        naam = std::to_string(waarde);
        addKaart(waarde, naam, vorm);
      } else if (waarde == 10) {
        switch (iterator) {
        case 0:
          naam = "J";
          ++iterator;
          addKaart(waarde, naam, vorm);
          break;
        case 1:
          naam = "Q";
          ++iterator;
          addKaart(waarde, naam, vorm);
          break;
        case 2:
          naam = "K";
          iterator = 0;
          addKaart(waarde, naam, vorm);
          ++waarde;
          break;
        }
      }
      break;
    case 3:
      vorm = "♣";
      if (waarde == 11) {
        naam = "A";
        addKaart(waarde, naam, vorm);
        waarde = 1;
      } else if (waarde <= 9) {
        ++waarde;
        naam = std::to_string(waarde);
        addKaart(waarde, naam, vorm);
      } else if (waarde == 10) {
        switch (iterator) {
        case 0:
          naam = "J";
          ++iterator;
          addKaart(waarde, naam, vorm);
          break;
        case 1:
          naam = "Q";
          ++iterator;
          addKaart(waarde, naam, vorm);
          break;
        case 2:
          naam = "K";
          iterator = 0;
          addKaart(waarde, naam, vorm);
          ++waarde;
          break;
        }
      }
      break;
    default:

      break;
    }
  }
}

void Game::setSpeler() {
  std::string naamSpeler = "Lars";
  //    Serial.println( << "[Input] - Vul hier uw speelnaam in: ";
  //    getline(std::cin, naamSpeler);
  addSpeler(naamSpeler);
  Serial.println(("[Game] - U bent succesvol in het spel gezet met de naam " +
                  naamSpeler + "!")
                     .c_str());
}

void Game::processInput(const std::string userInput) {
  std::string input = userInput;
  int length = input.length();
  if (std::isspace(input[length - 1])) {
    input.pop_back(); // Als er een enter of een andere whitespace gebruikt is
                      // in de input, verwijder deze.
  }

  for (char &c : input) {
    c = std::tolower(c);
  }
  if (input == "hit" || input == "h") {
    std::shared_ptr<Card> kaart = trekKaart();
    spelers.front()->addKaart(kaart, true);
    uint16_t waardeKaartenSpeler = spelers.front()->getWaardeKaarten();
    if (waardeKaartenSpeler > 21 && spelers.front()->checkForAce()) {
      spelers.front()->setWaardeKaart("A", 1);
      Serial.print(
          ("[" + spelers.front()->getNaam() + "] - Jouw kaarten zijn nu:")
              .c_str());
      spelers.front()->printKaarten();
      Serial.println((" met een totale waarde van " +
                      std::to_string(spelers.front()->getWaardeKaarten()) +
                      ".\n")
                         .c_str());
    } else if (waardeKaartenSpeler > 21) {
      Serial.println(
          ("[" + spelers.front()->getNaam() +
           "] - Je hebt helaas verloren met een totale waarde van " +
           std::to_string(waardeKaartenSpeler) +
           " en jouw inzet wordt nu gebruikt om de slaven in dit casino te "
           "betalen, want anders hebben we geen elektriciteit meer.")
              .c_str());
      gameFinished = true;
      Serial.println(("[" + spelers.front()->getNaam() +
                      "] - Jouw totale inzetpot bestaat nu uit €" +
                      std::to_string(spelers.front()->getTotaleInzet()) + ".\n")
                         .c_str());
    } else {
      Serial.print(
          ("[" + spelers.front()->getNaam() + "] - Jouw kaarten zijn nu:")
              .c_str());
      spelers.front()->printKaarten();
      Serial.println((" met een totale waarde van " +
                      std::to_string(spelers.front()->getWaardeKaarten()) +
                      ".\n")
                         .c_str());
    }
  } else if (input == "stand" || input == "s") {
    processDealerEinde();
  } else if (input == "double" || input == "d") {
    if (spelers.front()->getTotaleInzet() > spelers.front()->getInzet()) {
      spelers.front()->setTotaleInzet(spelers.front()->getTotaleInzet() -
                                      spelers.front()->getInzet());
      spelers.front()->setInzet(spelers.front()->getInzet() * 2);
      spelers.front()->addKaart(trekKaart(), true);
      if (spelers.front()->getWaardeKaarten() > 21 &&
          spelers.front()->checkForAce()) {
        spelers.front()->setWaardeKaart("A", 1);
      } else if (spelers.front()->getWaardeKaarten() > 21) {
        Serial.println(
            ("[" + spelers.front()->getNaam() +
             "] - Je hebt helaas verloren met een totale waarde van " +
             std::to_string(spelers.front()->getWaardeKaarten()) +
             " en jouw inzet wordt nu gebruikt om de slaven in dit casino te "
             "betalen, want anders hebben we geen elektriciteit meer.\n")
                .c_str());
        gameFinished = true;
        Serial.println(("[" + spelers.front()->getNaam() +
                        "] - Jouw totale inzetpot bestaat nu uit €" +
                        std::to_string(spelers.front()->getTotaleInzet()) +
                        ".\n")
                           .c_str());
        return;
      }
      Serial.println(
          ("[" + spelers.front()->getNaam() + "] - Jouw kaarten zijn nu:")
              .c_str());
      spelers.front()->printKaarten();
      Serial.println((" met een totale waarde van " +
                      std::to_string(spelers.front()->getWaardeKaarten()) +
                      ".\n")
                         .c_str());
      processDealerEinde();
    } else {
      Serial.println("[Input] - Dit is een ongeldige invoer, want je hebt niet "
                     "genoeg totale inzet om dit te proberen. Wees alsnog maar "
                     "blij, want je hebt nooit geen geld, kankerboef!");
    }
  } else if (input == "split" || input == "spl") {
  } else if (input == "help" || input == "hel") {
    Serial.println(
        "[Help] - Je hebt nu de keuze om te Hitten ('H'), Standen ('S'), "
        "Verdubbelen ('D'), Splitten ('SPL') of Stoppen ('STP')\n"
        "[Hit] - Speler pakt een nieuwe kaart en kan hierna opnieuw kiezen wat "
        "hij gaat doen.\n"
        "[Stand] - Speler wil geen nieuwe kaarten meer en houdt het bij deze "
        "kaarten. Als deze optie gekozen is, maakt de dealer de ronde af.\n"
        "[Double] - Speler verdubbelt zijn inzet, pakt 1 kaart en hierna maakt "
        "de dealer de ronde af.\n"
        "[Split] - Geen idee hoe dit werkt tbh.\n"
        "[Stop] - Voer dit commando uit om per direct het spel te stoppen.\n");
  } else if (input == "stop" || input == "stp") {
    stop();
  } else if (input == "win" || input == "w") {
    spelers.front()->resetKaarten();
    spelers.front()->addKaart(std::make_shared<Card>(Card(10, "K", "♥", true)),
                              false);
    spelers.front()->addKaart(std::make_shared<Card>(Card(11, "A", "♥", true)),
                              false);
    processDealerEinde();
  } else {
    Serial.println("[Error] - Dit commando is niet bekend of verkeerd getypt, "
                   "kijk of je dit goed getypt hebt en probeer opnieuw.");
  }
}

void Game::vraagVoorInput() {
  String SerialInput;
  Serial.println("[Game] - Kies nu wat je wilt doen met deze kaarten, de keuze "
                 "bestaat uit: Hit 'H',  Stand 'S', Double 'D' of Split 'SPL'. "
                 "Type Help voor hulp.");
  while (true) {
    if (Serial.available() > 0) {
      SerialInput = Serial.readStringUntil('\n');
      std::string input =
          SerialInput
              .c_str(); // Convert de arduino input string naar een c-string.
      processInput(input);
      break;
    }
  }
}

uint16_t Game::processDealerEinde() {
  std::shared_ptr<Card> kaart;
  uint16_t waardeKaartenDealer;
  while (!gameFinished) {
    Serial.print("[Dealer] - De kaarten van de dealer zijn:");
    dealer->printKaarten();
    Serial.println(("met een waarde van " +
                    std::to_string(dealer->getWaardeKaarten()) + ".\n")
                       .c_str());
    waardeKaartenDealer = dealer->getWaardeKaarten();
    if (waardeKaartenDealer <= 16) {
      kaart = trekKaart();
      dealer->addKaart(kaart, true);
    } else if (waardeKaartenDealer >= 17 && waardeKaartenDealer <= 21) {
      if (waardeKaartenDealer > spelers.front()->getWaardeKaarten()) {
        Serial.print(
            "\n[Game] - De dealer heeft gewonnen met de volgende kaarten: ");
        dealer->printKaarten();
        Serial.println(("\n[Game] - Dit geeft een waarde van " +
                        std::to_string(dealer->getWaardeKaarten()) +
                        " in vergelijking met de waarde " +
                        std::to_string(spelers.front()->getWaardeKaarten()) +
                        " van de speler.")
                           .c_str());
        spelers.front()->setInzet(0);
        gameFinished = true;
      } else if (waardeKaartenDealer < spelers.front()->getWaardeKaarten()) {
        Serial.println(("\n[Game] - Dit geeft een waarde van " +
                        std::to_string(spelers.front()->getWaardeKaarten()) +
                        " in vergelijking met de waarde " +
                        std::to_string(dealer->getWaardeKaarten()) +
                        " van de dealer.")
                           .c_str());
        Serial.print("\n[Game] - De speler heeft dus gewonnen met de volgende "
                     "kaarten: ");
        spelers.front()->printKaarten();
        Serial.println("");
        spelers.front()->setTotaleInzet(spelers.front()->getTotaleInzet() +
                                        (spelers.front()->getInzet() * 2));
        gameFinished = true;
      } else {
        Serial.println("\n[Game] - Gelijkspel");
        spelers.front()->setTotaleInzet(spelers.front()->getTotaleInzet() +
                                        (spelers.front()->getInzet()));
        spelers.front()->setInzet(0);
        gameFinished = true;
      }
    } else if (waardeKaartenDealer > 21) {
      Serial.print("\n[Game] - De speler heeft gewonnen omdat de dealer over "
                   "de 21 is gegaan met de volgende kaarten:");
      dealer->printKaarten();
      Serial.println(("met een waarde van " +
                      std::to_string(dealer->getWaardeKaarten()) + ".")
                         .c_str());
      spelers.front()->setTotaleInzet(spelers.front()->getTotaleInzet() +
                                      (spelers.front()->getInzet() * 2));
      gameFinished = true;
    }
  }
  Serial.println(("[" + spelers.front()->getNaam() +
                  "] - Jouw totale inzetpot bestaat nu uit €" +
                  std::to_string(spelers.front()->getTotaleInzet()) + ".\n")
                     .c_str());
  return 0;
}

std::string Game::vraagInput(uint8_t promptNummer) {
  uint64_t inputInt;
  String SerialInput;

  Serial.println();
  switch (promptNummer) {
  case 0:
    Serial.println(+"[Input] - Vul alstublieft uw totale geldinzet hier in "
                    "(zonder spaties, punten of komma's): ");
    break;
  case 1:
    Serial.println(+"[Game] - Vul alstublieft uw inzet voor deze ronde hier "
                    "in (zonder spaties, punten of komma's): ");
    break;
  }

  while (true) {
    if (Serial.available() > 0) {
      SerialInput = Serial.readStringUntil('\n');
      std::string input =
          SerialInput
              .c_str(); // Convert de arduino input string naar een c-string.
      // input = "100";
      if (input == "stop" || input == "stp") {
        stop();
        return "0";
      } else {
        bool isValid = true;
        for (char c : input) {
          std::cout << c;
          if (!std::isdigit(c) && !std::isspace(c) && c != 10) {
            isValid = false;
            break;
          }
        }

        if (isValid) {
          bool geldigAantal = false;
          try {
            inputInt = std::stoull(input);
            switch (promptNummer) {
            case 0:
              spelers.front()->setTotaleInzet(inputInt);
              Serial.println(
                  ("[" + spelers.front()->getNaam() +
                   "] - Jouw totale inzet voor het spel is nu: €" +
                   std::to_string(spelers.front()->getTotaleInzet()) +
                   ", hopelijk heb je zin om te beginnen!\n")
                      .c_str());
              geldigAantal = true;
              break;
            case 1:
              if (spelers.front()->getTotaleInzet() >= inputInt) {
                spelers.front()->setInzet(inputInt);
                spelers.front()->setTotaleInzet(
                    spelers.front()->getTotaleInzet() - inputInt);
                Serial.println(
                    ("[" + spelers.front()->getNaam() +
                     "] - Jouw inzet voor deze ronde is nu: €" +
                     std::to_string(spelers.front()->getInzet()) +
                     " en jouw totale inzet is nog €" +
                     std::to_string(spelers.front()->getTotaleInzet()) +
                     ", succes!\n")
                        .c_str());
                geldigAantal = true;
              } else {
                Serial.println("[Input] Dit is een ongeldige invoer, want uw "
                               "totale inzet kan niet lager dan 0 worden.");
                geldigAantal = false;
              }
              break;
            }
          } catch (const std::exception &e) {
            std::cerr << "[Game] - Inputfout: " << e.what() << "\n";
          }
          if (geldigAantal) {
            return input;
          }
        } else {
          Serial.println("[Input] - Ongeldige invoer. Probeer het opnieuw.\n");
        }
      }
    }
  }
}

std::string SerialAskInput() {
  std::string buffer;
  bool exitLoop = false;
  while (!exitLoop)

    if (Serial.available()) {
      char incomingChar = Serial.read(); // Read a single character from serial
      if (incomingChar == '\n') {        // If newline character is received
        exitLoop = true;
      } else if (incomingChar != '\r') { // Ignore carriage return ('\r')
        buffer += incomingChar; // Append the character to the command buffer
      }
    }
  return buffer;
}