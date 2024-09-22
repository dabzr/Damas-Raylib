#include "Piece.hpp"
#include "raylib.h"

class Board {
  Texture2D table;
  Texture2D redpiece;
  Texture2D bluepiece;
  Square square[64];
  Piece piece[24];
  const int squareSide = SIZESQ;
  ColorEnum currentTurn = Red;
  bool isHolding = false;
  Piece* selectedPiece = nullptr;
  void dropHandling();
  void holdHandling();
  bool isValid(Square square);
  void movementHandling();
  void Draw();
  public:
    Board();
    ~Board();
    void Tick();

};

