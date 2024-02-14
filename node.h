//
// Created by allih on 09/02/2024.
//

#ifndef AVLTREES_NODE_H
#define AVLTREES_NODE_H

// GENERIC
typedef struct node{
    int value = 0;
    int balanceFactor = 0;
    struct node* left = nullptr, *right = nullptr;
    int height = 0;
}Node;


#endif //AVLTREES_NODE_H