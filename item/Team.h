//
// Created by omar_ on 16/02/2024.
//

#ifndef AVLTREES_TEAM_H
#define AVLTREES_TEAM_H

#include "../Scripts/wet1util.h"
#include "item.h"
#include "../tree.h"

class Contestant;
class Country;

class Team : public Item {
    int teamID;
    Sport sport;
    int numberOfContestants;
    int strength;
    Tree<Contestant> allIDs;
    //Stree<Contestant> allStrengths;
//    STree<Contestant> lowerContestants;
//    STree<Contestant> middleContestants;
//    STree<Contestant> upperContestants;

    shared_ptr<Country> myCountry;

public:
    Team(int teamID, int countryID, Sport sport);
    int getStrength() const;
    int getNumberOfContestants() const;

    void addContestant();
};


#endif //AVLTREES_TEAM_H