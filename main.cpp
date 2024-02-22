#include <iostream>

#include "node.h"
#include "memory"
#include "item/item.h"
#include "item/Country.h"
#include "item/Team.h"
#include "Scripts/Olympicsa1.h"

#include "functions.h"
using namespace std;

int main() {

//    cout << "UNCOMMENT shared_ptr<Country> myCountry; in Team.h to see the error" << endl;
//    cout << "UNCOMMENT shared_ptr<Tree<Country>> allCountries; in Country.h to see the error" << endl;

    //Test case 1:
    Country someCountry(5,2);//testing Country constructor
    Team someTeam(3, Sport::SWIMMING, make_shared<Country>(someCountry));//testing team Constructor


    Olympics Paris2024;
    Paris2024.add_country(777, 1); // gives a seg fault
//    Paris2024.add_country(2, 2);
//    Paris2024.add_country(3, 3);


    //Test case2:
    Tree<Item> tree;

//    tree.insert(One);
//    tree.insert(Two);
//    tree.insert(Three);
//    tree.insert(Four);
//    tree.insert(Five);
//    tree.insert(Six);
//    tree.insert(Seven);
//    tree.insert(Eight);
//    tree.insert(Nine);
//    tree.insert(Ten);

    bool hasOneTest = tree.contains(1);
    bool hasTwoTest = tree.contains(2);
    bool hasThreeTest = tree.contains(3);
    bool hasFourTest = tree.contains(4);





    // Test case 2: remove with multiple rotations including at the root
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
    // testing functions

    // 50,25,75,15,40,60,80,35,55,65,90,62

//    // make root and size public fields for this to work
//    cout << isBalancedSlowVersion(tree.root) << endl;
//    cout << tree.size << endl;
//    tree.remove(15);
//    cout << tree.size << endl;
//    cout << isBalancedSlowVersion(tree.root) << endl;
//    inorder(tree.root);


//    ~tree();

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
