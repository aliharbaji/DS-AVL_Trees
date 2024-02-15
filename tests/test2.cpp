//
// Created by allih on 14/02/2024.
//
#include "test2.h"



shared_ptr<Node<Team>> test2(){
    shared_ptr<Team> team1 = make_shared<Team>(1);
    shared_ptr<Node<Team>> nodeptr = make_shared<Node<Team>>(team1);


    // make Teams with id values 12 8 6 4 10 11 15 14 13 24 29 20 19
    shared_ptr<Team> team8 = make_shared<Team>(8);
    shared_ptr<Team> team6 = make_shared<Team>(6);
    shared_ptr<Team> team4 = make_shared<Team>(4);
    shared_ptr<Team> team10 = make_shared<Team>(10);
    shared_ptr<Team> team11 = make_shared<Team>(11);
    shared_ptr<Team> team12 = make_shared<Team>(12);
    shared_ptr<Team> team15 = make_shared<Team>(15);
    shared_ptr<Team> team14 = make_shared<Team>(14);
    shared_ptr<Team> team13 = make_shared<Team>(13);
    shared_ptr<Team> team24 = make_shared<Team>(24);
    shared_ptr<Team> team29 = make_shared<Team>(29);
    shared_ptr<Team> team20 = make_shared<Team>(20);
    shared_ptr<Team> team19 = make_shared<Team>(19);

    // add them to an AVL Tree
    shared_ptr<Node<Team>> root = make_shared<Node<Team>>(team12);
    root->left = make_shared<Node<Team>>(team8);
    root->left->left = make_shared<Node<Team>>(team6);
    root->left->left->left = make_shared<Node<Team>>(team4);
    root->left->right = make_shared<Node<Team>>(team10);
    root->left->right->right = make_shared<Node<Team>>(team11);
    root->right = make_shared<Node<Team>>(team15);
    root->right->left = make_shared<Node<Team>>(team14);
    root->right->left->left = make_shared<Node<Team>>(team13);
    root->right->right = make_shared<Node<Team>>(team24);
    root->right->right->left = make_shared<Node<Team>>(team20);
    root->right->right->left->left = make_shared<Node<Team>>(team19);
    root->right->right->right = make_shared<Node<Team>>(team29);

    // update parent pointers
    root->left->parent = root;
    root->left->left->parent = root->left;
    root->left->left->left->parent = root->left->left;
    root->left->right->parent = root->left;
    root->left->right->right->parent = root->left->right;
    root->right->parent = root;
    root->right->left->parent = root->right;
    root->right->left->left->parent = root->right->left;
    root->right->right->parent = root->right;
    root->right->right->left->parent = root->right->right;
    root->right->right->left->left->parent = root->right->right->left;
    root->right->right->right->parent = root->right->right;

    // update balance factors
//    root->left->balanceFactor = 1;
//    root->left->left->balanceFactor = 1;
//    root->left->left->left->balanceFactor = 0;
//    root->left->right->balanceFactor = 0;
//    root->left->right->right->balanceFactor = 0;
//    root->right->balanceFactor = -1;
//    root->right->left->balanceFactor = -1;
//    root->right->left->left->balanceFactor = 0;
//    root->right->right->balanceFactor = 1;
//    root->right->right->left->balanceFactor = 1;
//    root->right->right->left->left->balanceFactor = 0;
//    root->right->right->right->balanceFactor = 0;

    // update heights
    root->height = 4;
    root->left->height = 2;
    root->left->left->height = 1;
    root->left->left->left->height = 0;
    root->left->right->height = 1;
    root->left->right->right->height = 0;
    root->right->height = 3;
    root->right->left->height = 1;
    root->right->left->left->height = 0;
    root->right->right->height = 2;
    root->right->right->left->height = 1;
    root->right->right->left->left->height = 0;
    root->right->right->right->height = 0;


    return root;
}