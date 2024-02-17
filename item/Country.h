//
// Created by omar_ on 16/02/2024.
//

#ifndef AVLTREES_COUNTRY_H
#define AVLTREES_COUNTRY_H


#include "../tree.h"

class Country {
    int countryID;
    int numberOfContestants;
    int strength;
    int medals;
public:
    Country(int countryID, int medals);
    int getID() const;
    int getMedals() const;
    int getStrength() const;
    int getNumberOfContestants() const;
};


#endif //AVLTREES_COUNTRY_H