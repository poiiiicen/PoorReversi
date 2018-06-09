//
// Created by bluejoe on 2018/6/7.
//
#include "MCT.h"
#include <iostream>
#include <ctime>

#define DEBUG

int num_node = 0;

void MCT::createMCT(bool color) {
    std::default_random_engine random(static_cast<unsigned int>(time(nullptr)));
    this->random = random;
    lunci = 0;
    treeColor = color;
}

std::pair<int, int> MCT::updateMCT(int map[8][8]) {
    initMap(map, treeColor);
    bool flag = true;
    using comjTimer::timer;
    timer timer1;
    timer1.start();
    while (flag) {
        node curNode;
        curNode = selection();
#ifdef DEBUG
        std::cout << "selection" << " " << num_node << std::endl;
#endif
        if (!curNode->isEnd) {
            curNode = expansion(curNode);
#ifdef DEBUG
            std::cout << "expansion" << " " << num_node << std::endl;
#endif
            backPropagation(curNode, simulation(curNode));
#ifdef DEBUG
            std::cout << "backPropagation" << " " << num_node << std::endl;
#endif
        }
        lunci++;
#ifdef DEBUG
        std::cout << lunci << std::endl;
#endif
        if (timer1.getTime() > 58) flag = false;
    }

#ifdef DEBUG
    std::cout << "Here" << std::endl;
#endif
    if (root->isEnd) return {0, -1};
    double max = -1;
    auto maxNode = new Node;
    for (auto tmpNode : root->Next) {
        double tmpVal;
        tmpVal = tmpNode->win * 1.0 / tmpNode->n;
        if (max < tmpVal) {
            max = tmpVal;
            maxNode = tmpNode;
        }
    }

#ifdef DEBUG
    std::cout << "Over" << std::endl;
#endif

    if (!maxNode->isEnd && maxNode->color != treeColor) return {maxNode->curi, maxNode->curj};
    else if (!maxNode->isEnd && maxNode->color == treeColor) return {-1, 0};
}

void MCT::initMap(int map[8][8], bool color) {
    auto tmpNode = new Node;
    tmpNode->color = color;
    tmpNode->win = 0;
    tmpNode->n = 0;
    tmpNode->c = sqrt(2);
    tmpNode->t = 0;
    tmpNode->isEnd = false;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) tmpNode->map[i][j] = map[i][j];
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (isLegal(tmpNode->map, i, j, tmpNode->color)) tmpNode->candidate.push_back(i * 8 + j);
    tmpNode->father = nullptr;
    root = tmpNode;

}

node MCT::selection() {
    node curNode = this->root;
#ifdef DEBUG
    std::cout << "Before" << std::endl;
#endif
    while (curNode->candidate.empty()) {
        if (curNode->isEnd) break;
        double max = -1;
        node maxNode;
        for (auto tmpNode : curNode->Next) {
            double tmpVal;
            tmpVal = tmpNode->win * 1.0 / tmpNode->n + tmpNode->c * (log(tmpNode->t) / tmpNode->n);
#ifdef DEBUG
            std::cout << tmpVal << ":" << tmpNode->win << ":" << tmpNode->n << ":" << tmpNode->c << ":" << tmpNode->t << " ";
#endif
            if (max < tmpVal) {
                max = tmpVal;
                maxNode = tmpNode;
            }
        }
#ifdef DEBUG
        std::cout << std::endl << max << " " << curNode->isEnd << " " << (curNode == maxNode) << " "
                  << curNode->candidate.size() << " " << curNode->Next.size() << std::endl;
        if (max == -1) {
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j){
                    std::cout << curNode->map[i][j] << " ";
                }
                std::cout << "\n";
            }
        }
#endif
        curNode = maxNode;
    }
#ifdef DEBUG
    std::cout << "After" << std::endl;
#endif
    return curNode;
}

node MCT::expansion(node curNode) {
    auto tmpNode = new Node;

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) tmpNode->map[i][j] = curNode->map[i][j];
    if (curNode->candidate.empty());
    else {
        auto randRange = static_cast<int>(curNode->candidate.size());
        std::uniform_int_distribution<int> dis(0, randRange - 1);
        //printf("%d\n",dis(random));
        int t = dis(random);
        int i = curNode->candidate[t] / 8, j = curNode->candidate[t] % 8;
        auto it = curNode->candidate.begin() + t;
        curNode->candidate.erase(it);
        run(tmpNode->map, i, j, curNode->color);
        tmpNode->curi = i;
        tmpNode->curj = j;
    }
    tmpNode->color = !curNode->color;
    tmpNode->c = curNode->c;
    tmpNode->t = curNode->n;
    tmpNode->win = 0;
    tmpNode->n = 0;
    tmpNode->father = curNode;
    curNode->Next.push_back(tmpNode);
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (isLegal(tmpNode->map, i, j, tmpNode->color)) tmpNode->candidate.push_back(i * 8 + j);
    if (tmpNode->candidate.empty()) {
        tmpNode->color = !tmpNode->color;
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (isLegal(tmpNode->map, i, j, tmpNode->color)) tmpNode->candidate.push_back(i * 8 + j);
        if (tmpNode->candidate.empty()) tmpNode->isEnd = true;
    } else {
        tmpNode->isEnd = false;
    }
    return tmpNode;
}

bool MCT::simulation(node curNode) {

    if (curNode->isEnd)
        return isWin(curNode->map, root->color);
    int tmpMap[8][8];
    std::vector<int> candidate;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) tmpMap[i][j] = curNode->map[i][j];

    bool tmpColor = curNode->color;

    while (!isEnd(tmpMap, tmpColor) || !isEnd(tmpMap, !tmpColor)) {
        if (isEnd(tmpMap, tmpColor)) tmpColor = !tmpColor;
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (isLegal(tmpMap, i, j, tmpColor)) candidate.push_back(i * 8 + j);
        auto randRange = static_cast<int>(candidate.size());
        std::uniform_int_distribution<int> dis(0, randRange - 1);
        int t = dis(random);
        int i = candidate[t] / 8, j = candidate[t] % 8;
        run(tmpMap, i, j, tmpColor);
        tmpColor = !tmpColor;
        candidate.clear();
        /*for(int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++)
                std::cout << tmpMap[i][j] << " ";
            std::cout << std::endl;
        }*/
    }

    return isWin(tmpMap, root->color);
}

void MCT::backPropagation(node curNode, bool isWin) {
    if (isWin) {
        node tmpNode = curNode;

        while (tmpNode->father != nullptr) {
            tmpNode->n++;
            for (auto i : tmpNode->Next) i->t = tmpNode->n;
            tmpNode->win++;
            tmpNode = tmpNode->father;
        }

        tmpNode->n++;
        tmpNode->win++;
        tmpNode->t++;
        for (auto i : tmpNode->Next) i->t = tmpNode->n;

    } else {
        node tmpNode = curNode;

        while (tmpNode->father != nullptr) {
            tmpNode->n++;
            for (auto i : tmpNode->Next) i->t = tmpNode->n;

            tmpNode = tmpNode->father;
        }

        tmpNode->n++;
        tmpNode->t++;
        for (auto i : tmpNode->Next) i->t = tmpNode->n;
    }
}

