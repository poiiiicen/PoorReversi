//
// Created by bluejoe on 2018/6/7.
//

#ifndef POORREVERSI_NODE_H
#define POORREVERSI_NODE_H

#include <vector>

extern int num_node;
typedef struct Node *node;
struct Node {
    int win;   //win times
    int n;     //total times
    double c;  //const
    int t;     //sum of total times

    int curi;
    int curj;  //current position chosen

    std::vector<node> Next; //point to the son node
    std::vector<int> candidate; //candidate of point
    int map[8][8];  //map of chess, 0 for no, 1 for black, 2 for white
    bool color; //0 for white, 1 for black
    bool isEnd; //is end or not
    node father;
    Node() {
        num_node++;
    }
};

#endif //POORREVERSI_NODE_H
