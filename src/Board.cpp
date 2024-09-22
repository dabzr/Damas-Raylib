#include "../include/Board.hpp"
#include <raylib.h>

Board::Board() {
    for(int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        float squareX = squareSide * j + BORDER_THICKNESS;
        float squareY = squareSide * i + BORDER_THICKNESS;
        ColorEnum squareColor = (i + j) % 2 ? White : Black;
        squares.push_back(Square(squareX, squareY, squareColor));
      }
    }
    table = LoadTexture("assets/tab.png");
}

Board::~Board(){
  UnloadTexture(table);
}

void Board::Draw(){ 
    DrawTexture(table, 0, 0, WHITE);
}

void Board::Tick() {
  Draw();
}
