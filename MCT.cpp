//
// Created by bluejoe on 2018/6/7.
//
#include "MCT.h"
#include <random>
#include <ctime>

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

void MCT::expansion(node curNode)
{
    std::default_random_engine random(static_cast<unsigned int>(time(nullptr)));

    auto tmpNode = new Node;
    tmpNode->color = !curNode->color;
    for (int i = 0; i < 8; i ++)
        for (int j = 0; j < 8; j++) tmpNode->map[i][j] = curNode->map[i][j];
    int randRange = curNode->space - curNode->num;
    std::uniform_int_distribution<int> dis(1, randRange);
    //printf("%d\n",dis(random));
    int t = dis(random);
    int i = 0, j = -1;
    while(t){
        j++;
        if (j >= 8) {j = j - 8; i++;}
        if (tmpNode->map[i][j] == 0) t = t - 1;
    }
    tmpNode->map[i][j] = tmpNode->color?1:2;
    curNode->num++;
    tmpNode->c = curNode->c;
    tmpNode->space = curNode->space - 1;
    tmpNode->num = 0;
    tmpNode->t = curNode->n;
    tmpNode->win = 0;
    tmpNode->n = 0;
    curNode->Next.push_back(tmpNode);
}

void MCT::simulation()
{

}

void MCT::backpropagation()
{

}