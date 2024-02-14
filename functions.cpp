#include "functions.h"
#include "iostream"


int getHeight(Node* root){
    if(root == nullptr) return 0;
    int R = getHeight(root->right);
    int L = getHeight(root->left);
    return 1 + std::max(R, L);
}

bool isBalanced(Node *root){
    if(root == nullptr) return true;
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    if(std::abs(leftHeight - rightHeight) > 1) return false;
    return isBalanced(root->left) && isBalanced(root->right);
}

bool contains(Node* root, int val){
    if(root == nullptr) return false;
    if(root->value == val) return true;
    if(root->value < val){
        return contains(root->right, val);
    }else{
        return contains(root->left, val);
    }
}

void print(Node *root){
    if(root == nullptr) return;
    cout << root->value << " ";
}

void printInfo(Node *root){
    if(root == nullptr) return;
    cout << "v: " << root->value << " h: " << root->height << " ";
}
void addAux(Node* root, int val) {
    if (root == nullptr) {
        root = new Node();
        root->value = val;
        return;
    }

    if (val < root->value) {
        if (root->left == nullptr) {
            root->left = new Node();
            root->left->value = val;
            root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
        } else {
            addAux(root->left, val);
        }
    } else if (val > root->value) {
        if (root->right == nullptr) {
            root->right = new Node();
            root->right->value = val;
            root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
        } else {
            addAux(root->right, val);
        }
    }
}

void addNode(Node* root, int val){
    if(contains(root, val)) return;
    addAux(root, val);
}

void inorder(Node* root){
    if (root == nullptr) return;
    inorder(root->left);
    print(root);
    inorder(root->right);
}

void inorderINFO(Node* root){
    if (root == nullptr) return;

    inorder(root->left);
    printInfo(root);
    inorder(root->right);
}

void swapFields(Node* n1, Node* n2){
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
void LL(Node* root){
    Node* newRoot = root->left; // A
    Node* tempL = newRoot->left; // AL
    Node* tempR = newRoot->right; // AR
    swapFields(root, newRoot); // A <-> B


    root->left = tempL;
    newRoot->right = root->right;
    newRoot->left = tempR;
    root->right = newRoot;

}

void RR(Node* root){
    Node* newRoot = root->right; // A
    Node* tempL = newRoot->left; // AL
    Node* tempR = newRoot->right; // AR
    swapFields(root, newRoot); // A <-> B

    root->right = tempR;
    newRoot->left = root->left;
    newRoot->right = tempL;
    root->left = newRoot;
}

void LR(Node* root){
    Node* tempL = root->left;
    Node* tempR = root->right;
    Node* tempLR = root->left->right;
    swapFields(root, tempLR);

    root->right = tempLR;
    Node* tempLRL = root->left->right->left;
    Node* tempLRR = root->left->right->right;
    tempLR->right = tempR;
    tempLR->left = tempLRR;
    tempL->right = tempLRL;
}