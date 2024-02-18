#include <iostream>

#include "node.h"
#include "memory"
#include "item/item.h"
#include "tree.h"
using namespace std;

int main() {
    //Test case 1:

    auto One = make_shared<Item>(1);
    auto Two = make_shared<Item>(2);
    auto Three = make_shared<Item>(3);
    auto Four = make_shared<Item>(4);
    auto Five = make_shared<Item>(5);
    auto Six = make_shared<Item>(6);
    auto Seven = make_shared<Item>(7);
    auto Eight = make_shared<Item>(8);
    auto Nine = make_shared<Item>(9);
    auto Ten = make_shared<Item>(10);

    Tree<Item> tree;

    tree.insert(One);
    tree.insert(Two);
    tree.insert(Three);
    tree.insert(Four);
    tree.insert(Five);
    tree.insert(Six);
    tree.insert(Seven);
    tree.insert(Eight);
    tree.insert(Nine);
    tree.insert(Ten);

    bool hasOneTest = tree.contains(1);
    bool hasTwoTest = tree.contains(2);
    bool hasThreeTest = tree.contains(3);
    bool hasFourTest = tree.contains(4);


    tree.remove(4);
    // TODO fix remove's rotation process
    // tree's root is now 5 which is WRONG!! it has to be 3
    // check https://www.cs.usfca.edu/~galles/visualization/AVLtree.html
    // and insert 1,2,3,4,5,6,7,8,9,10 and then remove 4 to see how the tree should look like after removing 4
    // in https://visualgo.net/en/bst?slide=3 our implementation is correct
    // I am still not sure which one is correct
    // will investigate further
    // according to https://visualgo.net/en/bst?slide=3 our implementation seems to be correct


//    ~tree();

    return 0;
}
