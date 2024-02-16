#ifndef AVLTREES_FUNCTIONS_H
#define AVLTREES_FUNCTIONS_H
using namespace std;
#include "node.h"
#include "iostream"

template <typename T>
void updateHeight(shared_ptr<Node<T>>& node) {
    if (node == nullptr) return;

    int leftHeight = (node->left != nullptr) ? getHeight(node->left) : 0;
    int rightHeight = (node->right != nullptr) ? getHeight(node->right) : 0;
    if(node->left == nullptr && node->right == nullptr){
        node->height = 0;
        return;
    }
    node->height = 1 + max(leftHeight, rightHeight);
}

//template <typename T>
//void updateHeight(shared_ptr<Node<T>>& node) {
//    if (node != nullptr) {
//        if(node->value == 20){
//            cout << "Updating height for " << node->value << endl; // delete later
//        }
//        int leftHeight = (node->left == nullptr) ? 0 : node->left->height;
//        int rightHeight = (node->right == nullptr) ? 0 : node->right->height;
//        int height = 1 + std::max(leftHeight, rightHeight);
//        height = (height < 0) ? 0 : height;
//        node->height = height;
//    }
//}

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
    updateHeight(root);
    updateHeight(temp); // Update the height after updating its right child
    updateHeight(parent);
}


//template <typename T>
//void LL(shared_ptr<Node<T>>& root) {
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

template <typename T>
void RR(shared_ptr<Node<T>>& root) {
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
    updateHeight(root->left); //this works for some reason
}
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
        case RIGHT_HEAVY:

            break;
        case LEFT_HEAVY:

            break;
    }
}

// TODO: make sure this works in O(1) time
//this does not work in O(1) time
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
        return;
    }

    if (newNode->value < son->value) {
        addAux(son, son->left, newNode);
    } else {
        addAux(son, son->right, newNode);
    }

    // Update son's height after recursive calls
    updateHeight(son);

    // Check if the tree is balanced
    if (son->getBF() > One || son->getBF() < -One) {

        cout << "***********PERFORM ROTATION************** on node " << son->value << " its BF is " << son->getBF() << endl;
        switch (son->getBF()) {
            case LEFT_HEAVY: {
                int rightHeight = (son->right == nullptr) ? 0 : getHeight(son->right);
                int leftHeight = (son->left == nullptr) ? 0 : getHeight(son->left);
                int BF = leftHeight - rightHeight;

                if (BF >= 0) {
                    LL(son);
                } else {
                    LR(son);
                }
                break;
            }
            case RIGHT_HEAVY: {
                int rightHeight = (son->right == nullptr) ? 0 : son->right->height;
                int leftHeight = (son->left == nullptr) ? 0 : son->left->height;
                int BF = leftHeight - rightHeight;

                if (BF <= 0) {
                    RR(son);
                } else {
                    RL(son);
                }
                break;
            }
        }
    }

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