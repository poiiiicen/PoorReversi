#include <iostream>
#include "MCT.h"

void initmap(){

}

int main() {
    MCT tree;

    initmap();

    node curNode;
    curNode = tree.selection();
    tree.expansion(curNode);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}