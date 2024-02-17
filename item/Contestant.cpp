//
// Created by omar_ on 16/02/2024.
//

#include "Contestant.h"

Contestant::Contestant(int contestantID, int countryID, Sport sport, int strength): Item(contestantID), sport(sport), strength(strength) {
    this->countries[0] = countryID;
}

