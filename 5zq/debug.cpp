

namespace DBG {
  
  void inline print_board() {
    printf("   ");
    for (int i = 1; i <= board_size; ++i) printf("%2d%c", i, " \n"[i == board_size]);
    for (int i = 0; i < board_size; ++i, puts("")) {
      printf("%2d ", i + 1);
      for (int j = 0; j < board_size; ++j) {
        if (~chess_board[i][j]) printf("%2d ", chess_board[i][j]);
        else printf("   ");
      }
    }
  }
  
}
