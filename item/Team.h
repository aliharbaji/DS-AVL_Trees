//
// Created by omar_ on 16/02/2024.
//

#ifndef AVLTREES_TEAM_H
#define AVLTREES_TEAM_H

#include "../Scripts/wet1util.h"
#include "item.h"
#include "../tree.h"
#include "Country.h"
#include "../strengthtree.h"
#include <vector>
class Contestant;
class Country;


class Team : public Item {
    Sport sport;
    int size;
    int strength;
    weak_ptr<Country> myCountry; //changed this to weak_ptr
    int ausMeasure;
    vector<shared_ptr<Contestant>> tempContestants; // We add contestants to the Subtrees 3 at a time.
    // so this temporarily holds up to 2 contestants when size % 3 != 0.

    shared_ptr<Tree<Contestant>> contestants;
    shared_ptr<STree<Contestant>> strengths;

    shared_ptr<Tree<Contestant>> lowID;
    shared_ptr<Tree<Contestant>> midID;
    shared_ptr<Tree<Contestant>> highID;

    shared_ptr<STree<Contestant>> lowStr;
    shared_ptr<STree<Contestant>> midStr;
    shared_ptr<STree<Contestant>> highStr;

    void updateAusMeasure();
    void updateStrength();



public:
    explicit Team(int teamID, Sport sport, shared_ptr<Country> myCountry)
            : Item(teamID), sport(sport), myCountry(myCountry), size(0), strength(0), ausMeasure(0),
              contestants(std::make_shared<Tree<Contestant>>()),
              strengths(std::make_shared<STree<Contestant>>()),
              lowID(std::make_shared<Tree<Contestant>>()),
              midID(std::make_shared<Tree<Contestant>>()),
              highID(std::make_shared<Tree<Contestant>>()),
              lowStr(std::make_shared<STree<Contestant>>()),
              midStr(std::make_shared<STree<Contestant>>()),
              highStr(std::make_shared<STree<Contestant>>())
    {}
    Team(const Team&) = delete;
    Team& operator=(const Team&)= delete;



    void removeTeamFromItsCountry();
    int getStrength() const;
    int getNumberOfContestants() const;

    // adds contestant. Returns true if successful. False otherwise.
    bool addContestant(shared_ptr<Contestant> contestant);
    bool removeContestant(int contestantID);
    Sport getSport() const;
    int getCountryID() const;
};


#endif //AVLTREES_TEAM_H