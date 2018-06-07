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
    void expansion();
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
        root = tmpNode;
    }

private:
    node root;
};


#endif //POORREVERSI_MCT_H
