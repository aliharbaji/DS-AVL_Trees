//
// Created by allih on 09/02/2024.
//

#include <memory>

#ifndef AVLTREES_NODE_H
using namespace std;
#define AVLTREES_NODE_H
#include "memory"

// TODO: remove balance factor field
template <class T>
class Node{
private:
    template<typename U> friend class Tree;

public:
    shared_ptr<T> data;
    shared_ptr<Node<T>> left, right;
    shared_ptr<Node<T>> parent; //TODO: parent needs to be changed to weak_ptr because we have circular references.
    int height;

    Node(shared_ptr<T> data): data(data),  height(0),
    left(nullptr), right(nullptr), parent(){}

    int getID() const {
        return data->getID();
    }

    int getStrength() const{
        return data->getStrength();
    }

    int getBF() const{
        int leftHeight = (left != nullptr) ? left->height : -1;
        int rightHeight = (right != nullptr) ? right->height : -1;
        int bf = leftHeight - rightHeight;
        return bf;
    }


};


#endif //AVLTREES_NODE_H