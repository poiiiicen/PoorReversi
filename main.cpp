#include <iostream>
#include <fstream>
#include "MCT.h"

int map[8][8];

int main() {
    std::ifstream in("in.txt");
    for (auto &i : map)
        for (int &j : i)
            in >> j;
    MCT tree;
    tree.createMCT(false);
    tree.updateMCT(map);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}