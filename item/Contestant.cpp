//
// Created by omar_ on 16/02/2024.
//

#include "Contestant.h"

Contestant::Contestant(int contestantID, int country, Sport sport, int strength):
Item(contestantID),
country(country),
sport(sport),
strength(strength),
numOfTeams(0){}

//Contestant::Contestant(int contestantID, int country, Sport sport, int strength):
//Item(contestantID),
//country(country),
//sport(sport),
//strength(strength),
//numOfTeams(0){}

//Contestant::Contestant(int contestantID, int country,
//                       Sport sport, int strength): Item(contestantID),
//                                                   sport(sport), strength(strength), country(country),
//                                                   activeTeams(0){}
