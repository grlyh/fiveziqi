
#ifndef STATISTICS_INCLUDED
#define STATISTICS_INCLUDED

#define FIRST 0
#define SECOND 1

#include <cstring>

const int board_size = 19;
const int maxn = 100010;

const int dx[] = {1, -1, 0, 0, 1, -1, 1, -1};
const int dy[] = {0, 0, 1, -1, -1, 1, 1, -1};

int chess_board[board_size][board_size];
int player_color;

#endif