//
// Created by omar_ on 16/02/2024.
//

#ifndef AVLTREES_COUNTRY_H
#define AVLTREES_COUNTRY_H


#include "../tree.h"
#include "Item.h"
#include "Contestant.h"
#include "Team.h"

class Country : public Item {

    int numberOfContestants;
    int numberOfTeams;
    int strength;
    int medals;
// not sure if this is the right way to do it
//    shared_ptr<Tree<Contestant>> myContestants;
    shared_ptr<Tree<Country>> allCountries;
public:
    Country(int countryID, int medals);
    int getMedals() const;
    int getStrength() const;
    int getNumberOfContestants() const;
    int getNumberOfTeams() const;

    void addTeam();
    void addContestant();
//    friend class Tree<Country>;
};


#endif //AVLTREES_COUNTRY_H