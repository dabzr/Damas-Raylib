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

    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if (squares[i * 8 + j].color == Black && i != 3 && i != 4) {
          ColorEnum color = (i >= 0 && i < 3)?Red:Blue; 
          pieces.push_back(Piece(squares[i * 8 + j].x, squares[i * 8 + j].y, color, &squares[i * 8 + j]));
        }
      }
    }

    table = LoadTexture("assets/tab.png");
    redpiece = LoadTexture("assets/pec.png");
    bluepiece = LoadTexture("assets/pecb.png");
}

Board::~Board(){
  UnloadTexture(table);
  UnloadTexture(redpiece);
  UnloadTexture(bluepiece);
}

void Board::dropHandling() {
    for (Square &square : squares) {
      if (square.color == Black && square.isColliding(selectedPiece->tempx, selectedPiece->tempy) && isValid(square)) {
        *selectedPiece = Piece(square.x, square.y, selectedPiece->color, &square);
        currentTurn = (currentTurn == Red) ? Blue : Red;
        isHolding = false;
        break;
      }
    }
}


void Board::holdHandling (){
  for(Piece &piece : pieces){
    if(piece.isColliding(GetMouseX(), GetMouseY())) {
      if(piece.color == currentTurn) {
        isHolding = true;
        selectedPiece = &piece;
      }
    }
  }
}

bool Board::isValid(Square square){
    for(Piece &piece : pieces){
      if((piece.square->x == square.x) &&(piece.square->y == square.y))
        return false;
    }
    return true;
}
void Board::movementHandling(){
  if (isHolding){
    selectedPiece->tempx = GetMouseX() - (float) SIZESQ/2; 
    selectedPiece->tempy = GetMouseY() - (float) SIZESQ/2;
  }
  if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    isHolding?dropHandling():holdHandling();
  }               
}

void Board::Draw(){ 
    BeginDrawing();
    DrawTexture(table, 0, 0, WHITE);
    for (Piece piece : pieces){
        Texture2D piecetexture = (piece.color == Red)?redpiece:bluepiece;
        if (piece.isAlive) DrawTexture(piecetexture, piece.tempx, piece.tempy, WHITE);
    }
    EndDrawing();
}

void Board::Tick() {
  Draw();
  movementHandling();
}
