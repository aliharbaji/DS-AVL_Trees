//
// Created by omar_ on 16/02/2024.
//

#include "Team.h"

Team::Team(int teamID) : teamID(teamID), numberOfContestants(Zero), strength(Zero), medals(Zero){}

int Team::getID() const {
    return teamID;
}

int Team::getMedals() const {
    return medals;
}

int Team::getStrength() const {
    return strength;
}

int Team::getNumberOfContestants() const {
    return numberOfContestants;
}


