//
// Created by bluejoe on 2018/6/8.
//

#ifndef POORREVERSI_LOGIC_H
#define POORREVERSI_LOGIC_H

const int dir[8][2] = {-1, 0, -1, 1, 0, 1, 1, 1, 1, 0, 1, -1, 0, -1, -1, -1};
bool isLegal(int map[8][8], int coni, int conj, bool color);
bool isEnd(int map[8][8], bool color);
bool isWin(int map[8][8], bool color);
void run(int map[8][8], int coni, int conj, bool color);

#endif //POORREVERSI_LOGIC_H
