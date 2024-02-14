//
// Created by allih on 09/02/2024.
//

#include "test1.h"

Node* test1(){
    Node *root = new Node();
    root->value = 12;
    root->left = new Node();
    root->left->value = 8;
    root->left->left = new Node();
    root->left->left->value = 6;
    root->left->right = new Node();
    root->left->right->value = 10;
    root->left->right->right = new Node();
    root->left->right->right->value = 11;
    root->right = new Node();
    root->right->value = 15;
    root->right->left = new Node();
    root->right->left->value = 14;
    root->right->left->left = new Node();
    root->right->left->left->value = 13;
    root->right->right = new Node();
    root->right->right->value = 24;
    root->right->right->left = new Node();
    root->right->right->left->value = 20;
    root->right->right->left->left = new Node();
    root->right->right->left->left->value = 19;
    root->right->right->right = new Node();
    root->right->right->right->value = 29;
    // update height of each node
    root->height = getHeight(root);
    root->left->height = getHeight(root->left);
    root->left->left->height = getHeight(root->left->left);
    root->left->right->height = getHeight(root->left->right);
    root->left->right->right->height = getHeight(root->left->right->right);
    root->right->height = getHeight(root->right);
    root->right->left->height = getHeight(root->right->left);
    root->right->left->left->height = getHeight(root->right->left->left);
    root->right->right->height = getHeight(root->right->right);
    root->right->right->left->height = getHeight(root->right->right->left);
    root->right->right->left->left->height = getHeight(root->right->right->left->left);
    root->right->right->right->height = getHeight(root->right->right->right);
    return root;
}
