//
// Created by omar_ on 16/02/2024.
//

#include "Team.h"



//int Team::getMedals() const {
//    return medals;
//}

int Team::getStrength() const {
    return strength;
}

int Team::getNumberOfContestants() const {
    return size;
}

void Team::addContestant(){
    size++;
}

void Team::removeTeamFromItsCountry() {
    myCountry->removeTeam();
}

void Team::removeContestant() {
    size--;
}

Sport Team::getSport() const {
    return sport;
}

int Team::getCountryID() const {
    return myCountry->getID();
}



