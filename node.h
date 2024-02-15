//
// Created by allih on 09/02/2024.
//

#include <memory>

#ifndef AVLTREES_NODE_H
using namespace std;
const int Zero = 0;
#define AVLTREES_NODE_H \
#include "memory"

// GENERIC
template <typename Item>
class Node{
public:
    shared_ptr<Item> data;
    int value;
    // TO DO: use value instead of Item->getID(), the Node shouldn't be generic (maybe)
    int balanceFactor;
    shared_ptr<Node> left, right;
    shared_ptr<Node> parent;
    int height = 0;

    Node(shared_ptr<Item> data): data(data), value(data->getID()), balanceFactor(Zero), left(nullptr), right(nullptr), parent(nullptr){}
    int getID() const {
        return data->getID();
    }

};


#endif //AVLTREES_NODE_H