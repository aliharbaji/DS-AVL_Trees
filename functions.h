#ifndef AVLTREES_FUNCTIONS_H

#define AVLTREES_FUNCTIONS_H
using namespace std;
#include "node.h"
#include "iostream"

// work in progress, still gives segmentation fault
template <typename Item>
void LL(shared_ptr<Node<Item>>& root){
    shared_ptr<Node<Item>> rootParent = root->parent;
    shared_ptr<Node<Item>> newRoot = root->left;

    if(rootParent->left == root){
        rootParent->left = newRoot;
    } else{
        rootParent->right = newRoot;
    }
    if(newRoot != nullptr){
        newRoot->parent = rootParent;
    }

    root->left = newRoot->right;

    if(newRoot->right != nullptr){
        newRoot->right->parent = root;
    }

    newRoot->right = root;
    root->parent = newRoot;


}

//template <typename Item>
//void LL(shared_ptr<Node<Item>> root){
//    shared_ptr<Node<Item>> newRoot = root->left; // A
//    shared_ptr<Node<Item>> tempL = newRoot->left; // AL
//    shared_ptr<Node<Item>> tempR = newRoot->right; // AR
//    swapFields(root, newRoot); // A <-> B
//
//    root->left = tempL;
//    newRoot->right = root->right;
//    newRoot->left = tempR;
//    root->right = newRoot;
//}

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
void rotate(shared_ptr<Node<Item>>& imbalancedNode){
    if(imbalancedNode == nullptr) return;
    switch(imbalancedNode->balanceFactor){
        case RIGHT_HEAVY:
            break;
        case LEFT_HEAVY:
            break;
    }
}

template <typename Item>
int getHeight(shared_ptr<Node<Item>> root){
    if(root == nullptr) return 0;
    int R = getHeight(root->right);
    int L = getHeight(root->left);
    return 1 + std::max(R, L);
}

// Slow Version meaning it iterates over the tree multiple times and doesn't use the height field
template <typename Item>
bool isBalancedSlowVersion(shared_ptr<Node<Item>> root){
    if(root == nullptr) return true;
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    if(std::abs(leftHeight - rightHeight) > 1) return false;
    return isBalancedSlowVersion(root->left) && isBalancedSlowVersion(root->right);
}

template <typename Item>
bool contains(shared_ptr<Node<Item>> root, int val){
    if(root == nullptr) return false;
    if(root->value == val) return true;
    if(root->value < val){
        return contains(root->right, val);
    }else{
        return contains(root->left, val);
    }
}

template <typename Item>
void print(shared_ptr<Node<Item>> root){
    if(root == nullptr) return;
    cout << root->value << " ";
}

template <typename Item>
void printInfo(shared_ptr<Node<Item>> root){
    if(root == nullptr) return;
    cout << "v:" << root->value << " h:" << root->height << ", ";
}

template <typename Item>
void updateHeight(shared_ptr<Node<Item>>& node) {
    if (node == nullptr) return;
    int leftHeight = (node->left != nullptr) ? node->left->height : -1;
    int rightHeight = (node->right != nullptr) ? node->right->height : -1;
    node->height = 1 + max(leftHeight, rightHeight);
}



template <typename Item>
void addAux(shared_ptr<Node<Item>> parent, shared_ptr<Node<Item>>& son, shared_ptr<Node<Item>> newNode){
    if (son == nullptr){
        son = newNode;
        newNode->parent = parent;
        return;
    }
    if(newNode->value < son->value){
        addAux(son, son->left, newNode);
    }else{
        addAux(son, son->right, newNode);
    }

    // update the height of the parent and balance factor
    if(parent != nullptr){
        if(parent->left == son) {
            if (parent->right == nullptr) {
                parent->height = 1 + son->height;
                parent->balanceFactor = parent->height - 0;
            } else {
                parent->height = 1 + max(son->height, parent->right->height);
            }
        }else if(parent->right == son){
            if(parent->left == nullptr){
                parent->height = 1 + son->height;
                parent->balanceFactor = 0 - parent->height;
            }else {
                parent->height = 1 + max(son->height, parent->left->height);
                parent->balanceFactor = parent->left->height - parent->right->height;
            }
        }
    }
    // update the height of the son (still dont know why this is necessary but it is)
    updateHeight(son);

    // update the balance factor of the son
    son->balanceFactor = (son->left != nullptr ? son->left->height : -1) - (son->right != nullptr ? son->right->height : -1);

    // check if the tree is balanced
    if(son->balanceFactor > 1 || son->balanceFactor < -1){
        cout << "PERFORM ROTATION " << son->value << endl; // delete later
//        rotate(son);
    }


}

template <typename Item>
void addNode(shared_ptr<Node<Item>>& parent, shared_ptr<Node<Item>> newNode){
    if(parent == nullptr){
        parent = newNode; // if the tree is empty make the new node the root
        return;
    }

    if(contains(parent, newNode->value)) return; // if the value is already in the tree dont add it

    if (newNode->value < parent->value){
        addAux(parent, parent->left, newNode);
    }else{
        addAux(parent, parent->right, newNode);
    }
}


// Old implementation of addNode
//template <typename Item>
//void addAux(shared_ptr<Node<Item>> root, shared_ptr<Node<Item>> newNode) {
//    if (root == nullptr) {
//        root = newNode;
//        return;
//    }
//
//    if (newNode->value < root->value) {
//        if (root->left == nullptr) {
//            root->left = newNode;
//            root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
//        } else {
//            addAux(root->left, newNode);
//        }
//    } else if (newNode->value > root->value) {
//        if (root->right == nullptr) {
//            root->right = newNode;
//            root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
//        } else {
//            addAux(root->right, newNode);
//        }
//    }
//}
//
//template <typename Item>
//void addNode(shared_ptr<Node<Item>> root, shared_ptr<Node<Item>> newNode){
//    if(contains(root, newNode->getID())) return;
//    addAux(root, newNode);
//}

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
    inorderINFO(root->left);
    printInfo(root);
    inorderINFO(root->right);
}

template <typename Item>
void swapFields(shared_ptr<Node<Item>> n1, shared_ptr<Node<Item>> n2){
    // maybe implement an assignment operator
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


//template <typename Item>
//void LR(shared_ptr<Node<Item>> root){
//    shared_ptr<Node<Item>> tempL = root->left;
//    shared_ptr<Node<Item>> tempR = root->right;
//    shared_ptr<Node<Item>> tempLR = root->left->right;
//    swapFields(root, tempLR);
//
//    root->right = tempLR;
//    shared_ptr<Node<Item>> tempLRL = root->left->right->left;
//    shared_ptr<Node<Item>> tempLRR = root->left->right->right;
//    tempLR->right = tempR;
//    tempLR->left = tempLRR;
//    tempL->right = tempLRL;
//}
#endif //AVLTREES_FUNCTIONS_H