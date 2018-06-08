//
// Created by bluejoe on 2018/6/7.
//

#ifndef POORREVERSI_MCT_H
#define POORREVERSI_MCT_H
#include <cmath>
#include <random>
#include "timer.h"
#include "logic.h"
#include "node.h"

class MCT{
public:
    explicit MCT(node r = nullptr):root(r){init();}
    ~MCT() = default;
    void creatMCT(int map[8][8], bool color);
    void updateMCT(int map[8][8]);
private:
    void init(){
        auto tmpNode = new Node;
        tmpNode->win = 0;
        tmpNode->n = 0;
        tmpNode->c = sqrt(2);
        tmpNode->t = 0;
        tmpNode->num = 0;
        tmpNode->space = 64;
        for (auto &i : tmpNode->map)
                for (int &j : i) j = 0;
        for (int i = 0; i < 64; i++) tmpNode->candidate.push_back(i);
        tmpNode->father = nullptr;
        root = tmpNode;
    }
    void initMap(int map[8][8], bool color);
    node selection();
    node expansion(node curNode);
    bool simulation(node curNode);
    void backPropagation(node curNode, bool isWin);
private:
    node root;
    bool treeColor;
    std::default_random_engine random;
    int lunci;
};


#endif //POORREVERSI_MCT_H
