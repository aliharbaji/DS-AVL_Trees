#include <iostream>

#include "node.h"
#include "memory"
#include "item/item.h"
#include "item/Country.h"
#include "item/Team.h"
#include "Scripts/Olympicsa1.h"

#include "functions.h"
using namespace std;
void print(StatusType res) {
    if (res == StatusType::FAILURE) {
        cout << "FAILURE" << endl;
    } else {
        cout << "SUCCESS" << endl;
    }
}
int main() {
    StatusType type;
//    cout << "UNCOMMENT shared_ptr<Country> myCountry; in Team.h to see the error" << endl;
//    cout << "UNCOMMENT shared_ptr<Tree<Country>> allCountries; in Country.h to see the error" << endl;

    //Test case 1:
    Country someCountry(5,2);//testing Country constructor

//    Team someTeam(3, Sport::SWIMMING, make_shared<Country>(someCountry));//testing team Constructor


    Olympics Paris2024;
    Paris2024.add_country(111, 1); // gives a seg fault
    Paris2024.add_country(222, 2);
    Paris2024.add_country(333, 3);

    Paris2024.add_team(1, 111, Sport::SWIMMING);
    Paris2024.add_team(2, 111, Sport::SWIMMING);

//    type = Paris2024.add_team(11, 111, Sport::BOULDERING);
//    print(type);

    Paris2024.add_team(111, 111, Sport::ACROBATICS);

    Paris2024.add_contestant(1, 111, Sport::SWIMMING, 1);
    Paris2024.add_contestant(2, 111, Sport::SWIMMING, 2);
    Paris2024.add_contestant(3, 111, Sport::SWIMMING, 3);
    Paris2024.add_contestant(4, 111, Sport::SWIMMING, 4);

    Paris2024.add_contestant(555, 222, Sport::SWIMMING, 5);

    Paris2024.add_contestant_to_team(1, 1);
    Paris2024.add_contestant_to_team(1, 3);

    Paris2024.add_contestant_to_team(2, 2);
    Paris2024.add_contestant_to_team(2, 4);

    type = Paris2024.add_contestant_to_team(2, 1);
    print(type);

    type = Paris2024.add_contestant_to_team(2, 555);
    print(type);



    // team 11: has: 1, 3
    // team 2: has: 2, 4, 1

    Paris2024.unite_teams(1, 2);
//    Paris2024.get_medals(111);




    //Test case2 for Trees:
//    Tree<Item> tree;

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

//    bool hasOneTest = tree.contains(1);
//    bool hasTwoTest = tree.contains(2);
//    bool hasThreeTest = tree.contains(3);
//    bool hasFourTest = tree.contains(4);
//
//
//
//
//
//    // Test case 2: remove with multiple rotations including at the root
//    auto a1 = make_shared<Item>(50);
//    tree.insert(a1);
//    auto a2 = make_shared<Item>(25);
//    tree.insert(a2);
//    auto a3 = make_shared<Item>(75);
//    tree.insert(a3);
//    auto a4 = make_shared<Item>(15);
//    tree.insert(a4);
//    auto a5 = make_shared<Item>(40);
//    tree.insert(a5);
//    auto a6 = make_shared<Item>(60);
//    tree.insert(a6);
//    auto a7 = make_shared<Item>(80);
//    tree.insert(a7);
//    auto a8 = make_shared<Item>(35);
//    tree.insert(a8);
//    auto a9 = make_shared<Item>(55);
//    tree.insert(a9);
//    auto a10 = make_shared<Item>(65);
//    tree.insert(a10);
//    auto a11 = make_shared<Item>(90);
//    tree.insert(a11);
//    auto a12 = make_shared<Item>(62);
//    tree.insert(a12);
//    tree.remove(15);
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
