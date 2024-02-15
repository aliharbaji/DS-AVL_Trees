#ifndef AVLTREES_FUNCTIONS_H
#define AVLTREES_FUNCTIONS_H
using namespace std;
#include "node.h"
#include "iostream"


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
}

template <typename T>
void LL(shared_ptr<Node<T>>& root) {
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

// work in progress, still gives segmentation fault
//template <typename T>
//void LL2(shared_ptr<Node<T>>& root){
//    shared_ptr<Node<T>> rootParent = root->parent;
//    shared_ptr<Node<T>> newRoot = root->left;
//
//    if(rootParent->left == root){
//        rootParent->left = newRoot;
//    } else{
//        rootParent->right = newRoot;
//    }
//    if(newRoot != nullptr){
//        newRoot->parent = rootParent;
//    }
//
//    root->left = newRoot->right;
//
//    if(newRoot->right != nullptr){
//        newRoot->right->parent = root;
//    }
//
//    newRoot->right = root;
//    root->parent = newRoot;
//}



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

template <typename T>
int getHeight(shared_ptr<Node<T>> root){
    if(root == nullptr) return 0;
    int R = getHeight(root->right);
    int L = getHeight(root->left);
    return 1 + std::max(R, L);
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
void updateHeight(shared_ptr<Node<T>>& node) {
    if (node != nullptr) {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }
}



template <typename T>
void addAux(shared_ptr<Node<T>> parent, shared_ptr<Node<T>>& son, shared_ptr<Node<T>> newNode){
    if (son == nullptr){
        son = newNode;
        newNode->parent = parent;
//        updateHeight(parent);
        return;
    }
    if(newNode->value < son->value){
        addAux(son, son->left, newNode);
    }else{
        addAux(son, son->right, newNode);
    }

    updateHeight(son);


    // check if the tree is balanced


    if(son->getBF() > 1 || son->getBF() < -1){
        cout << "PERFORM ROTATION************** " << son->value << "BF is" << son->getBF()<< endl; // delete later
        switch (son->getBF()) {
            case RIGHT_HEAVY:
                if(son->right->getBF() > 0){
                    LL(son);

                }else{
                    LR(son);
                }
                break;
            case LEFT_HEAVY:
                if(son->left->getBF() < 0){
                    RR(son);
                }else{
                    RL(son);
                }
                break;
        }
    }
        updateHeight(parent);

}

template <typename T>
void addNode(shared_ptr<Node<T>>& parent, shared_ptr<Node<T>> newNode){
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

template <typename T>
void inorder(shared_ptr<Node<T>> root){
    if (root == nullptr) return;
    inorder(root->left);
    print(root);
    inorder(root->right);
}

template <typename T>
void inorderINFO(shared_ptr<Node<T>> root){
    if (root == nullptr) return;
    inorderINFO(root->left);
    printInfo(root);
    inorderINFO(root->right);
}

template <typename T>
void swapFields(shared_ptr<Node<T>> n1, shared_ptr<Node<T>> n2){
    // maybe implement an assignment operator
    int val = n1->value;
    int height = n1->height;

    n1->value = n2->value;
    n1->height = n2->height; //getHeight
    n2->value = val;
    n2->height = height; // getHeight
}

#endif //AVLTREES_FUNCTIONS_H