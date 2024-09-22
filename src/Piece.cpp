#include "../include/Piece.hpp"

Square::Square(float x, float y, ColorEnum color) : 
  x(x), y(y), color(color)  
{}

Piece::Piece(float x, float y, ColorEnum color, Square *square) : 
  x(x), y(y), tempx(x), tempy(y),
  color(color), square(square)
{}

bool Piece::isColliding(float posX, float posY) {
   return (posX >= tempx) && (posX <= tempx + SIZESQ) && (posY >= tempy) && (posY <= tempy + SIZESQ);
}
bool Square::isColliding(float posX, float posY){
  return ( (posX >= x - (float)SIZESQ / 2) &&
           (posX <= x + (float)SIZESQ / 2) &&
           (posY >= y - (float)SIZESQ / 2) &&
           (posY <= y + (float)SIZESQ / 2));
}
