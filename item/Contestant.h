//
// Created by omar_ on 16/02/2024.
//

#ifndef AVLTREES_CONTESTANT_H
#define AVLTREES_CONTESTANT_H

#include "../Scripts/wet1util.h"
#include "Item.h"

class Contestant : public Item{

    Sport sport;
    int strength;
    int countries[];
public:
    explicit Contestant(int contestantID, int countryID, Sport sport, int strength);


};


#endif //AVLTREES_CONTESTANT_H