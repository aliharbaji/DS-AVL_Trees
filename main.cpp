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
    } else if(res == StatusType::SUCCESS){
        cout << "SUCCESS" << endl;
    }else if(res == StatusType::INVALID_INPUT){
        cout << "INVALID_INPUT" << endl;
    }
}


int main() {

    Tree<Country> emptyTree;
    emptyTree.makeEmptyCompleteTree(6);

    cout << "emptyTree size: " << emptyTree.getSize() << endl;


    Tree<Country> tree;
    shared_ptr<Country> c1 = make_shared<Country>(1, 1);
    shared_ptr<Country> c2 = make_shared<Country>(2, 2);
    shared_ptr<Country> c3 = make_shared<Country>(3, 3);
    shared_ptr<Country> c4 = make_shared<Country>(4, 4);
    shared_ptr<Country> c5 = make_shared<Country>(5, 5);

    tree.insert(c1);
    tree.insert(c2);
    tree.insert(c3);
    tree.insert(c4);
    tree.insert(c5);

    auto a1 = tree.returnSortedArrayOfElements();

    for (int i = 0; i < 5; i++) {
        cout << a1[i]->getID() << endl;
    }
    cout << "the function returnSortedArrayOfElements works" << endl;
    return 0;



    StatusType type;
//    cout << "UNCOMMENT shared_ptr<Country> myCountry; in Team.h to see the error" << endl;
//    cout << "UNCOMMENT shared_ptr<Tree<Country>> allCountries; in Country.h to see the error" << endl;

    //Test case 1:
    //testing Country constructor

//    Team someTeam(3, Sport::SWIMMING, make_shared<Country>(someCountry));//testing team Constructor


    Olympics Paris2024;
    Paris2024.add_country(111, 1); // gives a seg fault
    Paris2024.add_country(222, 2);
    Paris2024.add_country(333, 3);


    /*
    Paris2024.add_team(1, 111, Sport::SWIMMING);
    Paris2024.add_team(2, 111, Sport::SWIMMING);


    Paris2024.add_contestant(1, 111, Sport::SWIMMING, 1);
    Paris2024.add_contestant(2, 111, Sport::SWIMMING, 2);
    Paris2024.add_contestant(3, 111, Sport::SWIMMING, 3);
    Paris2024.add_contestant(4, 111, Sport::SWIMMING, 4);

   print(Paris2024.add_contestant(555, 222, Sport::SWIMMING, 5));

    Paris2024.add_contestant_to_team(1, 1);
    Paris2024.add_contestant_to_team(1, 3);

    Paris2024.add_contestant_to_team(2, 2);
    Paris2024.add_contestant_to_team(2, 4);

    Paris2024.add_contestant_to_team(2, 1);
//    type = Paris2024.add_contestant_to_team(2, 1);
//    print(type);
//
//    type = Paris2024.add_contestant_to_team(2, 3);
//    print(type);

    auto teamStrength = Paris2024.get_team_strength(2);
    Paris2024.printTeam(1);
    Paris2024.printTeam(2);

    // team 11: has: 1, 3
    // team 2: has: 2, 4

    Paris2024.unite_teams(1, 2); // team 1 should now have players 1, 3, 2, 4
//    return 0;
    Paris2024.printTeam(2);
    cout << "UNITED TEAM 1 AND 2" << endl;
    Paris2024.printTeam(1);

    cout << "Paris 2024 stops containing team 2, this function shouldn't print anything " << endl;
    Paris2024.printTeam(2);

    Paris2024.remove_team(1);
    cout << "tryting to remove team 1, but it won't be removed because it still "
            "contains contestants, this function should print team1's info " << endl;
    Paris2024.printTeam(1);

    cout << "removing contestant 1 from team 1" << endl;
    Paris2024.remove_contestant_from_team(1, 1);
    cout << "now team 1 should only contain 3, 2, 4" << endl;
    Paris2024.printTeam(1);
    cout << "ADD BREAKPOINT HERE AND OPEN DEBUGGER" << endl;
    cout << "GO TO PARIS2024 AND LOOK AT ITS ONLY TEAM, TEAM 1 " << endl;
    cout << "TEAM1 CORRECTLY CONTAINS CONTESTANTS 3, 2, 4" << endl;
    cout << "LOWERID MIDDLEID AND HIGHERID ARE CORRECTLY UPDATED" << endl;
    cout << "TEAM1'S LOWERSTRTREE AND MIDDLE AND HIGHER CONTAIN 0 ELEMENTS (THEY SHOULD CONTAIN 1 EACH)" << endl;

    cout << "team1's strength shouldn't be 0 and should be calculated properly" << endl;
    cout << "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999" << endl;
//    cout << Paris2024.get_team_strength(1).ans() << endl;
//    Paris2024.printTeam(1);
    cout << endl;
    cout << "*****************LOGIC ERROR*****************" << endl;
    cout << "team 1's strength should be 9" << endl;
    */

//    cout<< "testing the example in the PDF for get_team_strength and get_aus_measure"<<endl;
    Paris2024.add_team(3, 333, Sport::SWIMMING);
    Paris2024.add_contestant(1, 333, Sport::SWIMMING, 2);
    Paris2024.add_contestant(4, 333, Sport::SWIMMING, 5);
    Paris2024.add_contestant(6, 333, Sport::SWIMMING, 3);
    Paris2024.add_contestant(10, 333, Sport::SWIMMING, 10);
    Paris2024.add_contestant(16, 333, Sport::SWIMMING, 11);
    Paris2024.add_contestant(20, 333, Sport::SWIMMING, 15);
    Paris2024.add_contestant(100, 333, Sport::SWIMMING, 7);
    Paris2024.add_contestant(101, 333, Sport::SWIMMING, 6);
    Paris2024.add_contestant(102, 333, Sport::SWIMMING, 4);

    Paris2024.add_contestant_to_team(3, 1);
    Paris2024.add_contestant_to_team(3, 4);
    Paris2024.add_contestant_to_team(3, 6);
    Paris2024.add_contestant_to_team(3, 10);
    Paris2024.add_contestant_to_team(3, 16);
    Paris2024.add_contestant_to_team(3, 20);
    Paris2024.add_contestant_to_team(3, 100);
    Paris2024.add_contestant_to_team(3, 101);
    Paris2024.add_contestant_to_team(3, 102);

    cout<<"get team strength = ";
    cout<<Paris2024.get_team_strength(3).ans()<<endl;
    cout<<"get aus measure = ";
    cout<<Paris2024.austerity_measures(3).ans()<<endl;





    return 0;

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

    // Test from whatsapp regarding adding and removing countries
     Olympics olympus;
     cout <<"------------------------------------"<<endl;
    // trying successful things.
    std::cout << "These should print-out SUCCESS" << '\n';
    print(olympus.add_country(1,1)); // canada
    print(olympus.add_country(40,2)); // romania
    print(olympus.add_country(972,3)); // israel
    print(olympus.add_country(44,4)); // uk
    print(olympus.add_country(46,5)); // sweden
    print(olympus.add_country(7,6)); // russia
    print(olympus.add_country(39,0)); // italy
    cout <<"------------------------------------"<<endl;
    // trying invalid input.
    std::cout << "These should print-out INVALID_INPUT" << '\n';
    print(olympus.add_country(-2,0)); // negative country id
    print(olympus.add_country(39,-1)); // neaative medals
    print(olympus.add_country(0,0)); // null_id
    cout <<"------------------------------------"<<endl;
    // trying failure
    std::cout << "These should print-out FAILURE" << '\n';
    print(olympus.add_country(39,0)); // italy again
    cout <<"------------------------------------"<<endl;
    cout << "Medal Counts" << endl;
    // trying to get medal count successfully
    output_t<int> value = olympus.get_medals(1);
    std::cout << '(' << (int)value.status() << ',' << value.ans() << ')' << "\n";
    output_t<int> value2 = olympus.get_medals(972);
    std::cout << '(' << (int)value2.status() << ',' << value2.ans() << ')' << "\n\n";
    // trying invalid input
    output_t<int> value3 = olympus.get_medals(0); // null id
    std::cout << '(' << (int)value3.status() << ',' << value3.ans() << ')' << "\n\n";
    // trying failure
    output_t<int> value4 = olympus.get_medals(54); // argentina
    std::cout << '(' << (int)value4.status() << ',' << value4.ans() << ')' << "\n\n";
    cout <<"------------------------------------"<<endl;
    cout << "Removing countries (SUCCESS)" << endl;
    // trying to remove successfully
    print(olympus.remove_country(7)); // russia
    print(olympus.remove_country(39)); // italy
    print(olympus.remove_country(40)); // romania
    cout <<"------------------------------------"<<endl;
    // trying invalid input
    cout << "Removing countries (INVALID_INPUT)" << endl;
    print(olympus.remove_country(-7)); // negative country id
    print(olympus.remove_country(0)); // null id
    cout <<"------------------------------------"<<endl;

    // trying failure
    cout << "Removing countries (FAILURE)" << endl;
    print(olympus.remove_country(7)); // russia again (supposed to be removed already)
    print(olympus.remove_country(254)); // kenya
    print(olympus.remove_country(359)); // bulgaria
    cout <<"------------------------------------"<<endl;
    return 0;
}
