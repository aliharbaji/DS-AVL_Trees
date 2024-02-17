//
// Created by omar_ on 16/02/2024.
//

#ifndef AVLTREES_CONTESTANT_H
#define AVLTREES_CONTESTANT_H


class Contestant {
    int contestantID;
    int countryID;
    int strength;
    int medals;
public:
    explicit Contestant(int contestantID);

    int getID() const;

};


#endif //AVLTREES_CONTESTANT_H