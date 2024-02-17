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

    Tree<Item> tree;

    tree.insert(One);
    tree.insert(Two);
    tree.insert(Three);
    tree.insert(Four);

    bool hasOneTest = tree.contains(1);
    bool hasTwoTest = tree.contains(2);
    bool hasThreeTest = tree.contains(3);
    bool hasFourTest = tree.contains(4);


    tree.remove(4);




    return 0;
}
