#include <iostream>

#include "node.h"
#include "memory"
#include "item/item.h"
#include "tree.h"
using namespace std;

int main() {
    //Test case 1:
/*
    auto One = make_shared<Item>(1);
    auto Two = make_shared<Item>(2);
    auto Three = make_shared<Item>(3);
    auto Four = make_shared<Item>(4);

    Tree<Item> tree;

    tree.insert(One);
    tree.insert(Two);
    tree.insert(Three);
    tree.insert(Four);

    bool hasOneTest = tree.contains(1);
    bool hasTwoTest = tree.contains(2);
    bool hasThreeTest = tree.contains(3);
    bool hasFourTest = tree.contains(4);


    tree.remove(2);
    hasTwoTest = tree.contains(2);
*/


    Tree<Item> tree;
    /* Test case 2: remove with multiple rotations including at the root
    auto a1 = make_shared<Item>(50);
    tree.insert(a1);
    auto a2 = make_shared<Item>(25);
    tree.insert(a2);
    auto a3 = make_shared<Item>(75);
    tree.insert(a3);
    auto a4 = make_shared<Item>(15);
    tree.insert(a4);
    auto a5 = make_shared<Item>(40);
    tree.insert(a5);
    auto a6 = make_shared<Item>(60);
    tree.insert(a6);
    auto a7 = make_shared<Item>(80);
    tree.insert(a7);
    auto a8 = make_shared<Item>(35);
    tree.insert(a8);
    auto a9 = make_shared<Item>(55);
    tree.insert(a9);
    auto a10 = make_shared<Item>(65);
    tree.insert(a10);
    auto a11 = make_shared<Item>(90);
    tree.insert(a11);
    auto a12 = make_shared<Item>(62);
    tree.insert(a12);
    tree.remove(15);
*/

/*
    auto a1 = make_shared<Item>(2);
    tree.insert(a1);
    auto a2 = make_shared<Item>(4);
    tree.insert(a2);
    auto a3 = make_shared<Item>(3);
    tree.insert(a3);
*/

    return 0;
}
