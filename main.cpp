#include <iostream>

#include "node.h"
#include "memory"
#include "item/item.h"
using namespace std;
#include "tests/test2.h"
#include "functions.h"
#include "tests/test3Rotations.h"

int main() {
    shared_ptr<Node<Team>> teamRoot = test2();

    inorder<Team>(teamRoot);
    cout << endl;

    cout << "The tree is balanced: " << isBalancedSlowVersion(teamRoot) << endl;

    shared_ptr<Team> team30 = make_shared<Team>(30);
    shared_ptr<Node<Team>> team30Node = make_shared<Node<Team>>(team30);
    addNode(teamRoot, team30Node);
    inorderINFO<Team>(teamRoot);
    cout << endl;
    cout << "The tree is balanced: " << isBalancedSlowVersion(teamRoot) << endl;

    shared_ptr<Team> team31 = make_shared<Team>(18);
    shared_ptr<Node<Team>> team31Node = make_shared<Node<Team>>(team31);
    addNode(teamRoot, team31Node);
    inorderINFO<Team>(teamRoot);
    cout << endl;
    cout << "The tree is balanced: " << isBalancedSlowVersion(teamRoot) << endl;

//
//    shared_ptr<Team> team18 = make_shared<Team>(18);
//    shared_ptr<Node<Team>> team18Node = make_shared<Node<Team>>(team18);
//
//    inorderINFO(teamRoot);
//    cout << endl;
////    addNode(shared_ptr<Node<Team>> teamRoot, shared_ptr<Node<Team>>)
//    addNode(teamRoot, team18Node);
//    inorderINFO(teamRoot);
//    cout << endl;
//    cout << "The tree is balanced: " << isBalancedSlowVersion(teamRoot) << endl;
//
//    inorder<Team>(teamRoot);
//    cout << endl;
//



//    cout << "NEW TEST2 ***********************************" << endl;
//    cout<<endl;
//
//    shared_ptr<Node<Team>> teamRoot = test2();
//    inorderINFO(teamRoot);
//    cout << endl;
//
//    cout << "is balanced = " << isBalancedSlowVersion(teamRoot) << endl;
////    cout << contains(teamRoot, 18) << endl;
//    cout << "ADDING NODE 18" << endl;
//
//    shared_ptr<Team> team18 = make_shared<Team>(18);
//    shared_ptr<Node<Team>> team18Node = make_shared<Node<Team>>(team18);
//
//    addNode(teamRoot, team18Node);
//    inorderINFO(teamRoot);
//    cout << endl;
//
//    cout << "is balanced = " << isBalancedSlowVersion(teamRoot) << endl;
//
//    cout << "performing LL rotation on problematic node" << endl;
//
//
//
//    cout << "is balanced = " << isBalancedSlowVersion(teamRoot) << endl;
//    inorderINFO(teamRoot);
//    cout << endl;
//   cout << "NEW TEST3 ***********************************" << endl;

//    shared_ptr<Node<Team>> ts = test3();
//    inorderINFO(ts);
//    cout << getHeight(ts) << " mmmm " << ts->height << endl;
//    cout << "before rotation" << endl;
//    cout << ts->value << endl;
//    cout << ts->left->value << endl;
//    cout << ts->left->right->value << endl;
//    cout << ts->left->right->right->value << endl;
//    cout << endl;
//    RR(ts->left);
//    cout << ts->value << endl;
//    cout << ts->left->value << endl;
//    cout << ts->left->left->value << endl;
//    cout << ts->left->right->value << endl;


    // TRASHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
//    shared_ptr<Team> team30 = make_shared<Team>(30);
//    shared_ptr<Node<Team>> team30Node = make_shared<Node<Team>>(team30);
//    addNode(teamRoot, team30Node);
//    cout << "The tree is balanced: " << isBalanced(teamRoot) << endl;
//    inorder<Team>(teamRoot);
//    cout << endl;
//    addNode(teamRoot, 27);
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
