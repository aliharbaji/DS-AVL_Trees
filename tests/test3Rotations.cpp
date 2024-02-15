//
// Created by allih on 15/02/2024.
//

#include "test3Rotations.h"



shared_ptr<Node<Team>> test3(){
    shared_ptr<Team> P =  make_shared<Team>(69);
    shared_ptr<Team> A =  make_shared<Team>(3);
    shared_ptr<Team> B =  make_shared<Team>(2);
    shared_ptr<Team> C =  make_shared<Team>(1);

    // make P node
    shared_ptr<Node<Team>> Pn = make_shared<Node<Team>>(P);
    // make A node
    shared_ptr<Node<Team>> An = make_shared<Node<Team>>(A);
    // make B node
    shared_ptr<Node<Team>> Bn = make_shared<Node<Team>>(B);
    // make C node
    shared_ptr<Node<Team>> Cn = make_shared<Node<Team>>(C);

    // add A to P
    Pn->left = An;
    An->parent = Pn;
    // add B to A
    An->right = Bn;
    Bn->parent = An;
    // add C to B
    Bn->right = Cn;
    Cn->parent = Bn;

    Pn->height = 3;
    An->height = 2;
    Bn->height = 1;
    Cn->height = 0;



    return Pn;
}