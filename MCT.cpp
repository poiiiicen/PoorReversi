//
// Created by bluejoe on 2018/6/7.
//
#include "MCT.h"

node MCT::selection(MCT tree)
{
    node maxNode = tree.root;
    while(maxNode->num) {
        double max = 0;
        for (auto tmpNode : tree.root->Next) {
            double tmpVal;
            tmpVal = tmpNode->win * 1.0 / tmpNode->n + tmpNode->c * (log(tmpNode->t) / tmpNode->n);
            if (max < tmpVal) {
                max = tmpVal;
                maxNode = tmpNode;
            }
        }
    }
    return maxNode;
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