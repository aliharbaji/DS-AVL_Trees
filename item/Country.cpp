//
// Created by omar_ on 16/02/2024.
//

#include "Country.h"

Country::Country(int countryID, int medals) : countryID(countryID), numberOfContestants(Zero), strength(Zero), medals(medals){}

int Country::getID() const {
    return countryID;
}

int Country::getMedals() const {
    return medals;
}

int Country::getStrength() const {
    return strength;
}

int Country::getNumberOfContestants() const {
    return numberOfContestants;
}
