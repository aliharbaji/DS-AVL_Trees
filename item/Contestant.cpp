//
// Created by omar_ on 16/02/2024.
//

#include "Contestant.h"

int Contestant::getID() const {
    return contestantID;
}

Contestant::Contestant(int contestantID, int countryID, Sport sport, int strength): contestantID(contestantID), sport(sport), strength(strength) {
    this->countries[0] = countryID;
}

