//
// Created by allih on 14/02/2024.
//
#include "test2.h"



shared_ptr<Node<Team>> test2(){
    shared_ptr<Team> team1 = make_shared<Team>(14);

    shared_ptr<Node<Team>> nodeptr = make_shared<Node<Team>>(*team1);


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
    shared_ptr<Node<Team>> root = make_shared<Node<Team>>(*team12);
    root->left = make_shared<Node<Team>>(*team8);
    root->left->left = make_shared<Node<Team>>(*team6);
    root->left->left->left = make_shared<Node<Team>>(*team4);
    root->left->right = make_shared<Node<Team>>(*team10);
    root->left->right->right = make_shared<Node<Team>>(*team11);
    root->right = make_shared<Node<Team>>(*team15);
    root->right->left = make_shared<Node<Team>>(*team14);
    root->right->left->left = make_shared<Node<Team>>(*team13);
    root->right->right = make_shared<Node<Team>>(*team24);
    root->right->right->left = make_shared<Node<Team>>(*team20);
    root->right->right->left->left = make_shared<Node<Team>>(*team19);
    root->right->right->right = make_shared<Node<Team>>(*team29);
    return root;
}