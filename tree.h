//
// Created by allih on 15/02/2024.
//
#include "node.h"
#include <stdexcept>

#ifndef AVLTREES_TREE_H
template <typename T>

class Tree{
    template <typename U> friend class Node;

private:
    shared_ptr<Node<T>> root;
    int size;

    //The recursion takes an insertion node as an argument and returns the root of the subtree which may or may not change depending on insert location.
    shared_ptr<Node<T>> insertRecursively(shared_ptr<Node<T>> node, shared_ptr<T> item){
        if (node == nullptr) return make_shared<Node<T>>(item);

        if (item->getID() < node->getID()){
            auto leftChild = insertRecursively(node->left, item);
            node->left = leftChild;
            if (leftChild) leftChild->parent=node;

        }
        else if (item->getID() > node->getID()){
            auto rightChild = insertRecursively(node->right, item);
            node->right=rightChild;
            if (rightChild) rightChild->parent=node;
        }
        else throw logic_error("Trying to insert a duplicate after duplication was ruled out");

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        //Left-Left Heavy. We rotate the left child to the right swapping its place with the current node.
        if (balance > 1 && getBalance(node->left) >= 1){
            return rightRotate(node);
        }
        //RR
        else if (balance < -1 && getBalance(node->right) <= -1){
            return leftRotate(node);
        }

        //Left-Right Heavy. We rotate the left subtree to the left, then we rotate the current tree to the right.
        else if (balance > 1 && getBalance(node->left) <= -1){
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        //RL
        else if (balance < - 1 && getBalance(node->right) >= 1){
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;

        }

    void deleteRecursively(shared_ptr<Node<T>>& node, int ID){
        if (node == nullptr) return;
        if (ID < node->getID()) deleteRecursively(node->left, ID);
        else if (ID > node->getID()) deleteRecursively(node->right, ID);

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
               deleteRecursively(node->right, minNode->getID());
            }


        }

        if (node==nullptr) return;

        node->height = 1 + max(getHeight(node->right), getHeight(node->left));
        int balance = getBalance(node);

        //Left-Left Heavy. We rotate the left child to the right swapping its place with the current node.
        if (balance > 1 && getBalance(node->left) >= 1){
            node = rightRotate(node);
        }
            //RR
        else if (balance < -1 && getBalance(node->right)){
            node = leftRotate(node);
        }

            //Left-Right Heavy. We rotate the left subtree to the left, then we rotate the current tree to the right.
        else if (balance > 1 && getBalance(node->left) <= -1){
            node->left = leftRotate(node->left);
            node = rightRotate(node);
        }
            //RL
        else if (balance < - 1 && getBalance(node->right) >= 1){
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


    bool containsRecursively(shared_ptr<Node<T>> rootNode, int ID) const{
        if (rootNode == nullptr) return false;
        if (rootNode->data->getID() == ID) return true;
        if (ID < rootNode->data->getID()) return containsRecursively(rootNode->left, ID);
        else return containsRecursively(rootNode->right, ID);
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
    int getBalance(shared_ptr<Node<T>> node) const{
        if (node == nullptr) return -1;
        else return node->getBF();
    }


public:

    Tree() : root(nullptr), size(0){}
    Tree(const Tree&) = delete;
    Tree& operator=(const Tree&)= delete;

    bool contains(const int ID) const{
        return containsRecursively(root, ID);
    }

    // Inserts item. Returns false in case of duplication. True otherwise.
    bool insert(shared_ptr<T> item){
        if (contains(item->getID())) return false;
        try {
            root=insertRecursively(root, item);
        }
        catch(const bad_alloc& e){
         //Need to manage this exception in the olympics class.
        }
        size++;
        return true;
    }

    bool remove(const int ID){
        if (!contains(ID) || root == nullptr) return false;
        deleteRecursively(root, ID);
        size--;
        return true;
    }

};
#define AVLTREES_TREE_H

#endif //AVLTREES_TREE_H
