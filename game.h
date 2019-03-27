#ifndef GAME_H
#define GAME_H

#include <cstdio>
#include <cstdlib>

namespace {
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
}  //end

class Cell {
 public:
  Cell(const Cell& cell) = delete;
  Cell(Cell&& cell) = delete;
  Cell& operator=(const Cell& cell) = delete;
  Cell& operator=(Cell&& cell) = delete;

  Cell();

  void Show();

  void set_state(CellState state) { state_ = state; }
  CellState state() const { return state_; }
 private:
  CellState state_;
};

class GameDesk {
 public:
  GameDesk(const GameDesk& game_desk) = delete;
  GameDesk(GameDesk&& game_desk) = delete;
  GameDesk& operator=(const GameDesk& game_desk) = delete;
  GameDesk& operator=(GameDesk&& game_desk) = delete;

  GameDesk() {}

  void Show();
  void Reset();

  Cell& getCellYX(int y, int x) { return cells_[y][x]; }

 private:
  Cell cells_[kDeskSize][kDeskSize];
};

class Game {
 public:
  Game(const Game& game) = delete;
  Game(Game&& game) = delete;
  Game& operator=(const Game& game) = delete;
  Game& operator=(Game&& game) = delete;

  Game();

  void InitNewGame();
  void StartGame();

 private:
  GameWinState JudjeGameDesk();

  bool is_game_over_;
  PlayerTurn player_turn_;
  GameDesk game_desk_;
};

#endif
