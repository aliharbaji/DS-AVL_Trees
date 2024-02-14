#ifndef AVLTREES_FUNCTIONS_H

#define AVLTREES_FUNCTIONS_H
using namespace std;

#include "node.h"
int getHeight(Node* root);
bool isBalanced(Node *root);
bool contains(Node* root, int val);
void inorder(Node* root);
void addNode(Node* root, int val);
void inorderINFO(Node* root);


void LL(Node* root);
void RR(Node* root);
void LR(Node* root);
#endif //AVLTREES_FUNCTIONS_H