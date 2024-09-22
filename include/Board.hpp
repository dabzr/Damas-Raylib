#pragma once
#include "Piece.hpp"
#include "raylib.h"
#include <vector>
using namespace std;
class Board {
  Texture2D table;
  const int squareSide = SIZESQ; 
  void Draw();
  public:
    Board();
    ~Board();
    void Tick();
    vector<Square> squares;

};

