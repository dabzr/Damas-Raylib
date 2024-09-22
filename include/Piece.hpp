#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800
#define SIZESQ 96
#define BORDER_THICKNESS 16

typedef enum{
  Black, White, Red, Blue
}ColorEnum;


class Square {
  public:
  Square(float x, float y, ColorEnum color);
  Square(){};
  float x, y;
  ColorEnum color;
  bool isColliding(float posX, float posY);
};


class Piece{
  public:
  Piece(float x, float y, ColorEnum color, Square *square);
  Piece(){};
  float x, y;
  float tempx, tempy;
  ColorEnum color;
  bool alive = true;
  Square *square;
  bool isColliding(float posX, float posY);
};

