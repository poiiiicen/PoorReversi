#include <iostream>
#include "MCT.h"


int main() {
    MCT tree;

    tree.initMap();

    node curNode;
    curNode = tree.selection();
    curNode = tree.expansion(curNode);
    tree.backPropagation(curNode, tree.simulation(curNode));
    std::cout << "Hello, World!" << std::endl;
    return 0;
}