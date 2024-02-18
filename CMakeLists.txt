cmake_minimum_required(VERSION 3.23.2)
project(AVLtrees)

set(CMAKE_CXX_STANDARD 11)

#add_executable(AVLtrees main.cpp test1.cpp test1.h functions.h node.h functions.cpp item.cpp item.h)

add_executable(AVLtrees main.cpp   node.h item/item.cpp item/item.h tree.h)
