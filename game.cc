#include "game.h"

// Cell
Cell::Cell() 
  : state_(CellState::kEmpty) {
}

void Cell::Show() {
  switch (state_) {
   case CellState::kEmpty:
    printf(" ");
    break;
   case CellState::kZero:
    printf("O");
    break;
   case CellState::kCross:
    printf("X");
    break;
  }
}

// GameDesk
void GameDesk::Show() {
  for (int i = 0; i < kDeskSize; i++) {
    for (int j = 0; j < kDeskSize; j++) {
      cells_[i][j].Show();
      if (j < kDeskSize - 1) {
        printf("|");
      }
    }
    if (i < kDeskSize - 1) {
      printf("\n");
      for (int j = 0; j < kDeskSize; j++) {
        printf("- ");
      }
    }
    printf("\n");
  }
}

void GameDesk::Reset() {
  for (int i = 0; i < kDeskSize; i++) {
    for (int j = 0; j < kDeskSize; j++) {
      cells_[i][j].set_state(CellState::kEmpty);
    }
  }
}


// Game
void Game::InitNewGame() {
  is_game_over_ = false;
  player_turn_ = PlayerTurn::kPlayer1;
  game_desk_.Reset();
}

void Game::StartGame() {
  game_desk_.Show();
  while (!is_game_over_) {
    bool is_entered_turn_correct_ = false;
    while (!is_entered_turn_correct_) {
      printf("\nHi %s, please make your turn: ", (PlayerTurn::kPlayer1 == player_turn_) ? "Player1" : "Player2");
      int x, y;
      scanf("%d%d", &y, &x);
      if (0 <= y && y < kDeskSize &&
          0 <= x && x < kDeskSize &&
          game_desk_.getCellYX(y, x).state() == CellState::kEmpty) {
        game_desk_.getCellYX(y, x).set_state((PlayerTurn::kPlayer1 == player_turn_) ?
                                                 CellState::kZero : CellState::kCross);
        is_entered_turn_correct_ = true;
      } else {
        printf("This cell is not enable! Please try again.\n");
      }
    }

    system("cls");
    game_desk_.Show();

    auto game_win_state = JudjeGameDesk();
    switch (game_win_state) {
     case GameWinState::kPlayer1:
      printf("Congratulations to Player1! Hi's winner!\n");
      is_game_over_ = true;
      break;
     case GameWinState::kPlayer2:
      printf("Congratulations to Player2! Hi's winner!\n");
      is_game_over_ = true;
      break;
     case GameWinState::kDraw:
      printf("Here is a draw! :(\n");
      is_game_over_ = true;
      break;
    }

    player_turn_ = ((PlayerTurn::kPlayer1 == player_turn_) ? PlayerTurn::kPlayer2 : PlayerTurn::kPlayer1);
  }
}

GameWinState Game::JudjeGameDesk() {
  CellState first_cell_state;
  bool is_line_won;
  // Check rows
  for (int i = 0; i < kDeskSize; i++) {
    first_cell_state = game_desk_.getCellYX(i, 0).state();
    is_line_won = CellState::kEmpty != first_cell_state;
    for (int j = 1; j < kDeskSize && is_line_won; j++) {
      if (game_desk_.getCellYX(i, j).state() != first_cell_state) {
        is_line_won = false;
        break;
      }
    }
    if (is_line_won) {
      return (first_cell_state == CellState::kZero) ? GameWinState::kPlayer1 : GameWinState::kPlayer2;
    }
  }

  // Check columns
  for (int i = 0; i < kDeskSize; i++) {
    first_cell_state = game_desk_.getCellYX(0, i).state();
    is_line_won = CellState::kEmpty != first_cell_state;
    for (int j = 1; j < kDeskSize && is_line_won; j++) {
      if (game_desk_.getCellYX(j, i).state() != first_cell_state) {
        is_line_won = false;
        break;
      }
    }
    if (is_line_won) {
      return (first_cell_state == CellState::kZero) ? GameWinState::kPlayer1 : GameWinState::kPlayer2;
    }
  }


  // Check diagonals
  first_cell_state = game_desk_.getCellYX(0, 0).state();
  is_line_won = CellState::kEmpty != first_cell_state;
  for (int i = 1; i < kDeskSize && is_line_won; i++) {
    if (game_desk_.getCellYX(i, i).state() != first_cell_state) {
      is_line_won = false;
      break;
    }
  }

  if (is_line_won) {
    return (first_cell_state == CellState::kZero) ? GameWinState::kPlayer1 : GameWinState::kPlayer2;
  }

  first_cell_state = game_desk_.getCellYX(0, kDeskSize - 1).state();
  is_line_won = CellState::kEmpty != first_cell_state;
  for (int i = 1; i < kDeskSize && is_line_won; i++) {
    if (game_desk_.getCellYX(i, kDeskSize - 1 - i).state() != first_cell_state) {
      is_line_won = false;
      break;
    }
  }

  if (is_line_won) {
    return (first_cell_state == CellState::kZero) ? GameWinState::kPlayer1 : GameWinState::kPlayer2;
  }

  // Check on draw
  int count_of_empty_cells = 0;
  for (int i = 0; i < kDeskSize; i++) {
    for (int j = 0; j < kDeskSize; j++) {
      count_of_empty_cells += (game_desk_.getCellYX(i, j).state() == CellState::kEmpty);
    }
  }

  if (count_of_empty_cells == 0) {
    return GameWinState::kDraw;
  }

  return GameWinState::kNone;
}
