//
// Created by omar_ on 16/02/2024.
//

#ifndef AVLTREES_TEAM_H
#define AVLTREES_TEAM_H

#include "../Scripts/wet1util.h"
#include "item.h"
#include "../tree.h"
#include "Country.h"
class Contestant;
class Country;

class Team : public Item {
    int teamID;
    Sport sport;
    int numberOfContestants;
    int strength;

    shared_ptr<Country> myCountry;

public:
    Team(int teamID, int countryID, Sport sport);
    Team(int teamID, shared_ptr<Country>& country, Sport sport);
    void removeTeamFromItsCountry();
    int getStrength() const;
    int getNumberOfContestants() const;

    void addContestant();
    void removeContestant();
    Sport getSport() const;
};


#endif //AVLTREES_TEAM_H