#ifndef GAME_H
#define GAME_H

#include <cstdio>
#include <cstdlib>

enum class CellState {
  kEmpty = 0,
  kZero,
  kCross
};

enum class PlayerTurn {
  kPlayer1 = 0,
  kPlayer2
};

enum class GameWinState {
  kNone = 0,
  kPlayer1,
  kPlayer2,
  kDraw
};

const int kDeskSize = 3;

class Cell {
 public:
  Cell();

  void Show();

  void set_state(CellState state) { state_ = state; }
  CellState state() const { return state_; }
 private:
  CellState state_;
};

class GameDesk {
 public:
  void Show();
  void Reset();

  Cell& getCellYX(int y, int x) { return cells_[y][x]; }

 private:
  Cell cells_[kDeskSize][kDeskSize];
};

class Game {
 public:
  void InitNewGame();
  void StartGame();

 private:
  GameWinState JudjeGameDesk();

  bool is_game_over_;
  PlayerTurn player_turn_;
  GameDesk game_desk_;
};

#endif
