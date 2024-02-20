//
// Created by omar_ on 16/02/2024.
//

#ifndef AVLTREES_CONTESTANT_H
#define AVLTREES_CONTESTANT_H

#include "../Scripts/wet1util.h"
#include "item.h"
#include "Country.h"

class Country;
class Team;

class Contestant : public Item{

    Sport sport;
    int strength;
    int numOfTeams;
    shared_ptr<Team> myTeams[3];
    shared_ptr<Country> myCountry;
public:
    explicit Contestant(int contestantID, shared_ptr<Country>& country, Sport sport, int strength);
    int getNumOfActiveTeams() const;
    void removeFromTeams();
    void removeFromCountry();
    Sport getSport() const;
    bool isActiveInTeam(int teamID);
    void addTeam(shared_ptr<Team>& team);
    void removeTeam(int teamID);
    int getCountryID() const;
    void updateStrength(int change);
    int getStrength() const;
};


#endif //AVLTREES_CONTESTANT_H