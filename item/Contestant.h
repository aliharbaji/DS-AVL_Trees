//
// Created by omar_ on 16/02/2024.
//

#ifndef AVLTREES_CONTESTANT_H
#define AVLTREES_CONTESTANT_H

#include "../Scripts/wet1util.h"
#include "item.h"

class Country;
class Team;

class Contestant : public Item{

    Sport sport;
    int strength;
    int numOfTeams;
    shared_ptr<Team> myTeams[3];
   shared_ptr<Country> myCountry;
    int country;
public:
    explicit Contestant(int contestantID, int country, Sport sport, int strength);


};


#endif //AVLTREES_CONTESTANT_H