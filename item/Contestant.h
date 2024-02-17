//
// Created by omar_ on 16/02/2024.
//

#ifndef AVLTREES_CONTESTANT_H
#define AVLTREES_CONTESTANT_H

#include "../Scripts/wet1util.h"

class Contestant {
    int contestantID;
    Sport sport;
    int strength;
    int countries[];
public:
    explicit Contestant(int contestantID, int countryID, Sport sport, int strength);

    int getID() const;

};


#endif //AVLTREES_CONTESTANT_H