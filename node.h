//
// Created by bluejoe on 2018/6/7.
//

#ifndef POORREVERSI_NODE_H
#define POORREVERSI_NODE_H
#include <vector>

typedef struct Node* node;
struct Node
{
    int win;   //win times
    int n;     //total times
    double c;  //const
    int t;     //sum of total times

    int num;   //number of sons
    std::vector<node> *Next; //point to the son node
};

#endif //POORREVERSI_NODE_H
