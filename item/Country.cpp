//
// Created by omar_ on 16/02/2024.
//

#include "Country.h"

Country::Country(int countryID, int medals) : Item(countryID), numberOfContestants(Zero), numberOfTeams(Zero), strength(Zero), medals(medals){}



int Country::getMedals() const {
    return medals;
}

int Country::getStrength() const {
    return strength;
}

int Country::getNumberOfContestants() const {
    return numberOfContestants;
}

int Country::getNumberOfTeams() const {
    return numberOfTeams;
}
