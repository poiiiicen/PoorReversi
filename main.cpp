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
    tree.creatMCT(map, false);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}