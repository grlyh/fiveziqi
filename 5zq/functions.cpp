
#ifndef FUNCTIONS_INCLUDED
#define FUNCTIONS_INCLUDED

#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <cstdio>

void inline initialize() {
  system("chcp 936");
  system("cls");
  srand(time(0));
  memset(chess_board, -1, sizeof chess_board);
  player_color = FIRST;
  bot = new AI_SKH(FIRST);
  bot2 = new AI_1(SECOND);
}

void inline player_move() {
  int x, y;
  while (true) {
    scanf("%d%d", &x, &y);
    --x, --y;
    if (x < 0 || y < 0 || x >= board_size || y >= board_size || ~chess_board[x][y]) continue;
    chess_board[x][y] = player_color;
    break;
  }
}

void inline print_board() {
  printf("   ");
  for (int i = 1; i <= board_size; ++i) printf("%2d%c", i, " \n"[i == board_size]);
  for (int i = 0; i < board_size; ++i, puts("")) {
    printf("%2d ", i + 1);
    for (int j = 0; j < board_size; ++j) {
      if (~chess_board[i][j]) printf("%s ", chess_board[i][j] == FIRST ? "¡ð" : "¡ñ");
      else printf("   ");
    }
  }
}

int inline judge() {
  for (int i = 0; i < board_size; ++i) {
    for (int j = 0; j < board_size; ++j) {
      for (int k = 0; k < 8; k += 2) {
        int res = 0;
        for (int l = 0; l < 5; ++l) {
          int x = i + l * dx[k], y = j + l * dy[k];
          if (x < 0 || y < 0 || x >= board_size || y >= board_size) break;
          res += (chess_board[x][y] == FIRST) - (chess_board[x][y] == SECOND);
        }
        if (abs(res) == 5) return 1;
      }
    }
  }
  for (int i = 0; i < board_size; ++i) {
    for (int j = 0; j < board_size; ++j) {
      if (chess_board[i][j] == -1) return 0;
    }
  }
  return -1;
}

void inline gamemainloop() {
  print_board();
  while (true) {
    // player_move();
    bot->move();
    getchar();
    system("cls");
    print_board();
    int result = judge();
    if (result) {
      puts(result > 0 ? "player win" : "tie");
      break;
    }
    bot2->move();
    system("cls");
    print_board();
    result = judge();
    if (result) {
      puts(result > 0 ? "bot win" : "tie");
      break;
    }
  }
}

#endif
