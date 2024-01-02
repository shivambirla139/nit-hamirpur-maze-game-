#include<bits/stdc++.h>
#include"constants.hpp"
using namespace std;

int maze[MAZE_ROWS][MAZE_COLS]={
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1,0,0,0,1,1,1,1},
    {1,1,1,0,1,1,0,0,0,0,0,0,1,1,1,0,1,1,0,1,1,0,1,0,1,1,0,1,1,1,0,1,1,0,1,0,1,1,1,1},
    {1,0,1,0,1,1,0,1,1,1,0,1,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,1,1,1,0,0,1,0,1,1,0,1,1,1,0,1,1,0,1,0,0,0,0,1},
    {1,0,1,0,1,1,0,1,0,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,1,1,1,0,1,1,0,1,0,1,1,1,1},
    {1,1,0,0,1,1,0,1,1,1,1,0,1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,0,0,0,0,0,1,1,1,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1},
    {1,0,0,0,1,1,0,1,0,1,1,0,1,1,1,1,1,1,0,1,1,1,0,1,1,0,1,0,1,1,0,0,0,0,0,0,0,0,1,1},
    {1,1,1,0,1,0,0,1,0,1,1,0,0,0,0,0,1,1,0,1,1,1,0,0,0,0,0,0,1,1,1,1,0,1,1,0,1,0,1,1},
    {1,0,1,0,0,0,1,1,0,1,1,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,1,0,1,1,0,1,0,0,1},
    {1,0,0,0,1,1,1,1,0,1,1,0,1,0,1,0,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,0,0,0,0,0,1,1,1,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1},
    {1,0,0,0,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,1,1,0,1,1,1,1,1,0,1,1},
    {1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,1,1},
    {1,1,1,0,1,1,1,0,1,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,1,0,1,1,0,1,1,1,0,1,1,0,1,1},
    {1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,0,0,0,1,1,0,1,0,1,1,1,1,0,1,1,0,1,1,1,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};