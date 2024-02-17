//
// Created by omar_ on 16/02/2024.
//

#ifndef AVLTREES_COUNTRY_H
#define AVLTREES_COUNTRY_H


#include "../tree.h"
#include "Item.h"

class Country : public Item {

    int numberOfContestants;
    int numberOfTeams;
    int strength;
    int medals;
public:
    Country(int countryID, int medals);
    int getMedals() const;
    int getStrength() const;
    int getNumberOfContestants() const;
    int getNumberOfTeams() const;
};


#endif //AVLTREES_COUNTRY_H