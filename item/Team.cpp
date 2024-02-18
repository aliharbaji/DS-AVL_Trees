//
// Created by omar_ on 16/02/2024.
//

#include "Team.h"

Team::Team(int teamID, int countryID, Sport sport) : Item(teamID), sport(sport), strength(Zero),
numberOfContestants(Zero) {
    this->countries[0] = countryID;
}


//int Team::getMedals() const {
//    return medals;
//}

int Team::getStrength() const {
    return strength;
}

int Team::getNumberOfContestants() const {
    return numberOfContestants;
}




