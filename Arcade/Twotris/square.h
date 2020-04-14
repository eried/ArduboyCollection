#ifndef SQUARE_H
#define SQUARE_H

#define SW 4 //Square Width

#define SHAPE_I 1
#define SHAPE_T 2
#define SHAPE_Z 3
#define SHAPE_O 4
#define SHAPE_S 5
#define SHAPE_P 6
#define SHAPE_L 7
#define TYPE_EMPTY 0
#define TYPE_SIMPLE 1
#define TYPE_SLASH 2
#define TYPE_DOTS 3
#define TYPE_4 4
#define TYPE_STONE 5
#define TYPE_FILLED 6
#define TYPE_BLINKING 10

class Square{
  public:
    byte x;
    byte y;
    byte type;
    Square(){
      this->x=0;
      this->y=0;
      this->type=0;      
    }
    Square(byte x, byte y, byte t){
      this->x=x;
      this->y=y;
      this->type=t;
    }
    void Square::draw();
};

class Piece {
  public:
    byte x;
    byte y;
    byte orientation; //todo: share the same byte with shape (4bits are plenty)
    byte shape;
    bool p1; // to know if it's belong to p1 or p2
    Square body[4]={Square(0,0,TYPE_SIMPLE),Square(0,0,TYPE_SIMPLE),Square(0,0,TYPE_SIMPLE),Square(0,0,TYPE_SIMPLE)}; 
    //Piece(bool p1);
    
    Piece(bool p1):Piece(0,0,0,p1){//:Piece(p1? 23:23+6+9*SW, 3,random(6)+1,p1){
      this->reInit(SHAPE_T);
    }
    
    Piece(int x, int y, byte s, bool p1){
      this->x=x;
      this->y=y;      
      this->orientation=0;
      this->shape=s; //todo: change square type when several
      this->p1=p1;
    }
    void Piece::update();
    void Piece::reInit(byte shape);
    void Piece::shapeShift();
    void Piece::stick();
    void Piece::turn();
    void Piece::draw();
    bool Piece::move(byte dir);
    bool Piece::checkCollision();
};

void resetOccupiedGrids();
int getIndice(int x, int y, bool p1);
int getXfromI(int i, bool p1);
int getYfromI(int i);

#endif
