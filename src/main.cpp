#include <raylib.h>
#include "../include/Game.hpp"

int main (){
  SetTargetFPS(60);
  InitWindow(WINDOW_HEIGHT, WINDOW_WIDTH, "Damas");
  SetExitKey(KEY_ESCAPE);
  Game damas = Game();
  while(!WindowShouldClose()){
    damas.Tick();
  }
  CloseWindow();
}
