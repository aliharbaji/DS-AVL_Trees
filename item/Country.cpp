//
// Created by omar_ on 16/02/2024.
//

#include "Country.h"

Country::Country(int countryID, int medals) : Item(countryID), numberOfContestants(0), numberOfTeams(0), strength(0), medals(medals){}



int Country::getMedals() const {
    return medals;
}

int Country::getStrength() const {
    return strength;
}

int Country::getNumberOfContestants() const {
    return numberOfContestants;
}

int Country::getNumberOfTeams() const {
    return numberOfTeams;
}

void Country::addTeam(){
    numberOfTeams++;
}
void Country::addContestant(){
    numberOfContestants++;
}


//void addContestant(shared_ptr<Contestant>& contestant){
////    contestants.insert(contestant->getID());
////    numberOfContestants++;
////    strength += contestant->getStrength();
////    myContestants->insert(contestant);
//
//}