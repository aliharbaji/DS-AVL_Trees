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
const int RIGHT_HEAVY = -2;
const int LEFT_HEAVY = 2;
const int BALANCED = 0;
const int Zero = 0;
const int One = 1;
#define AVLTREES_NODE_H
#include "memory"

// TODO: remove balance factor field
template <class T>
class Node{
private:
public:
    shared_ptr<T> data;
    shared_ptr<Node> left, right;
    shared_ptr<Node> parent;
    int value;
    int height;
    friend class Tree;

    Node(shared_ptr<T> data): data(data), value(data->getID()), height(Zero),
    left(nullptr), right(nullptr), parent(nullptr){}

    int getID() const {
        return data->getID();
    }

    int getBF() {
        int leftHeight = (left != nullptr) ? left->height : -1;
        int rightHeight = (right != nullptr) ? right->height : -1;
        int bf = leftHeight - rightHeight;
        return bf;
    }


};


#endif //AVLTREES_NODE_H