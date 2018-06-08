//
// Created by bluejoe on 2018/6/7.
//
#include "MCT.h"
#include <random>
#include <ctime>

void MCT::creatMCT(int map[8][8], bool color)
{
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
            if (isLegal(root->map,i,j,root->color)) root->candidate.push_back(i*8+j);
    tmpNode->father = nullptr;
    root = tmpNode;

}

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

node MCT::expansion(node curNode)
{
    std::default_random_engine random(static_cast<unsigned int>(time(nullptr)));

    auto tmpNode = new Node;
    tmpNode->color = !curNode->color;
    for (int i = 0; i < 8; i ++)
        for (int j = 0; j < 8; j++) tmpNode->map[i][j] = curNode->map[i][j];

    auto randRange = static_cast<int>(curNode->candidate.size());
    std::uniform_int_distribution<int> dis(1, randRange);
    //printf("%d\n",dis(random));
    int t = dis(random);
    int i = curNode->candidate[t] / 8, j = curNode->candidate[t] % 8;
    auto it = curNode->candidate.begin()+t;
    curNode->candidate.erase(it);
    run(tmpNode->map, i, j, tmpNode->color);
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
    std::default_random_engine random(static_cast<unsigned int>(time(nullptr)));
    int tmpMap[8][8];
    std::vector<int> candidate;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) tmpMap[i][j] = curNode->map[i][j];

    bool tmpColor = !curNode->color;

    while (!isEnd(tmpMap, tmpColor) && !isEnd(tmpMap, !tmpColor)){
        if (isEnd(tmpMap, tmpColor)) tmpColor = !tmpColor;
        for (int i = 0; i < 8; i ++)
            for (int j = 0; j < 8; j++)
                if (isLegal(tmpMap,i,j,tmpColor)) candidate.push_back(i*8+j);
        auto randRange = static_cast<int>(candidate.size());
        std::uniform_int_distribution<int> dis(1, randRange);
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
            tmpNode = curNode->father;
        }

        tmpNode->n++;
        tmpNode->win++;
        tmpNode->t++;


    }
    else
    {
        node tmpNode = curNode;

        while (tmpNode->father!= nullptr) {
            tmpNode->n++;
            for(auto i : tmpNode->Next) i->t = tmpNode->n;

            tmpNode = curNode->father;
        }

        tmpNode->n++;
        tmpNode->t++;
    }
}

