#include <raylib.h>
#include "../include/Board.hpp"

int main (){
  SetTargetFPS(60);
  InitWindow(WINDOW_HEIGHT, WINDOW_WIDTH, "Damas");
  SetExitKey(KEY_ESCAPE);
  Board board = Board();
  while(!WindowShouldClose()){
    board.Tick();
  }
  CloseWindow();
}
