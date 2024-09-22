#include "../include/Board.hpp"
#include <raylib.h>

Board::Board(){
    for(int i = 0; i < 8; i++){
      for (int j = 0; j < 8; j++){
        float squareX = squareSide * j + BORDER_THICKNESS;
        float squareY = squareSide * i + BORDER_THICKNESS;
        ColorEnum squareColor = (i+j)%2?White:Black;
        square[i][j] = Square(squareX, squareY, squareColor);
      }
    }
    
    for (int i = 0; i < 3; i++){
      for (int j = 0; j < 8; j++){
        if(square[i][j].color == Black){
          piece[i][j/2] = Piece(square[i][j].x, square[i][j].y, Red, &square[i][j]);
        }
      }
    }

    for (int i = 5; i < 8; i++){
      for (int j = 0; j < 8; j++){
        if(square[i][j].color == Black){
          piece[i-2][j/2] = Piece(square[i][j].x, square[i][j].y, Blue, &square[i][j]);
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

void Board::dropHandling(){
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (square[i][j].color == Black && square[i][j].isColliding(selectedPiece->tempx, selectedPiece->tempy) && isValid(square[i][j])) {
            *selectedPiece = Piece(square[i][j].x, square[i][j].y, selectedPiece->color, &square[i][j]);
            currentTurn = (currentTurn == Red)? Blue : Red;
            isHolding = false;
            break;
        }
      }
    }
}

void Board::holdHandling (){
  for(int i = 0; i < 6; i++){
    for(int j = 0; j < 4; j++) {
      if(piece[i][j].isColliding(GetMouseX(), GetMouseY())) {
        if(piece[i][j].color == currentTurn) {
          isHolding = true;
          selectedPiece = &piece[i][j];
        }
      }
    }
  }
}

bool Board::isValid(Square square){
    for(int i = 0; i < 6; i++){
      for(int j = 0; j < 4; j++){
        if((piece[i][j].square->x == square.x) &&(piece[i][j].square->y == square.y)){
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
        if (piece[i][j].color == Red && piece[i][j].alive)
          DrawTexture(redpiece, piece[i][j].tempx, piece[i][j].tempy, WHITE);
        if (piece[i][j].color == Blue && piece[i][j].alive)
          DrawTexture(bluepiece, piece[i][j].tempx, piece[i][j].tempy, WHITE);
      }
    }
    EndDrawing();
}

void Board::Tick() {
  Draw();
  movementHandling();
}
