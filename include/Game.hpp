#pragma once
#include "Piece.hpp"
#include "Board.hpp"
#include <raylib.h>
#include <vector>
using namespace std;
class Game{
  Board board;
  Texture2D redpiece;
  Texture2D bluepiece;
  vector<Piece> pieces;
  ColorEnum currentTurn = Red;
  bool isHolding = false;
  Piece* selectedPiece = nullptr;
  void dropHandling();
  void holdHandling();
  void movementHandling();
  bool isValid(Square square);
  void Draw();
  public:
  Game();
  ~Game();
  void Tick();

};
