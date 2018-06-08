//
// Created by bluejoe on 2018/6/7.
//
#include "MCT.h"
#include <iostream>
#include <ctime>

void MCT::creatMCT(int map[8][8], bool color)
{
    std::default_random_engine random(static_cast<unsigned int>(time(nullptr)));
    this->random = random;
    lunci = 0;
    treeColor = color;
    initMap(map, color);
    bool flag = true;
    using comjTimer::timer;
    timer timer1;
    timer1.start();
    while(flag) {
        node curNode;
        curNode = selection();
        curNode = expansion(curNode);
        backPropagation(curNode, simulation(curNode));
        lunci++;
        //std::cout<<lunci<<std::endl;
        //std::cout<<timer1.getTime()<<std::endl;
        if (timer1.getTime() > 58) flag = false;
    }
}
void MCT::updateMCT(int map[8][8])
{
    initMap(map, treeColor);
    bool flag = true;
    using comjTimer::timer;
    timer timer1;
    timer1.start();
    while(flag) {
        node curNode;
        curNode = selection();
        curNode = expansion(curNode);
        backPropagation(curNode, simulation(curNode));
        if (timer1.getTime() > 58) flag = false;
    }
}

void MCT::initMap(int map[8][8], bool color)
{
    auto tmpNode = new Node;
    tmpNode->color = color;
    tmpNode->win = 0;
    tmpNode->n = 0;
    tmpNode->c = sqrt(2);
    tmpNode->t = 0;
    tmpNode->num = 0;
    tmpNode->space = 64;
    for(int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) tmpNode->map[i][j] = map[i][j];
    for (int i = 0; i < 8; i ++)
        for (int j = 0; j < 8; j++)
            if (isLegal(tmpNode->map,i,j,tmpNode->color)) tmpNode->candidate.push_back(i*8+j);
    tmpNode->father = nullptr;
    root = tmpNode;

}

node MCT::selection()
{
    node curNode = this->root;
    while(curNode->candidate.empty()) {
        double max = -1;
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

node MCT::expansion(node curNode)
{
    auto tmpNode = new Node;

    for (int i = 0; i < 8; i ++)
        for (int j = 0; j < 8; j++) tmpNode->map[i][j] = curNode->map[i][j];

    auto randRange = static_cast<int>(curNode->candidate.size());
    std::uniform_int_distribution<int> dis(0, randRange - 1);
    //printf("%d\n",dis(random));
    int t = dis(random);
    int i = curNode->candidate[t] / 8, j = curNode->candidate[t] % 8;
    auto it = curNode->candidate.begin()+t;
    curNode->candidate.erase(it);
    run(tmpNode->map, i, j, curNode->color);
    tmpNode->color = !curNode->color;
    curNode->num++;
    tmpNode->c = curNode->c;
    tmpNode->space = curNode->space - 1;
    tmpNode->num = 0;
    tmpNode->t = curNode->n;
    tmpNode->win = 0;
    tmpNode->n = 0;
    tmpNode->father = curNode;
    curNode->Next.push_back(tmpNode);
    for (i = 0; i < 8; i ++)
        for (j = 0; j < 8; j++)
            if (isLegal(tmpNode->map,i,j,tmpNode->color)) tmpNode->candidate.push_back(i*8+j);

    return tmpNode;
}

bool MCT::simulation(node curNode)
{
    int tmpMap[8][8];
    std::vector<int> candidate;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) tmpMap[i][j] = curNode->map[i][j];

    bool tmpColor = curNode->color;

    while (!isEnd(tmpMap, tmpColor) || !isEnd(tmpMap, !tmpColor)){
        if (isEnd(tmpMap, tmpColor)) tmpColor = !tmpColor;
        for (int i = 0; i < 8; i ++)
            for (int j = 0; j < 8; j++)
                if (isLegal(tmpMap,i,j,tmpColor)) candidate.push_back(i*8+j);
        auto randRange = static_cast<int>(candidate.size());
        std::uniform_int_distribution<int> dis(0, randRange - 1);
        int t = dis(random);
        int i = candidate[t] / 8, j = candidate[t] % 8;
        run(tmpMap, i, j, tmpColor);
        tmpColor = !tmpColor;
        candidate.clear();
    }

    return isWin(tmpMap, root->color);
}

void MCT::backPropagation(node curNode, bool isWin)
{
    if(isWin)
    {
        node tmpNode = curNode;

        while (tmpNode->father!= nullptr) {
            tmpNode->n++;
            for(auto i : tmpNode->Next) i->t = tmpNode->n;
            tmpNode->win++;
            tmpNode = tmpNode->father;
        }

        tmpNode->n++;
        tmpNode->win++;
        tmpNode->t++;
        for(auto i : tmpNode->Next) i->t = tmpNode->n;

    }
    else
    {
        node tmpNode = curNode;

        while (tmpNode->father!= nullptr) {
            tmpNode->n++;
            for(auto i : tmpNode->Next) i->t = tmpNode->n;

            tmpNode = tmpNode->father;
        }

        tmpNode->n++;
        tmpNode->t++;
        for(auto i : tmpNode->Next) i->t = tmpNode->n;
    }
}

