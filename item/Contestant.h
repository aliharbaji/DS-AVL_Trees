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

    Sport sport;
    int strength;
    int numOfTeams;
    int myTeams[MAX_TEAMS];
    //On the other hand he definitely needs a pointer to his country because the complexity requires it.
    weak_ptr<Country> myCountry;
public:
    explicit Contestant(int contestantID, weak_ptr<Country> country, Sport sport, int strength);
    int getNumOfActiveTeams() const;
    Sport getSport() const;
    bool isActiveInTeam(int teamID) const;
    bool addTeam(weak_ptr<Team> team);
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