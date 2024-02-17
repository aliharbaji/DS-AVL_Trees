//
// Created by omar_ on 16/02/2024.
//

#ifndef AVLTREES_TEAM_H
#define AVLTREES_TEAM_H
#include "../tree.h"

class Team {
    int teamID;
    int numberOfContestants;
    int strength;
    int medals;
public:
    Team(int teamID);
    int getID() const;
    int getMedals() const;
    int getStrength() const;
    int getNumberOfContestants() const;
};


#endif //AVLTREES_TEAM_H