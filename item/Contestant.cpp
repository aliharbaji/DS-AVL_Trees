//
// Created by omar_ on 16/02/2024.
//

#include "Contestant.h"


Contestant::Contestant(int contestantID, weak_ptr<Country> country, Sport sport, int strength):
Item(contestantID),
myCountry(country),
sport(sport),
strength(strength),
numOfTeams(0){}

int Contestant::getNumOfActiveTeams() const {
    return numOfTeams;
}


Sport Contestant::getSport() const {
    return sport;
}

bool Contestant:: isAvailable() const{
    return numOfTeams <= MAX_TEAMS;
    // probably the right approach
    // TODO: Check this while testing
    return !(numOfTeams >= MAX_TEAMS || numOfTeams >= myCountry.lock()->getMedals());
}

bool Contestant::isActiveInTeam(int teamID) const{
    for (int i = 0; i < numOfTeams; i++) {
        if (myTeams[i] == teamID) {
            return true;
        }
    }
    return false;
}

//returns false in case adding contestant to the team is illegal.
bool Contestant::addTeam(int teamID) {
    if (!isAvailable()) return false;
    myTeams[numOfTeams] = teamID;
    numOfTeams++;
    return true;
}

int Contestant::getCountryID() const {
    return myCountry.lock()->getID();
}

bool Contestant::removeTeam(int teamID) {
    if (!isActiveInTeam(teamID)) return false;

    for (int i = 0; i < numOfTeams; i++) {
        if (myTeams[i] == teamID) {
            myTeams[i] = myTeams[numOfTeams - 1];
            numOfTeams--;
            return true;
        }
    }
    return false;
}

void Contestant::updateStrength(int change) {
    strength = (strength + change > 0) ? strength + change : 0;
}

int Contestant::getStrength() const {
    return strength;
}

weak_ptr<Country> Contestant::getCountry() const {
    return myCountry;
}

//weak_ptr<Team> Contestant::getTeam(int i) const {
//    if(i < 0 || i >= numOfTeams) {
//        return weak_ptr<Team>(); // returns an empty weak_ptr which is equivalent to nullptr
//    }
//    return myTeams[i];
//}

int Contestant::getTeamID(int i) const {
    if(i < 0 || i >= numOfTeams) {
        return -1; // returns an empty weak_ptr which is equivalent to nullptr
    }
    return myTeams[i];
}