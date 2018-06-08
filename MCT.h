//
// Created by bluejoe on 2018/6/7.
//

#ifndef POORREVERSI_MCT_H
#define POORREVERSI_MCT_H
#include <cmath>
#include "node.h"

class MCT{
public:
    MCT(node r = nullptr):root(r){init();}
    ~MCT() = default;
    node selection();
    void expansion(node curNode);
    void simulation();
    void backpropagation();
private:
    void init(){
        auto tmpNode = new Node;
        tmpNode->win = 0;
        tmpNode->n = 0;
        tmpNode->c = sqrt(2);
        tmpNode->t = 0;
        tmpNode->num = 0;
        tmpNode->space = 64;
        root = tmpNode;
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++) tmpNode->map[i][j] = 0;
    }

private:
    node root;
};


#endif //POORREVERSI_MCT_H
