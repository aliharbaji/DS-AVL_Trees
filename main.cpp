#include <iostream>

#include "node.h"
#include "memory"
#include "item/item.h"
using namespace std;
#include "tests/test2.h"
#include "functions.h"
#include "tests/test3Rotations.h"
#include "tree.h"

int main() {
//    shared_ptr<Node<Team>> root;

//    insert(root, 10);
//    insert(root, 20);
//    insert(root, 30);
//    inorderINFO(root->parent);
//    cout << endl;
//    Tree<Team> t;
//    shared_ptr<Team> team10 = make_shared<Team>(10);
//    shared_ptr<Team> team20 = make_shared<Team>(20);
//    shared_ptr<Team> team30 = make_shared<Team>(30);
//    t.insert(team10);
//    t.insert(team20);
//    inorderINFO(t.root);
//    cout << endl;


//    t.insert(team30); // this makes the tree unbalanced and should perform RR on tree.root
//
//    cout << "we must update tree.root to the new root of the tree after performing rotations" << endl;
//    cout <<  t.root->value << ", left - >";
//    cout <<  t.root->left->value << endl;
//    cout << t.root->left->value << " left - >" << t.root->value << " right - >" << t.root->right->value << endl;
//    inorderINFO(t.root); // this is the problem
//    cout << endl;
////    cout << root->right->value << endl;
//    cout << "The tree is balanced: " << isBalancedSlowVersion(t.root) << endl;
//    cout << "fixed many of the issues with the rotations, but need to fix the problem in this test" << endl;
//    cout << "if we create a שרוך with 3 nodes the tree becomes unbalanced, and to fix we perform an RR rotation" << endl;
//    cout << "the problem that arises is that the pointer root stops pointing to the root of the tree" << endl;
//    cout << "and instead points to the left child of the root" << endl;
//    cout << "this is a problem because the root of the tree is not updated" << endl;
//    cout << "the solution is to return the new root of the tree from the rotation functions" << endl;

//    shared_ptr<Node<Team>> teamRoot = test2();
//    inorder<Team>(teamRoot);
//    inorder<Team>(teamRoot);
//    cout << endl;
//
//    cout << "The tree is balanced: " << isBalancedSlowVersion(teamRoot) << endl;
//    cout << endl;
//
//
//    shared_ptr<Team> team18 = make_shared<Team>(18);
//    shared_ptr<Node<Team>> team18Node = make_shared<Node<Team>>(team18);
//    addNode(teamRoot, team18Node);
//    inorderINFO<Team>(teamRoot);
//    cout << endl;
//    cout << "The tree is balanced: " << isBalancedSlowVersion(teamRoot) << endl;
//    cout << teamRoot->right->right->left->value << endl;
//    cout << teamRoot->right->right->left->right->value << endl;
////    cout << teamRoot->right->right->left->left->right->value << endl;
//    cout << endl;
//    cout << endl;
//    cout << "HEIGHT OF n:20 should be 0 and not 2 after LL rotation!!, check example from lecture!!!" << endl;
//    cout << "The error has something to do with updating heights correctly " << endl;
//    cout << "The tree is balanced: " << isBalancedSlowVersion(teamRoot) << endl;
//    cout << "the height of node 24 should be 2, but it is " << teamRoot->right->right->height << endl;
//    cout << "this is the height of the right child of node 24: " << teamRoot->right->right->right->height << endl;
//    cout << "this is the height of the left child of node 24: " << teamRoot->right->right->left->height << endl;
//    cout << "the left child of node 24 is correct and is " << teamRoot->right->right->left->value << endl;
//    cout << "its height is " << teamRoot->right->right->left->height << endl;
//    cout << "now it works but LL's implementation seems weird and maybe only works for this case" << endl;
//    cout << "check TODO comments in LL function" << endl;
//
//    inorderINFO<Team>(teamRoot);
//    cout << endl;
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
////



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
//
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
//    inorderINFO(ts);

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
