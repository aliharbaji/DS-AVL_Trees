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
#include <iostream>

class Contestant;
class Country;
//TODO: clean code and remove all cases of throwing logic_error which was mainly for debugging.
//this is apparently necessary if you want to pass "this" instance of a class as a shared_ptr.
class Team : public Item {
    Sport sport;
    int strength;
    weak_ptr<Country> myCountry; //changed this to weak_ptr
    int ausMeasure;

    shared_ptr<Tree<Contestant>> contestants;
    shared_ptr<STree<Contestant>> strengths;

    shared_ptr<Tree<Contestant>> lowIDTree;
    shared_ptr<Tree<Contestant>> midIDTree;
    shared_ptr<Tree<Contestant>> highIDTree;

    shared_ptr<STree<Contestant>> lowStrTree;
    shared_ptr<STree<Contestant>> midStrTree;
    shared_ptr<STree<Contestant>> highStrTree;


    bool updateAusMeasure();
    void updateStrength();
    void redistribute();
    void moveHighToMid();
    void moveMidToLow();
    void moveMidToHigh();
    void moveHighToLow();
    void moveLowToHigh();
    void moveLowToMid();
    bool addAux(shared_ptr<Contestant> contestant);
    bool removeAux(int contestantID);
    static shared_ptr<Contestant>* copyTeamIntoArrayAndUpdateContestants(shared_ptr<Team> team);
    static void auxCopy(shared_ptr<Node<Contestant>> root, shared_ptr<Contestant>* arr, int& index, shared_ptr<Team> team);
    static shared_ptr<Contestant>* mergeIDArrays(shared_ptr<Contestant>* arr1, shared_ptr<Contestant>* arr2, int size1, int size2, int* totalSize);
    static shared_ptr<Contestant>* mergeStrArrays(shared_ptr<Contestant>* arr1, shared_ptr<Contestant>* arr2, int size1, int size2, int* totalSize);

public:
    explicit Team(int teamID, Sport sport, std::shared_ptr<Country> myCountry)
            : Item(teamID), sport(sport), myCountry(myCountry), strength(0), ausMeasure(0),
              contestants(std::make_shared<Tree<Contestant>>()),
              strengths(std::make_shared<STree<Contestant>>()),
              lowIDTree(std::make_shared<Tree<Contestant>>()),
              midIDTree(std::make_shared<Tree<Contestant>>()),
              highIDTree(std::make_shared<Tree<Contestant>>()),
              lowStrTree(std::make_shared<STree<Contestant>>()),
              midStrTree(std::make_shared<STree<Contestant>>()),
              highStrTree(std::make_shared<STree<Contestant>>())
    {}
    Team(const Team&) = delete;
    Team& operator=(const Team&)= delete;



    void removeTeamFromItsCountry();
    int getStrength() const;
    int getAusMeasure() const;
    int getNumberOfContestants() const;

    //Takes a pointer to the contestant and adds him to the team. Returns true if successful. False otherwise.
    bool addContestant(shared_ptr<Contestant> contestant);
    bool removeContestant(int contestantID);
    Sport getSport() const;
    int getCountryID() const;
    void recursivePrintPreOrder(shared_ptr<Node<Contestant>> node);
    void recursivePrintInOrder(shared_ptr<Node<Contestant>> node);

    void uniteWith(shared_ptr<Team> other);
    void uniteTeamsIntoThis(shared_ptr<Team> team);


};


#endif //AVLTREES_TEAM_H