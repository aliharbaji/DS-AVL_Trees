//
// Created by allih on 09/02/2024.
//

#include <memory>

#ifndef AVLTREES_NODE_H
using namespace std;
// const init
enum class IMBALANCE_TYPE{
    LL,
    LR,
    RL,
    RR
};
const int RIGHT_HEAVY = 1;
const int LEFT_HEAVY = -1;
const int BALANCED = 0;
const int Zero = 0;

#define AVLTREES_NODE_H
#include "memory"

// GENERIC
template <typename Item>
class Node{
public:
    shared_ptr<Item> data;
    shared_ptr<Node> left, right;
    shared_ptr<Node> parent;
    int value;
    int balanceFactor;
    int height;
    friend class Tree;

    Node(shared_ptr<Item> data): data(data), value(data->getID()), height(Zero), balanceFactor(Zero),
    left(nullptr), right(nullptr), parent(nullptr){}

    int getID() const {
        return data->getID();
    }

};


#endif //AVLTREES_NODE_H