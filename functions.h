#ifndef AVLTREES_FUNCTIONS_H

#define AVLTREES_FUNCTIONS_H
using namespace std;
#include "node.h"
#include "iostream"

template <typename Item>
int getHeight(shared_ptr<Node<Item>> root){
    if(root == nullptr) return 0;
    int R = getHeight(root->right);
    int L = getHeight(root->left);
    return 1 + std::max(R, L);
}

template <typename Item>
bool isBalanced(shared_ptr<Node<Item>> root){
    if(root == nullptr) return true;
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    if(std::abs(leftHeight - rightHeight) > 1) return false;
    return isBalanced(root->left) && isBalanced(root->right);
}

// TO DO: maybe revert to the old implementation
template <typename Item>
bool contains(shared_ptr<Node<Item>> root, int val){
    if(root == nullptr) return false;
    if(root->getID() == val) return true;
    if(root->getID() < val){
        return contains(root->right, val);
    }else{
        return contains(root->left, val);
    }
}


// OLD IMPLEMENTATION
//template <typename Item>
//bool contains(shared_ptr<Node<Item>> root, int val){
//    if(root == nullptr) return false;
//    if(root->value == val) return true;
//    if(root->value < val){
//        return contains(root->right, val);
//    }else{
//        return contains(root->left, val);
//    }
//}

template <typename Item>
void print(shared_ptr<Node<Item>> root){
    if(root == nullptr) return;
    cout << root->getID() << " ";
}

template <typename Item>
void printInfo(shared_ptr<Node<Item>> root){
    if(root == nullptr) return;
    cout << "v: " << root->value << " h: " << root->height << " ";
}

template <typename Item>
void addAux(shared_ptr<Node<Item>> root, int val) {
    if (root == nullptr) {
        root = make_shared<Node<Item>>( val);
        return;
    }

    if (val < root->value) {
        if (root->left == nullptr) {
            root->left = make_shared<Node<Item>>(val);
            root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
        } else {
            addAux(root->left, val);
        }
    } else if (val > root->value) {
        if (root->right == nullptr) {
            root->right = make_shared<Node<Item>>(val);
            root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
        } else {
            addAux(root->right, val);
        }
    }
}

template <typename Item>
void addNode2(shared_ptr<Node<Item>> root, shared_ptr<Node<Item>> newNode){
    if(contains(root, newNode->getID())) return;
    addAux2(root, newNode);
}

template <typename Item>
void addAux2(shared_ptr<Node<Item>> root, shared_ptr<Node<Item>> newNode) {
    if (root == nullptr) {
        root = newNode;
        return;
    }

    if (newNode->getID() < root->getID()) {
        if (root->left == nullptr) {
            root->left = newNode;
            root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
        } else {
            addAux2(root->left, newNode);
        }
    } else if (newNode->getID() > root->getID()) {
        if (root->right == nullptr) {
            root->right = newNode;
            root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
        } else {
            addAux2(root->right, newNode);
        }
    }
}


template <typename Item>
void addNode(shared_ptr<Node<Item>>root, int val){
    if(contains(root, val)) return;
    addAux(root, val);
}

template <typename Item>
void inorder(shared_ptr<Node<Item>> root){
    if (root == nullptr) return;
    inorder(root->left);
    print(root);
    inorder(root->right);
}

template <typename Item>
void inorderINFO(shared_ptr<Node<Item>> root){
    if (root == nullptr) return;

    inorder(root->left);
    printInfo(root);
    inorder(root->right);
}

template <typename Item>
void swapFields(shared_ptr<Node<Item>> n1, shared_ptr<Node<Item>> n2){
    int val = n1->value;
    int bf = n1->balanceFactor;
    int height = n1->height;

    n1->value = n2->value;
    n1->balanceFactor = n2->balanceFactor;
    n1->height = n2->height; //getHeight

    n2->value = val;
    n2->balanceFactor = bf;
    n2->height = height; // getHeight

}

template <typename Item>
void LL(shared_ptr<Node<Item>> root){
    shared_ptr<Node<Item>> newRoot = root->left; // A
    shared_ptr<Node<Item>> tempL = newRoot->left; // AL
    shared_ptr<Node<Item>> tempR = newRoot->right; // AR
    swapFields(root, newRoot); // A <-> B


    root->left = tempL;
    newRoot->right = root->right;
    newRoot->left = tempR;
    root->right = newRoot;

}

template <typename Item>
void RR(shared_ptr<Node<Item>> root){
    shared_ptr<Node<Item>> newRoot = root->right; // A
    shared_ptr<Node<Item>> tempL = newRoot->left; // AL
    shared_ptr<Node<Item>> tempR = newRoot->right; // AR
    swapFields(root, newRoot); // A <-> B

    root->right = tempR;
    newRoot->left = root->left;
    newRoot->right = tempL;
    root->left = newRoot;
}

template <typename Item>
void LR(shared_ptr<Node<Item>> root){
    shared_ptr<Node<Item>> tempL = root->left;
    shared_ptr<Node<Item>> tempR = root->right;
    shared_ptr<Node<Item>> tempLR = root->left->right;
    swapFields(root, tempLR);

    root->right = tempLR;
    shared_ptr<Node<Item>> tempLRL = root->left->right->left;
    shared_ptr<Node<Item>> tempLRR = root->left->right->right;
    tempLR->right = tempR;
    tempLR->left = tempLRR;
    tempL->right = tempLRL;
}
#endif //AVLTREES_FUNCTIONS_H