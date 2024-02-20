//
// Created by omar_ on 16/02/2024.
//

#include "Contestant.h"

Contestant::Contestant(int contestantID, shared_ptr<Country>& country, Sport sport, int strength):
Item(contestantID),
myCountry(country),
sport(sport),
strength(strength),
numOfTeams(0){}

int Contestant::getNumOfActiveTeams() const {
    return numOfTeams;
}

void Contestant::removeFromTeams() {
    for (int i = 0; i < numOfTeams; i++) {
        myTeams[i]->removeContestant();
    }
}

void Contestant::removeFromCountry() {
    myCountry->removeContestant();
}

Sport Contestant::getSport() const {
    return sport;
}

bool Contestant::isActiveInTeam(int teamID) {
    for (int i = 0; i < numOfTeams; i++) {
        if (myTeams[i]->getID() == teamID) {
            return true;
        }
    }
    return false;
}

void Contestant::addTeam(shared_ptr<Team> &team) {
    myTeams[numOfTeams] = team;
    numOfTeams++;
}

int Contestant::getCountryID() const {
    return myCountry->getID();
}

void Contestant::removeTeam(int teamID) {
    for (int i = 0; i < numOfTeams; i++) {
        if (myTeams[i]->getID() == teamID) {
            myTeams[i] = myTeams[numOfTeams - 1];
            numOfTeams--;
            return;
        }
    }
}

//Contestant::Contestant(int contestantID, int country, Sport sport, int strength):
//Item(contestantID),
//country(country),
//sport(sport),
//strength(strength),
//numOfTeams(0){}

//Contestant::Contestant(int contestantID, int country,
//                       Sport sport, int strength): Item(contestantID),
//                                                   sport(sport), strength(strength), country(country),
//                                                   activeTeams(0){}
