
#ifndef AI_INCLUDED
#define AI_INCLUDED

#include <cstdlib>
#include "statistics.cpp"


class AI {
 public:
  AI(int _color) : color(_color) {}
  ~AI() {}
  void virtual move() {}
 protected:
  bool inline inboard(int x, int y) {
    return x >= 0 && y >= 0 && x < board_size && y < board_size;
  }
  int color;
} *bot, *bot2;

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
            if (!inboard(x, y) || chess_board[x][y] == (color ^ 1)) break;
            score += 10 * (chess_board[x][y] == color);
          }
        }
        if (max_score < score) max_score = score, movex = i, movey = j;
      }
    }
    if (~max_score) chess_board[movex][movey] = color;
  }
 private:
  static const int s_score[board_size][board_size];
};

class AI_1 : public AI {
 public:
  AI_1(int c) : AI(c) {}
  ~AI_1() {}
  void move() {
    // huo 4 & tiao 4
    for (int i = 0; i < board_size; ++i) {
      for (int j = 0; j < board_size; ++j) if (chess_board[i][j] == -1) {
        for (int k = 0; k < 8; k += 2) {
          for (int g = 0; g < 2; ++g) {
            int res = 0;
            for (int l = 1; l < 5; ++l) {
              int x = i + l * dx[k], y = j + l * dy[k];
              if (!inboard(x, y) || chess_board[x][y] != (color ^ g)) break;
              ++res;
            }
            for (int l = 1; l < 5; ++l) {
              int x = i + l * dx[k + 1], y = j + l * dy[k + 1];
              if (!inboard(x, y) || chess_board[x][y] != (color ^ g)) break;
              ++res;
            }
            if (res >= 4) return (void) (chess_board[i][j] = color);
          }
        }
      }
    }
    // huo 3 & tiao 3
    for (int i = 0; i < board_size; ++i) {
      for (int j = 0; j < board_size; ++j) if (chess_board[i][j] == -1) {
        for (int k = 0; k < 8; k += 2) {
          for (int g = 0; g < 2; ++g) {
            int res = 0, cnum = 0, f = 0;
            for (int l = 1; l < 5; ++l) {
              int x = i + l * dx[k], y = j + l * dy[k];
              if (!inboard(x, y) || chess_board[x][y] != (color ^ g)) {
                if (res && inboard(x, y) &&
                    chess_board[x][y] == (color ^ g ^ 1) &&
                    chess_board[x - dx[k]][y - dy[k]] == (color ^ g)) f = 1;
                break;
              }
              res++, cnum++;
            }
            res = 0;
            for (int l = 1; l < 5; ++l) {
              int x = i + l * dx[k + 1], y = j + l * dy[k + 1];
              if (!inboard(x, y) || chess_board[x][y] != (color ^ g)) {
                if (res && inboard(x, y) &&
                    chess_board[x][y] == (color ^ g ^ 1) &&
                    chess_board[x - dx[k]][y - dy[k]] == (color ^ g)) f = 1;
                break;
              }
              res++, cnum++;
            }
            if (cnum < 3) f = 1;
            res = 1;
            for (int l = 1; l < 5; ++l) {
              int x = i + l * dx[k], y = j + l * dy[k];
              if (!inboard(x, y) || chess_board[x][y] == (color ^ g ^ 1)) break;
              res++;
            }
            for (int l = 1; l < 5; ++l) {
              int x = i + l * dx[k], y = j + l * dy[k];
              if (!inboard(x, y) || chess_board[x][y] == (color ^ g ^ 1)) break;
              res++;
            }
            if (res < 5) f = 1;
            if (!f) return (void) (chess_board[i][j] = color);
          }
        }
      }
    }
    // ai

    //
    int movex, movey, max_score = -1;
    for (int i = 0; i < board_size; ++i) {
      for (int j = 0; j < board_size; ++j) if (chess_board[i][j] == -1) {
        int score = s_score[i][j];
        for (int k = 0; k < 8; ++k) {
          for (int l = 1; l < board_size; ++l) {
            int x = i + l * dx[k], y = j + l * dy[k];
            if (!inboard(x, y) || (chess_board[x][y] != color) * ((unsigned)rand() % 100 < 00)) break;
            score += 10 * (chess_board[x][y] == color);
          }
        }
        if (max_score < score) max_score = score, movex = i, movey = j;
      }
    }
    if (~max_score) chess_board[movex][movey] = color;
  }
 private:
  static const int s_score[board_size][board_size];
};

class AI_SKH : public AI {
 public:
  AI_SKH(int c) : AI(c) {}
  ~AI_SKH() {}
  bool check(int x,int y,int k){
    return (x < 0 || y < 0 || x >= board_size || y >= board_size || chess_board[x][y] == k);
  }
  void move() {
    int movex, movey, max_score = -1;
    int sti=rand()&1;
    for (int XX = 0; XX < board_size; ++XX) {
    int i=sti?XX:board_size-XX+1,stj=rand()*rand()&1;
      for(int YY = 0,j=stj?YY:board_size-YY+1; YY < board_size; ++YY,j=stj?YY:board_size-YY+1) if (chess_board[i][j] == -1) {
    int score = s_score[i][j],f2=0,f3=0;
        for(int k=0;k<8;k+=2){
          int MX=i,MY=j,TOT=0;
          for(int l=1;l<=4;++l){
            MX+=dx[k],MY+=dy[k];
            if(check(MX,MY,color^1))break;
            if(chess_board[MX][MY]==color)TOT++;
            else if(l>1 && chess_board[MX-dx[k]][MY-dy[k]]==-1)break;
      }
      MX=i,MY=j;
      for(int l=1;l<=4;++l){
            MX-=dx[k],MY-=dy[k];
            if(check(MX,MY,color^1))break;
            if(chess_board[MX][MY]==color)TOT++;
            else if(l>1 && chess_board[MX+dx[k]][MY+dy[k]]==-1)break;
      }
      if(f2){if(TOT==2)score+=400,f2=0;}
      else if(TOT==2)f2=1;
      if(f3){if(TOT==3)score+=400,f3=0;}
      else if(TOT==3)f3=1;
      score+=mVAL[TOT];
      MX=i,MY=j,TOT=0;
      for(int l=1;l<=4;++l){
            MX+=dx[k],MY+=dy[k];
            if(check(MX,MY,color)){if(TOT<=3)TOT--;break;}
            if(chess_board[MX][MY]==(color^1))TOT++;
            else if(chess_board[MX-dx[k]][MY-dy[k]]==-1)break;
      }
      MX=i,MY=j;
      for(int l=1;l<=4;++l){
            MX-=dx[k],MY-=dy[k];
            if(check(MX,MY,color)){if(TOT<=3)TOT--;break;}
            if(chess_board[MX][MY]==(color^1))TOT++;
            else if(chess_board[MX+dx[k]][MY+dy[k]]==-1)break;
      }
      score+=aVAL[TOT];
    }
        if (max_score < score) max_score = score, movex = i, movey = j;
      }
    }
    if (~max_score) chess_board[movex][movey] = color;
  }
 private:
  static const int mVAL[];
  static const int aVAL[];
  static const int s_score[board_size][board_size];
};

const int SHABI_AI::s_score[board_size][board_size] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, 
  {0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0}, 
  {0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0}, 
  {0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0}, 
  {0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0}, 
  {0, 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 5, 4, 3, 2, 1, 0}, 
  {0, 1, 2, 3, 4, 5, 6, 7, 7, 7, 7, 7, 6, 5, 4, 3, 2, 1, 0}, 
  {0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 8, 7, 6, 5, 4, 3, 2, 1, 0}, 
  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, 
  {0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 8, 7, 6, 5, 4, 3, 2, 1, 0}, 
  {0, 1, 2, 3, 4, 5, 6, 7, 7, 7, 7, 7, 6, 5, 4, 3, 2, 1, 0}, 
  {0, 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 5, 4, 3, 2, 1, 0}, 
  {0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0}, 
  {0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0}, 
  {0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0}, 
  {0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0}, 
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
};

const int AI_1::s_score[board_size][board_size] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, 
  {0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0}, 
  {0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0}, 
  {0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0}, 
  {0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0}, 
  {0, 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 5, 4, 3, 2, 1, 0}, 
  {0, 1, 2, 3, 4, 5, 6, 7, 7, 7, 7, 7, 6, 5, 4, 3, 2, 1, 0}, 
  {0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 8, 7, 6, 5, 4, 3, 2, 1, 0}, 
  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, 
  {0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 8, 7, 6, 5, 4, 3, 2, 1, 0}, 
  {0, 1, 2, 3, 4, 5, 6, 7, 7, 7, 7, 7, 6, 5, 4, 3, 2, 1, 0}, 
  {0, 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 5, 4, 3, 2, 1, 0}, 
  {0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0}, 
  {0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0}, 
  {0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0}, 
  {0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0}, 
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
};

const int AI_SKH::s_score[board_size][board_size] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, 
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, 
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, 
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, 
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, 
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, 
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, 
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 0, 0}, 
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, 
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, 
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, 
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, 
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, 
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, 
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
};

const int AI_SKH::mVAL[] = {0, 5, 10, 101, 1001, 1001, 1001, 1001, 1001};
const int AI_SKH::aVAL[] = {0, 5, 10, 102, 1002, 1002, 1002, 1002, 1002};

#endif
