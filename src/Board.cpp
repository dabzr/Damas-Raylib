#include "../include/Board.hpp"
#include <raylib.h>

Board::Board() {
    for(int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        float squareX = squareSide * j + BORDER_THICKNESS;
        float squareY = squareSide * i + BORDER_THICKNESS;
        ColorEnum squareColor = (i + j) % 2 ? White : Black;
        square[i * 8 + j] = Square(squareX, squareY, squareColor);  // Usando índice contínuo
      }
    }

    int pieceIndex = 0;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 8; j++) {
        if (square[i * 8 + j].color == Black) {
          piece[pieceIndex++] = Piece(square[i * 8 + j].x, square[i * 8 + j].y, Red, &square[i * 8 + j]);
        }
      }
    }

    for (int i = 5; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if (square[i * 8 + j].color == Black) {
          piece[pieceIndex++] = Piece(square[i * 8 + j].x, square[i * 8 + j].y, Blue, &square[i * 8 + j]);
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
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        int index = i * 8 + j;
        if (square[index].color == Black && square[index].isColliding(selectedPiece->tempx, selectedPiece->tempy) && isValid(square[index])) {
          *selectedPiece = Piece(square[index].x, square[index].y, selectedPiece->color, &square[index]);
          currentTurn = (currentTurn == Red) ? Blue : Red;
          isHolding = false;
          break;
        }
      }
    }
}


void Board::holdHandling (){
  for(int i = 0; i < 6; i++){
    for(int j = 0; j < 4; j++) {
      int index = i * 4 + j;
      if(piece[index].isColliding(GetMouseX(), GetMouseY())) {
        if(piece[index].color == currentTurn) {
          isHolding = true;
          selectedPiece = &piece[index];
        }
      }
    }
  }
}

bool Board::isValid(Square square){
    for(int i = 0; i < 6; i++){
      for(int j = 0; j < 4; j++){
        int index = i * 4 + j;
        if((piece[index].square->x == square.x) &&(piece[index].square->y == square.y)){
          return false;
        }
      }
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
    for (int i = 0; i < 6; i++){
      for (int j = 0; j < 4; j++){
        int index = i * 4 + j;
        Texture2D piecetexture = (piece[index].color == Red)?redpiece:bluepiece;
        if (piece[index].alive) DrawTexture(piecetexture, piece[index].tempx, piece[index].tempy, WHITE);
      }
    }
    EndDrawing();
}

void Board::Tick() {
  Draw();
  movementHandling();
}
