//
// Created by bluejoe on 2018/6/7.
//
#include "MCT.h"

node MCT::selection()
{
    node curNode = this->root;
    while(curNode->num) {
        double max = 0;
        auto maxNode = new Node;
        for (auto tmpNode : curNode->Next) {
            double tmpVal;
            tmpVal = tmpNode->win * 1.0 / tmpNode->n + tmpNode->c * (log(tmpNode->t) / tmpNode->n);
            if (max < tmpVal) {
                max = tmpVal;
                maxNode = tmpNode;
            }
        }
        curNode = maxNode;
    }
    return curNode;
}

void MCT::expansion()
{

}

void MCT::simulation()
{

}

void MCT::backpropagation()
{

}