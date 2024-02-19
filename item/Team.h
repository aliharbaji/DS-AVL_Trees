//
// Created by omar_ on 16/02/2024.
//

#ifndef AVLTREES_TEAM_H
#define AVLTREES_TEAM_H
#include "../tree.h"
#include "../Scripts/wet1util.h"
#include "Item.h"
#include "Contestant.h"

class Team : public Item {
    int teamID;
    Sport sport;
    int numberOfContestants;
    int strength;
//    STree<Contestant> lowerContestants;
//    STree<Contestant> middleContestants;
//    STree<Contestant> upperContestants;

    int countries[];

public:
    Team(int teamID, int countryID, Sport sport);
    int getStrength() const;
    int getNumberOfContestants() const;

    void addContestant();
};


#endif //AVLTREES_TEAM_H