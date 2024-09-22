#include "../include/Game.hpp"
#include <raylib.h>

Game::Game(){ 
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (board.squares[i * 8 + j].color == Black && i != 3 && i != 4) {
        ColorEnum color = (i >= 0 && i < 3)?Red:Blue; 
        pieces.push_back(Piece(board.squares[i * 8 + j].x, board.squares[i * 8 + j].y, color, &board.squares[i * 8 + j]));
      }
    }
  }
  redpiece = LoadTexture("assets/pec.png");
  bluepiece = LoadTexture("assets/pecb.png"); 
}

Game::~Game(){ 
  UnloadTexture(redpiece);
  UnloadTexture(bluepiece);
}

void Game::dropHandling() {
    for (Square &square : board.squares) {
      if (square.color == Black && square.isColliding(selectedPiece->tempx, selectedPiece->tempy) && isValid(square)) {
        *selectedPiece = Piece(square.x, square.y, selectedPiece->color, &square);
        currentTurn = (currentTurn == Red) ? Blue : Red;
        isHolding = false;
        break;
      }
    }
}


void Game::holdHandling (){
  for(Piece &piece : pieces){
    if(piece.isColliding(GetMouseX(), GetMouseY())) {
      if(piece.color == currentTurn) {
        isHolding = true;
        selectedPiece = &piece;
      }
    }
  }
}

bool Game::isValid(Square square){
    for(Piece piece : pieces){
      if((piece.square->x == square.x) &&(piece.square->y == square.y))
        return false;
    }
    return true;
}
void Game::movementHandling(){
  if (isHolding){
    selectedPiece->tempx = GetMouseX() - (float) SIZESQ/2; 
    selectedPiece->tempy = GetMouseY() - (float) SIZESQ/2;
  }
  if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    isHolding?dropHandling():holdHandling();
  }               
}

void Game::Draw(){
  for (Piece piece : pieces){
      Texture2D piecetexture = (piece.color == Red)?redpiece:bluepiece;
      if (piece.isAlive) DrawTexture(piecetexture, piece.tempx, piece.tempy, WHITE);
  }
}

void Game::Tick() {
  BeginDrawing();
  board.Tick();
  Draw();
  EndDrawing();

  movementHandling();
}
