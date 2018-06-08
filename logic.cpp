//
// Created by bluejoe on 2018/6/8.
//
#include "logic.h"
bool isLegal(int map[8][8], int coni, int conj, bool color)
{
    if (map[coni][conj]!=0) return false;
    int i, j;
    bool flag = false;
    for(int di = 0; di < 8; di++){
        i = coni + dir[di][0];
        j = conj + dir[di][1];
        while(i >= 0 && i < 8 && j >= 0 && j < 8)
        {
            if (!flag && (map[i][j] == 2 && color || map[i][j] == 1 && !color)){
                flag = true;
            }
            else if (!flag && (map[i][j] == 2 && !color || map[i][j] == 1 && color)){
                break;
            }
            else if (flag && (map[i][j] == 2 && !color || map[i][j] == 1 && color)){
                return true;
            }
            else if (map[i][j] == 0) {
                break;
            }
            i = i + dir[di][0];
            j = j + dir[di][1];
        }
        flag = false;
    }
    return false;
}

void run(int map[8][8], int coni, int conj, bool color)
{
    map[coni][conj] = color?1:2;
    int i, j;
    bool flag = false;
    bool doThis = false;
    for(int di = 0; di < 8; di++) {
        i = coni + dir[di][0];
        j = conj + dir[di][1];
        while(i >= 0 && i < 8 && j >= 0 && j < 8)
        {
            if (!flag && (map[i][j] == 2 && color || map[i][j] == 1 && !color)){
                flag = true;
            }
            else if (!flag && (map[i][j] == 2 && !color || map[i][j] == 1 && color)){
                break;
            }
            else if (flag && (map[i][j] == 2 && !color || map[i][j] == 1 && color)){
                doThis = true;
                break;
            }
            else if (map[i][j] == 0) {
                break;
            }
            i = i + dir[di][0];
            j = j + dir[di][1];
        }
        if (doThis) {
            i = coni + dir[di][0];
            j = conj + dir[di][1];
            while (map[i][j] == 2 && color || map[i][j] == 1 && !color){
                map[i][j] = color?1:2;
                i = i + dir[di][0];
                j = j + dir[di][1];
            }
        }
        doThis = false;
        flag = false;
    }
}

bool isEnd(int map[8][8], bool color)
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (isLegal(map, i, j, color)){
                return false;
    }
    return true;
}

bool isWin(int map[8][8], bool color)
{
    int black = 0, white = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (map[i][j] == 1) black++;
            else if (map[i][j] == 2) white++;
    return black > white && color || white > black && !color;
}