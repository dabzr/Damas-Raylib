#include <raylib.h>
#include <math.h>
#include <iostream>
#include <array>
#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800
#define SIZESQ 96
#define BORDER_THICKNESS 16


typedef enum{
  Black, White, Red, Blue
}ColorEnum;

struct Piece{
  float x, y;
  float tempx, tempy;
  ColorEnum color;
  bool alive = true;
  struct Square *square;
};

struct Square {
  float x, y;
  const size_t squareSide = SIZESQ;
  ColorEnum color;
};
class Movement {
public:
  Vector2 tempvec {-1, -1};
  ColorEnum currentTurn = Red;
  std::array<std::array<Square, 8>, 8> square;
  std::array<std::array<Piece, 4>, 6> piece;
  const size_t squareSide = square[0][0].squareSide;
  Movement(){
     for(int i = 0; i < 8; i++){
      for (int j = 0; j < 8; j++){
        square[i][j].x = squareSide * j + BORDER_THICKNESS;
        square[i][j].y = squareSide * i + BORDER_THICKNESS;
        square[i][j].color = (i+j)%2?White:Black;
      }
    }
    
    for (int i = 0; i < 3; i++){
      for (int j = 0; j < 8; j++){
        if(square[i][j].color == Black){
          piece[i][j/2].x = square[i][j].x;
          piece[i][j/2].y = square[i][j].y;
          piece[i][j/2].tempx = square[i][j].x;
          piece[i][j/2].tempy = square[i][j].y;
          piece[i][j/2].color = Red;
          piece[i][j/2].square = &square[i][j];
        }
      }
    }

    for (int i = 5; i < 8; i++){
      for (int j = 0; j < 8; j++){
        if(square[i][j].color == Black){
          piece[i-2][j/2].x = square[i][j].x;
          piece[i-2][j/2].y = square[i][j].y;
          piece[i-2][j/2].tempx = square[i][j].x;
          piece[i-2][j/2].tempy = square[i][j].y;
          piece[i-2][j/2].color = Blue;
          piece[i-2][j/2].square = &square[i][j];
        }

      }
    }
  }
  bool PieceCollision(const Piece piece, int x, int y) {
   return (x >= piece.tempx) && (x <= piece.tempx + SIZESQ) && (y >= piece.tempy) && (y <= piece.tempy + SIZESQ);
  }
  bool isInBlack (int x, int y, Vector2 &vec){
    for (int i = 0; i < 8; i++){
      for (int j = 0; j < 8; j++){            
        if (square[i][j].color == Black) {
          if (x >= square[i][j].x - (float)SIZESQ / 2 &&
            x <= square[i][j].x + (float)SIZESQ / 2 &&
            y >= square[i][j].y - (float)SIZESQ / 2 &&
            y <= square[i][j].y + (float)SIZESQ / 2) {
            vec = { (float)i, (float)j };
            return true;
          }
        }
      }     
    }
    return false;
  } 

  bool isInPiece (Vector2 &vec, int x, int y){
    for(int i = 0; i < 6; i++){
      for (int j = 0; j < 4; j++){
        if (PieceCollision(piece[i][j], x, y)){
          vec = {(float)i, (float)j};
          return true;
        }
      }
    }
    return false;
  }
  bool IsValid(Square square){
    for(int i = 0; i < 6; i++){
      for(int j = 0; j < 4; j++){
        if((piece[i][j].square->x == square.x) &&(piece[i][j].square->y == square.y)){
          return false;
        }
      }
    }
    return true;
  }
  bool isholding = false;
  Piece* selectedPiece = nullptr;
  void movepiece(){
    if (isholding){
      selectedPiece->tempx = GetMouseX() - (float) SIZESQ/2; 
      selectedPiece->tempy = GetMouseY() - (float) SIZESQ/2;
    }
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !isholding){
      if(isInPiece(tempvec, GetMouseX(), GetMouseY())){
        if (piece[tempvec.x][tempvec.y].color == currentTurn){
          isholding = true;
          selectedPiece = &piece[tempvec.x][tempvec.y];
        }
      } 
    }
    else if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isholding){
          Vector2 tempvec2;
          if (isInBlack(selectedPiece->tempx, selectedPiece->tempy, tempvec2)) {
            if ((tempvec2.x != selectedPiece->square->x || tempvec2.y != selectedPiece->square->y) && IsValid(square[tempvec2.x][tempvec2.y])) {
              selectedPiece->x = square[tempvec2.x][tempvec2.y].x;
              selectedPiece->y = square[tempvec2.x][tempvec2.y].y;
              selectedPiece->square = &square[tempvec2.x][tempvec2.y];
              selectedPiece->tempx = selectedPiece->x;
              selectedPiece->tempy = selectedPiece->y;
              currentTurn = (currentTurn == Red) ? Blue : Red;
              isholding = false;
            }
          }          
    }
  }

};

class Graphics : public Movement{
public:
  Texture2D table;
  Texture2D redpiece;
  Texture2D bluepiece;
protected:
  void gameUI(){
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
};

class WindowLoop : public Graphics{
public:
  void windowLoop(){
    SetTargetFPS(60);
    InitWindow(WINDOW_HEIGHT, WINDOW_WIDTH, "Chess");
    SetExitKey(KEY_ESCAPE);
    table = LoadTexture("assets/tab.png");
    redpiece = LoadTexture("assets/pec.png");
    bluepiece = LoadTexture("assets/pecb.png");
    while(!WindowShouldClose()){
      gameUI();
      movepiece();
    }
    CloseWindow();
  }
};

int main (){
  WindowLoop loop;
  loop.windowLoop();
}
