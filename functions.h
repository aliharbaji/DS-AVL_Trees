#ifndef AVLTREES_FUNCTIONS_H
#define AVLTREES_FUNCTIONS_H
using namespace std;
#include "node.h"
#include "iostream"

template <typename T>
void updateHeight(shared_ptr<Node<T>>& node) {
    if (node == nullptr) return;

    int leftHeight = (node->left != nullptr) ? node->left->height : -1; // Initialize to -1 instead of 0
    int rightHeight = (node->right != nullptr) ? node->right->height : -1; // Initialize to -1 instead of 0

    node->height = 1 + max(leftHeight, rightHeight);
}


// TODO: fix the height update
template <typename T>
void LL(shared_ptr<Node<T>>& root) {
    if (root == nullptr) return;
    cout << "inside LL on node " << root->value << endl;
    shared_ptr<Node<T>> parent = root->parent;
    shared_ptr<Node<T>> temp = root->left;

    // Update parent pointers
    temp->parent = parent;
    root->parent = temp;

    // Update child pointers
    root->left = temp->right;
    if (temp->right != nullptr) {
        temp->right->parent = root;
    }

    temp->right = root;

    // Update parent's child pointer
    if (parent != nullptr) {
        if (parent->left == root) {
            parent->left = temp;
        } else {
            parent->right = temp;
        }
    }

    // Update heights
    updateHeight(temp); // Update the height after updating its right child
    updateHeight(temp->right); // Update the height of the right child
    updateHeight(root);
    updateHeight(parent);
}

template <typename T>
void RR(shared_ptr<Node<T>>& root) {
    if (root == nullptr || root->right == nullptr) return;

    cout << "inside RR on node " << root->value << endl;

    shared_ptr<Node<T>> parent = root->parent;
    shared_ptr<Node<T>> temp = root->right;

    // Update parent pointers
    temp->parent = parent;
    root->parent = temp;

    // Update child pointers
    root->right = temp->left;
    if (temp->left != nullptr) {
        temp->left->parent = root;
    }

    temp->left = root;

    // Update parent's child pointer
    if (parent != nullptr) {
        if (parent->left == root) {
            parent->left = temp;
        } else {
            parent->right = temp;
        }
    }

    // Update heights
    updateHeight(temp); // Update the height after updating its left child
    updateHeight(temp->left); // Update the height of the left child
    updateHeight(root);
    updateHeight(parent);
}


//template <typename T>
//void LLOLD(shared_ptr<Node<T>>& root) {
//    if(root == nullptr) return;
//    if(root->value == 20){
//        cout <<"here*************" << endl;
//
//    }
//    shared_ptr<Node<T>> parent = root->parent;
//    shared_ptr<Node<T>> temp = root->left;
//
//    // Update parent pointers
//    temp->parent = parent;
//    root->parent = temp;
//
//    // Update child pointers
//    root->left = temp->right;
//    if (temp->right != nullptr) {
//        temp->right->parent = root;
//    }
//
//    temp->right = root;
//
//    // Update parent's child pointer
//    if (parent != nullptr) {
//        if (parent->left == root) {
//            parent->left = temp;
//        } else {
//            parent->right = temp;
//        }
//    }
//    updateHeight(root->right); //this works for some reason
//}

//template <typename T>
//void RROLD(shared_ptr<Node<T>>& root) {
//    shared_ptr<Node<T>> parent = root->parent;
//    shared_ptr<Node<T>> temp = root->right;
//
//    // Update parent pointers
//    temp->parent = parent;
//    root->parent = temp;
//
//    // Update child pointers
//    root->right = temp->left;
//    if (temp->left != nullptr) {
//        temp->left->parent = root;
//    }
//
//    temp->left = root;
//    // Update parent's child pointer
//    if (parent != nullptr) {
//        if (parent->left == root) {
//            parent->left = temp;
//        } else {
//            parent->right = temp;
//        }
//    }
//    updateHeight(root->left); //this works for some reason
//}
template <typename T>
void LR(shared_ptr<Node<T>>& root){
    if(root == nullptr || root->left == nullptr) return;
    RR(root->right);
    LL(root);
}
template <typename T>
void RL(shared_ptr<Node<T>>& root){
    if(root == nullptr || root->left == nullptr) return;
    LL(root->left);
    RR(root);
}




template <typename T>
void rotate(shared_ptr<Node<T>>& imbalancedNode){
    if(imbalancedNode == nullptr) return;

    switch(imbalancedNode->getBF()){
        case LEFT_HEAVY: {
            int rightHeight = (imbalancedNode->right == nullptr) ? 0 : imbalancedNode->right->height;
            int leftHeight = (imbalancedNode->left == nullptr) ? 0 : imbalancedNode->left->height;
            int BF = leftHeight - rightHeight;

            if (BF >= 0) {
                LL(imbalancedNode);
            } else {
                LR(imbalancedNode);
            }
            break;
        }
        case RIGHT_HEAVY: {
            int rightHeight = (imbalancedNode->right == nullptr) ? 0 : imbalancedNode->right->height;
            int leftHeight = (imbalancedNode->left == nullptr) ? 0 : imbalancedNode->left->height;
            int BF = leftHeight - rightHeight;

            if (BF <= 0) {
                RR(imbalancedNode);
            } else {
                RL(imbalancedNode);
            }
            break;
        }
    }
}


template <typename T>
int getHeight(shared_ptr<Node<T>> root){
    if(root == nullptr) return -1;
//    int R = getHeight(root->right);
//    int L = getHeight(root->left);
    //the commented lines give a segmentation fault
    int R = (root->right == nullptr ? -1 : root->right->height);
    int L = (root->left == nullptr ? -1 : root->left->height);

    int height = 1 + max(R, L);
    int heightToReturn = (height < Zero) ? Zero : height;
    if(root->right == nullptr && root->left == nullptr) { // if it's a leaf node
        return Zero;
    }
    return heightToReturn;
}

// Slow Version meaning it iterates over the tree multiple times and doesn't use the height field
template <typename T>
bool isBalancedSlowVersion(shared_ptr<Node<T>> root){
    if(root == nullptr) return true;
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    if(std::abs(leftHeight - rightHeight) > 1) return false;
    return isBalancedSlowVersion(root->left) && isBalancedSlowVersion(root->right);
}

template <typename T>
bool contains(shared_ptr<Node<T>> root, int val){
    if(root == nullptr) return false;
    if(root->value == val) return true;
    if(root->value < val){
        return contains(root->right, val);
    }else{
        return contains(root->left, val);
    }
}

template <typename T>
void print(shared_ptr<Node<T>> root){
    if(root == nullptr) return;
    cout << root->value << " ";
}

template <typename T>
void printInfo(shared_ptr<Node<T>> root){
    if(root == nullptr) return;
    cout << "v:" << root->value << " h:" << root->height << ", ";
}




template <typename T>
void addAux(shared_ptr<Node<T>>& parent, shared_ptr<Node<T>>& son, shared_ptr<Node<T>>& newNode) {
    if (son == nullptr) {
        son = newNode;
        son->parent = parent;
        updateHeight(parent);
        return;
    }

    if (newNode->value < son->value) {
        addAux(son, son->left, newNode);
    } else {
        addAux(son, son->right, newNode);
    }

    cout << "son is " << son->value << " and its BF is " << son->getBF() << endl;
    cout << "parent is " << parent->value << " and its BF is " << parent->getBF() << endl;
    // Check if the tree is balanced
    if (son->getBF() > One || son->getBF() < -One) {
        cout << "***********PERFORM ROTATION************** on node " << son->value << " its BF is " << son->getBF() << endl;
        rotate(son);
    }else if(parent->getBF() > One || parent->getBF() < -One){
        cout << "***********PERFORM ROTATION************** on node " << parent->value << " its BF is " << parent->getBF() << endl;
        rotate(parent);
    }

    // Update son's height after recursive calls
    updateHeight(son);
    // Update parent's height after rotations
    updateHeight(parent);
}


template <typename T>
void addNode(shared_ptr<Node<T>>& parent, shared_ptr<Node<T>>& newNode){
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

template <typename T>
shared_ptr<Node<T>> insert(shared_ptr<Node<T>>& root, int id){
    shared_ptr<T> newNode = make_shared<T>(id);
    shared_ptr<Node<T>> team18Node = make_shared<Node<T>>(newNode);
    addNode(root, team18Node);
    return root;
}

template <typename T>
void inorder(shared_ptr<Node<T>> root){
    if (root == nullptr) return;
    inorder(root->left);
    print(root);
    inorder(root->right);
}

// for debugging purposes
template <typename T>
void inorderINFO(shared_ptr<Node<T>> root){
    if (root == nullptr) return;
    inorderINFO(root->left);
    printInfo(root);
    inorderINFO(root->right);
}


#endif //AVLTREES_FUNCTIONS_H