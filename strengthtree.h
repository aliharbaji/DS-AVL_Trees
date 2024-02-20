//
// Created by omar_ on 18/02/2024.
//

#ifndef AVLTREES_STRENGTHTREE_H
#define AVLTREES_STRENGTHTREE_H
//
// Created by allih on 15/02/2024.
//
#include "node.h"
#include <stdexcept>
#include <vector>


template <typename T>

class STree{
    template <typename U> friend class Node;
private:
    shared_ptr<Node<T>> root;
    int size;
    bool miniTree;
    shared_ptr<Node<T>> maximum;
    shared_ptr<Node<T>> minimum;
    //Adjusted logic to compare based on strength and in case of strength equality to compare based on ID.
    shared_ptr<Node<T>> insertRecursively(shared_ptr<Node<T>> node, shared_ptr<T> item){
        if (node == nullptr) return make_shared<Node<T>>(item);

        bool isLeft = false, isRight = false;

        if (item->getStrength() < node->getStrength() ||
            (item->getStrength() == node->getStrength() && item->getID() < node->getID())) {
            isLeft = true;
        }

        else if (item->getStrength() > node->getStrength() ||
                   (item->getStrength() == node->getStrength() && item->getID() > node->getID())) {
            isRight = true;
        }

        if (isLeft){
            auto leftChild = insertRecursively(node->left, item);
            node->left = leftChild;
            if (leftChild) leftChild->parent=node;

        }
        else if (isRight){
            auto rightChild = insertRecursively(node->right, item);
            node->right=rightChild;
            if (rightChild) rightChild->parent=node;
        }
        else throw logic_error("Trying to insert a duplicate after duplication was ruled out");

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        //Rotation logic stays the same
        if (balance > 1 && getBalance(node->left) >= 0){
            return rightRotate(node);
        }
            //RR
        else if (balance < -1 && getBalance(node->right) <= 0){
            return leftRotate(node);
        }

            //Left-Right Heavy. We rotate the left subtree to the left, then we rotate the current tree to the right.
        else if (balance > 1 && getBalance(node->left) < 0){
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
            //RL
        else if (balance < - 1 && getBalance(node->right) > 0){
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;

    }

    //delete now searches based on strength and ID
    void deleteRecursively(shared_ptr<Node<T>>& node, int ID, int strength){
        if (node == nullptr) return;

        bool isLeft = false, isRight = false;

        if (strength < node->getStrength() ||
            (strength == node->getStrength() && ID < node->getID())) {
            isLeft = true;
        }

        else if (strength > node->getStrength() ||
                 (strength == node->getStrength() && ID > node->getID())) {
            isRight = true;
        }

        if (isLeft) deleteRecursively(node->left, strength, ID);
        else if (isRight) deleteRecursively(node->right, strength, ID);

            // found the node
        else{
            // node has 1 or fewer children
            if (node->right == nullptr || node->left == nullptr){
                auto child = (node->left == nullptr) ? node->right : node->left;
                // no child case
                if (child == nullptr){
                    if (node->parent != nullptr) {
                        if (node->parent->left == node) node->parent->left = nullptr;
                        else if (node->parent->right == node) node->parent->right = nullptr;
                    }
                    node = nullptr;
                }
                    // 1 child case
                else{
                    child->parent = node->parent;
                    if (node->parent != nullptr) {
                        if (node->parent->left == node) node->parent->left = child;
                        else node->parent->right = child;
                    }
                    node = child;

                    /* probably incorrect approach
                    node->data = child->data;
                    node->left = child->left;
                    node->right = child->right;
                    if (node->left) node->left->parent = node;
                    if (node->right) node->right->parent = node; */
                }
            }
                // 2 child case
            else{
                // find the smallest child in the right subtree to become new root
                auto minNode = getMinNode(node->right);
                node->data = minNode->data;
                deleteRecursively(node->right, minNode->getID(), minNode->getStrength());
            }


        }

        if (node==nullptr) return;

        node->height = 1 + max(getHeight(node->right), getHeight(node->left));
        int balance = getBalance(node);

        //Left-Left Heavy. We rotate the left child to the right swapping its place with the current node.
        if (balance > 1 && getBalance(node->left) >= 0){
            node = rightRotate(node);
        }
            //RR
        else if (balance < -1 && getBalance(node->right) <= 0){
            node = leftRotate(node);
        }

            //Left-Right Heavy. We rotate the left subtree to the left, then we rotate the current tree to the right.
        else if (balance > 1 && getBalance(node->left) < 0){
            node->left = leftRotate(node->left);
            node = rightRotate(node);
        }
            //RL
        else if (balance < - 1 && getBalance(node->right) > 0){
            node->right = rightRotate(node->right);
            node = leftRotate(node);
        }


    }



    shared_ptr<Node<T>> rightRotate(shared_ptr<Node<T>> node){
        auto leftChild = node->left;
        auto subTree = leftChild->right;
        //rotating
        leftChild->right = node;
        node->left = subTree;

        node->height = 1 + max(getHeight(node->left),getHeight(node->right));
        leftChild->height = 1 + max(getHeight(leftChild->left), getHeight(leftChild->right));

        if (subTree != nullptr) subTree->parent = node;
        leftChild->parent = node->parent;
        node->parent = leftChild;

        // returning the new root.
        return leftChild;

    }

    shared_ptr<Node<T>> leftRotate(shared_ptr<Node<T>> node){
        auto rightChild = node->right;
        auto subTree = rightChild->left;
        //rotating
        rightChild->left = node;
        node->right = subTree;

        node->height = 1 + max(getHeight(node->left),getHeight(node->right));
        rightChild->height = 1 + max(getHeight(rightChild->left), getHeight(rightChild->right));

        if (subTree != nullptr) subTree->parent = node;
        rightChild->parent = node->parent;
        node->parent = rightChild;

        // returning the new root.
        return rightChild;

    }


    bool containsRecursively(shared_ptr<Node<T>> node, int ID, int strength) const{
        if (node == nullptr) return false;
        bool isLeft = false;

        if (strength < node->getStrength() ||
            (strength == node->getStrength() && ID < node->getID())) {
            isLeft = true;
        }

        if (node->getID() == ID) return true;
        if (isLeft) return containsRecursively(node->left, ID);
        else return containsRecursively(node->right, ID);
    }

    shared_ptr<T> findRecursively(shared_ptr<Node<T>> node, int ID, int strength) const{
        if (node == nullptr) return nullptr;

        bool isLeft = false;
        if (strength < node->getStrength() ||
            (strength == node->getStrength() && ID < node->getID())) {
            isLeft = true;
        }

        if (node->data->getID() == ID) return node->data;
        if (isLeft) return findRecursively(node->left, ID);
        else return findRecursively(node->right, ID);
    }

    int getHeight(shared_ptr<Node<T>> node) const{
        if (node == nullptr) return -1;
        else return node->height;
    }

    shared_ptr<Node<T>> getMinNode(shared_ptr<Node<T>> node){
        auto current = node;
        while (current->left != nullptr){
            current = current->left;
        }
        return current;
    }
    shared_ptr<Node<T>> getMaxNode(shared_ptr<Node<T>> node){
        auto current = node;
        while (current->right != nullptr){
            current = current->right;
        }
        return current;
    }

    int getBalance(shared_ptr<Node<T>> node) const{
        if (node == nullptr) return -1;
        else return node->getBF();
    }


public:

    explicit STree(bool miniTree = false) : root(nullptr), size(0), miniTree(miniTree), maximum(nullptr), minimum(nullptr){}
    STree(const STree&) = delete;
    STree& operator=(const STree&)= delete;


    // finds member with ID, returns NULL if he doesn't exist.
    shared_ptr<T> find(const int ID) const{
        return findRecursively(root, ID);
    }

    //TODO: adapt contain and find to strength. Probably unecessary because we should check for duplication before insertion into STree.
    bool contains(const int ID) const{
        return containsRecursively(root, ID);
    }

    // Inserts item. Returns false in case of duplication. True otherwise.
    bool insert(shared_ptr<T> item){
        try {
            root = insertRecursively(root, item);
        }
        catch(const bad_alloc& e){
            //Need to manage this exception in the olympics class.
        }
        size++;
        minimum = getMinNode(root);
        maximum = getMaxNode(root);
        return true;
    }

    bool remove(const int ID, const int strength){
        if (!size) return false;
        deleteRecursively(root, ID, strength);
        size--;
        minimum = getMinNode(root);
        maximum = getMaxNode(root);
        return true;
    }

    shared_ptr<T> getMax(){
        if (size) return maximum->data;
        else return nullptr;
    }

    shared_ptr<T> getMin(){
        if (size) return minimum->data;
        else return nullptr;
    }

    // function that returns a vector of the maximum members in the tree in decreasing order. Reverse inorder traversal.
    vector<shared_ptr<T>> getMaxN(int n) const{
        if (n > size) throw invalid_argument("argument is bigger than container");
        vector<shared_ptr<T>> result;

        auto current = maximum;
        while (current != nullptr && n > 0) {
            result.push_back(current->data);
            n--;

            if (current->left != nullptr) {
                current = current->left;
                while (current->right != nullptr) {
                    current = current->right;
                }
            } else {
                while (current->parent != nullptr && current == current->parent->left) {
                    current = current->parent;
                }
                current = current->parent;
            }
        }
        return result;
    }

    vector<shared_ptr<T>> getMinN(int n) const{
        if (n > size) throw invalid_argument("argument is bigger than container");
        vector<shared_ptr<T>> result;
        auto current = minimum;
        while (current != nullptr && n > 0) {
            result.push_back(current->data);
            n--;

            if (current->right != nullptr) {
                current = current->right;
                while (current->left != nullptr) {
                    current = current->left;
                }
            } else {
                while (current->parent != nullptr && current == current->parent->right) {
                    current = current->parent;
                }
                current = current->parent;
            }
        }
        return result;
    }

    int getSize(shared_ptr<Node<T>> node) const {
        return node ? node->size : 0; // Return 0 if node is nullptr, otherwise node's size
    }





};



#endif //AVLTREES_STRENGTHTREE_H
