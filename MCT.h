//
// Created by bluejoe on 2018/6/7.
//

#ifndef POORREVERSI_MCT_H
#define POORREVERSI_MCT_H
#include <cmath>
#include "logic.h"
#include "node.h"

class MCT{
public:
    explicit MCT(node r = nullptr):root(r){init();}
    ~MCT() = default;
    void initMap();
    node selection();
    node expansion(node curNode);
    bool simulation(node curNode);
    void backPropagation(bool isWin);
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
        root = tmpNode;
    }

private:
    node root;
};


#endif //POORREVERSI_MCT_H
