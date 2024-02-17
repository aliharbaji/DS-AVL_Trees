cmake_minimum_required(VERSION 3.24)
project(AVLtrees)

set(CMAKE_CXX_STANDARD 11)

#add_executable(AVLtrees main.cpp test1.cpp test1.h functions.h node.h functions.cpp item.cpp item.h)

add_executable(AVLtrees main.cpp   node.h item/item.cpp item/item.h functions.h tree.h Scripts/Olympicsa1.h Scripts/Olympicsa1.cpp item/Country.cpp item/Country.h item/Team.cpp item/Team.h item/Contestant.cpp item/Contestant.h)
