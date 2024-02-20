//
// Created by omar_ on 16/02/2024.
//

#include "Team.h"

Team::Team(int teamID, int countryID, Sport sport) : Item(teamID), sport(sport), strength(0),
numberOfContestants(0) {

}


//int Team::getMedals() const {
//    return medals;
//}

int Team::getStrength() const {
    return strength;
}

int Team::getNumberOfContestants() const {
    return numberOfContestants;
}

void Team::addContestant(){
    numberOfContestants++;
}

Team::Team(int teamID, shared_ptr<Country>& country, Sport sport) : Item(teamID), sport(sport), strength(0),
numberOfContestants(0), myCountry(country)
{

}

void Team::removeTeamFromItsCountry() {
    myCountry->removeTeam();
}

void Team::removeContestant() {
    numberOfContestants--;
}

Sport Team::getSport() const {
    return sport;
}

int Team::getCountryID() const {
    return myCountry->getID();
}



