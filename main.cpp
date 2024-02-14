#include <iostream>

#include "node.h"
#include "memory"
#include "item/item.h"
using namespace std;
#include "tests/test2.h"
#include "functions.h"

int main() {

    shared_ptr<Node<Team>> teamRoot = test2();

    cout << teamRoot->getID() << endl;

    inorder<Team>(teamRoot);
    cout << endl;

    cout << "The tree is balanced: " << isBalanced(teamRoot) << endl;
    cout << contains(teamRoot, 27) << endl;
    cout << contains(teamRoot, 20) << endl;


//    Node* tree = test1();
//    cout << endl << "the tree starts off balanced: " << isBalanced(tree) << endl;
//    inorder(tree);
//    cout << endl;
//    //          ***********
//
//    addNode(tree, 27);
//    addNode(tree, 28);
//    inorder(tree);
//
//    cout << endl << endl <<"After adding 27 then 28 the tree stops being balanced: "<< isBalanced(tree) << endl;
//
//    LR(tree->right->right->right);
//    cout << endl << "After performing LR on the problematic node it becomes balanced again: " << isBalanced(tree) << endl;

//    LL(tree->right->right->left);
//    cout << endl << "After performing LL on the problematic node it becomes balanced again: " << isBalanced(tree) << endl;
//    inorder(tree);
//
//    addNode(tree,30);
//    addNode(tree, 31);

//    cout << endl << endl <<"After adding 30 and 31 the tree stops being balanced: "<< isBalanced(tree) << endl;
//    RR(tree->right->right->right);
//    cout << endl << "After performing RR on the problematic node it becomes balanced again: " << isBalanced(tree) << endl;


//    inorder(tree);
    return 0;
}
