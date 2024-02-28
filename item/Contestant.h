//
// Created by omar_ on 16/02/2024.
//

#ifndef AVLTREES_CONTESTANT_H
#define AVLTREES_CONTESTANT_H

#include "../Scripts/wet1util.h"
#include "item.h"
#include "Country.h"

#define MAX_TEAMS 3

class Country;
class Team;



class Contestant : public Item{

    weak_ptr<Country> myCountry;
    Sport sport;
    int strength;
    int numOfTeams;
    int myTeams[MAX_TEAMS];
public:
    explicit Contestant(int contestantID, weak_ptr<Country> country, Sport sport, int strength);
    int getNumOfActiveTeams() const;
    Sport getSport() const;
    bool isActiveInTeam(int teamID) const;
    bool addTeam(int teamID);
    bool removeTeam(int teamID);
    int getCountryID() const;
    void updateStrength(int change);
    int getStrength() const;
    bool isAvailable() const;
    weak_ptr<Country> getCountry() const;
    int getTeamID(int i) const;
//    weak_ptr<Team> getTeam(int i) const;
};


#endif //AVLTREES_CONTESTANT_H