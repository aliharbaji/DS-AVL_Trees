#include <iostream>

#include "node.h"
#include "functions.h"
#include "test1.h"

using namespace std;

int main() {
    Node* tree = test1();
    cout << endl << "the tree starts off balanced: " << isBalanced(tree) << endl;
    inorder(tree);
    cout << endl;
    //          ***********

    addNode(tree, 27);
    addNode(tree, 28);
    inorder(tree);

    cout << endl << endl <<"After adding 27 then 28 the tree stops being balanced: "<< isBalanced(tree) << endl;

    LR(tree->right->right->right);
    cout << endl << "After performing LR on the problematic node it becomes balanced again: " << isBalanced(tree) << endl;

//    LL(tree->right->right->left);
//    cout << endl << "After performing LL on the problematic node it becomes balanced again: " << isBalanced(tree) << endl;
//    inorder(tree);
//
//    addNode(tree,30);
//    addNode(tree, 31);

//    cout << endl << endl <<"After adding 30 and 31 the tree stops being balanced: "<< isBalanced(tree) << endl;
//    RR(tree->right->right->right);
//    cout << endl << "After performing RR on the problematic node it becomes balanced again: " << isBalanced(tree) << endl;


    inorder(tree);
    return 0;
}
