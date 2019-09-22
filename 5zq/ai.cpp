
#ifndef AI_INCLUDED
#define AI_INCLUDED

#include "statistics.cpp"

class AI {
 public:
  AI(int _color) : color(_color) {}
  ~AI() {}
  void virtual move() {}
 protected:
  int color;
} *bot;

class SHABI_AI : public AI {
 public:
  SHABI_AI(int c) : AI(c) {}
  ~SHABI_AI() {}
  void move() {
    int movex, movey, max_score = -1;
    for (int i = 0; i < board_size; ++i) {
      for (int j = 0; j < board_size; ++j) if (chess_board[i][j] == -1) {
        int score = s_score[i][j];
        for (int k = 0; k < 8; ++k) {
          for (int l = 1; l < board_size; ++l) {
            int x = i + l * dx[k], y = j + l * dy[k];
            if (x < 0 || y < 0 || x >= board_size || y >= board_size || chess_board[x][y] == (color ^ 1)) break;
            score += 10 * (chess_board[x][y] == color);
          }
        }
        if (max_score < score) max_score = score, movex = i, movey = j;
      }
    }
    if (~max_score) chess_board[movex][movey] = color;
  }
};

class AI_1 : public AI {
 public:
  AI_1(int c) : AI(c) {}
  ~AI_1() {}
  void move() {
    int movex, movey, max_score = -1;
    for (int i = 0; i < board_size; ++i) {
      for (int j = 0; j < board_size; ++j) if (chess_board[i][j] == -1) {
        int score = s_score[i][j];
        for (int k = 0; k < 8; ++k) {
          for (int l = 1; l < board_size; ++l) {
            int x = i + l * dx[k], y = j + l * dy[k];
            if (x < 0 || y < 0 || x >= board_size || y >= board_size || chess_board[x][y] == (color ^ 1)) break;
            score += 10 * (chess_board[x][y] == color);
          }
        }
        if (max_score < score) max_score = score, movex = i, movey = j;
      }
    }
    if (~max_score) chess_board[movex][movey] = color;
  }
};

#endif