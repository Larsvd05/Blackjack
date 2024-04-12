cmake_minimum_required(VERSION 3.27)
project(Blackjack)

set(CMAKE_CXX_STANDARD 20)

add_executable(Blackjack main.cpp
        Card.h
        Card.cpp
        Player.h
        Player.cpp
        Game.h
        Game.cpp
        Dealer.h
        Dealer.cpp
)
