
#include "globals.h"
#include "square.h"
#include "background.h"
/*
Piece(bool p1):Piece(0,0,0,p1){//:Piece(p1? 23:23+6+9*SW, 3,random(6)+1,p1){
  this->reInit();
}*/
void Square::draw(){
  int temp;
  switch(this->type){
    case TYPE_SIMPLE :
      ab.drawRect(this->x,this->y,SW,SW,1);
      break;
    case TYPE_SLASH :
      ab.fillRect(this->x,this->y,SW,SW,1);
      ab.drawLine(this->x+SW-1,this->y,this->x,this->y+SW-1,0);
      break;
    case TYPE_DOTS :
      ab.drawLine(this->x,this->y,this->x+SW-1,this->y+SW-1,1);
      ab.drawLine(this->x+2,this->y,this->x+3,this->y+1,1);
      ab.drawLine(this->x,this->y+2,this->x+1,this->y+3,1);
      break;      
    case TYPE_4 :
        ab.drawPixel(this->x+SW-1,this->y+SW-1);
        ab.fillRect(this->x,this->y,SW-1,SW-1,1);
      break;
    case TYPE_STONE :
        ab.drawPixel(this->x,this->y+SW-1);
        ab.drawLine(this->x,this->y,this->x+2,this->y,1);
        ab.drawLine(this->x+1,this->y+1,this->x+3,this->y+1,1);
      break;      
    case TYPE_FILLED:
      ab.fillRect(this->x,this->y,SW,SW,1);
      break;
    case TYPE_BLINKING:
      temp = 0==(timer%2)? 1:0;
      ab.fillRect(this->x,this->y,SW,SW,temp);
      break;
    default :
    break;
  }
}

void Piece::reInit(byte shape){
  this->shape=shape;
  this->x= p1? LB1:LB2;
  this->y= UP_BORDER;
  this->orientation=0; //depends... todo check
  if (p1)
    p1GoesToTheRight=true;
  else
    p2GoesToTheRight=true;
  //this->shapeShift();
}

void Piece::shapeShift(){
  int temp=random(7)+1;  //tODO: CHECK THIS RANDOM... I don't think it works as you want
  int temp2;
  this->shape=temp;
  switch (temp){
    case SHAPE_Z : case SHAPE_L :
      temp2=TYPE_SLASH;
    break;
    case SHAPE_O:
      temp2=TYPE_DOTS;
    break;
    case SHAPE_I :
      temp2=TYPE_4;
    break;
    case SHAPE_S :
      temp2=TYPE_STONE;
    break;
    default :
      temp2=TYPE_SIMPLE;
      //temp2=TYPE_BLINKING;
    break;
  }
  for (int i=0; i<4; i++){
    this->body[i].type=temp2;
  }
}
  
void Piece::stick(){
  int minY=64;
  int maxY=0;  
  if (this->p1){    
    for (int i=0; i<4; i++){
      occupiedGridP1[getIndice(this->body[i].x,this->body[i].y,true)]=this->body[i].type;
//      stillSquaresP1[NbStillSquaresP1+i]=this->body[i];
      if (this->body[i].y>maxY)
        maxY=this->body[i].y;
      if (this->body[i].y<minY)
        minY=this->body[i].y;           
    }
    /*
    if (NbStillSquaresP1+4<=MAXS){
      NbStillSquaresP1+=4;
      checkFullLines(minY, maxY,true);
    }
    else blinkingLinesP1=-2;  //Busted by filling the Squares array...
    */    
  }
  else { //p2
    for (int i=0; i<4; i++){
      occupiedGridP2[getIndice(this->body[i].x,this->body[i].y,false)]=this->body[i].type;
      //stillSquaresP2[NbStillSquaresP2+i]=this->body[i];
      if (this->body[i].y>maxY)
        maxY=this->body[i].y;
      if (this->body[i].y<minY)
        minY=this->body[i].y;     
    }
    /*
    if (NbStillSquaresP2+4<=MAXS){
      NbStillSquaresP2+=4;
      checkFullLines(minY, maxY,false);
    }
    else blinkingLinesP2=-2; //Busted by filling the Squares array...
    */
  }
  checkFullLines(minY, maxY,this->p1? true:false);
}

void Piece::update(){
  body[0].x=this->x;
  body[0].y=this->y;
  //body[0].type=0;
  switch (this->shape){
    case SHAPE_I:
      switch (this->orientation){
        case 1 : case 3:
          body[1].x=this->x-SW;
          body[1].y=this->y;
          body[2].x=this->x+SW;
          body[2].y=this->y;
          body[3].x=this->x+2*SW;
          body[3].y=this->y;
        break;
        case 0 : case 2:
          body[1].x=this->x;
          body[1].y=this->y-1*SW;
          body[2].x=this->x;
          body[2].y=this->y+1*SW;
          body[3].x=this->x;
          body[3].y=this->y-2*SW;
        break;
      }
    break;
    case SHAPE_T:
      switch (this->orientation){
        case 0 :
          body[1].x=this->x;
          body[1].y=this->y-SW;
          body[2].x=this->x+SW;
          body[2].y=this->y;
          body[3].x=this->x;
          body[3].y=this->y+SW;
        break;
        case 3 :
          body[1].x=this->x;
          body[1].y=this->y-1*SW;
          body[2].x=this->x+SW;
          body[2].y=this->y;
          body[3].x=this->x-SW;
          body[3].y=this->y;
        break;
        case 2 :
          body[1].x=this->x;
          body[1].y=this->y-SW;
          body[2].x=this->x-SW;
          body[2].y=this->y;
          body[3].x=this->x;
          body[3].y=this->y+SW;
        break;
        case 1 :
          body[1].x=this->x;
          body[1].y=this->y+1*SW;
          body[2].x=this->x+SW;
          body[2].y=this->y;
          body[3].x=this->x-SW;
          body[3].y=this->y;
        break;        
      }
    break;
    case SHAPE_S:
      switch (this->orientation){
        case 0 : case 2:
          body[1].x=this->x;
          body[1].y=this->y-SW;
          body[2].x=this->x+SW;
          body[2].y=this->y;
          body[3].x=this->x+SW;
          body[3].y=this->y+SW;
        break;
        case 1 : case 3:
          body[1].x=this->x;
          body[1].y=this->y-1*SW;
          body[2].x=this->x-SW;
          body[2].y=this->y;
          body[3].x=this->x+SW;
          body[3].y=this->y-SW;
        break;
      }
    break;
    case SHAPE_Z:
      switch (this->orientation){
        case 0 : case 2:
          body[1].x=this->x;
          body[1].y=this->y+SW;
          body[2].x=this->x+SW;
          body[2].y=this->y;
          body[3].x=this->x+SW;
          body[3].y=this->y-SW;
        break;
        case 1 : case 3:
          body[1].x=this->x;
          body[1].y=this->y+SW;
          body[2].x=this->x+SW;
          body[2].y=this->y+SW;
          body[3].x=this->x-SW;
          body[3].y=this->y;
        break;
      }
    break;    
    case SHAPE_L:
      switch (this->orientation){
        case 0 :
          body[1].x=this->x;
          body[1].y=this->y+SW;
          body[2].x=this->x+SW;
          body[2].y=this->y+SW;
          body[3].x=this->x;
          body[3].y=this->y-SW;
        break;
        case 1 :
          body[1].x=this->x-SW;
          body[1].y=this->y;
          body[2].x=this->x-SW;
          body[2].y=this->y+SW;
          body[3].x=this->x+SW;
          body[3].y=this->y;
        break;
        case 2 :
          body[1].x=this->x;
          body[1].y=this->y-SW;
          body[2].x=this->x-SW;
          body[2].y=this->y-SW;
          body[3].x=this->x;
          body[3].y=this->y+SW;
        break;
        case 3 :
          body[1].x=this->x+SW;
          body[1].y=this->y-SW;
          body[2].x=this->x+SW;
          body[2].y=this->y;
          body[3].x=this->x-SW;
          body[3].y=this->y;
        break;        
      }
    break; 
    case SHAPE_P:
      switch (this->orientation){
        case 0 :
          body[1].x=this->x;
          body[1].y=this->y-SW;
          body[2].x=this->x+SW;
          body[2].y=this->y-SW;
          body[3].x=this->x;
          body[3].y=this->y+SW;
        break;
        case 1 :
          body[1].x=this->x-SW;
          body[1].y=this->y;
          body[2].x=this->x+SW;
          body[2].y=this->y+SW;
          body[3].x=this->x+SW;
          body[3].y=this->y;
        break;
        case 2 :
          body[1].x=this->x;
          body[1].y=this->y-SW;
          body[2].x=this->x-SW;
          body[2].y=this->y+SW;
          body[3].x=this->x;
          body[3].y=this->y+SW;
        break;
        case 3 :
          body[1].x=this->x-SW;
          body[1].y=this->y-SW;
          body[2].x=this->x+SW;
          body[2].y=this->y;
          body[3].x=this->x-SW;
          body[3].y=this->y;
        break;        
      }
    break;     
    case SHAPE_O: default :
      body[1].x=this->x;
      body[1].y=this->y+1*SW;
      body[2].x=this->x+SW;
      body[2].y=this->y+SW;
      body[3].x=this->x+SW;
      body[3].y=this->y;    
    break;
  }
  for (int i=1; i<4;i++){ //replace out of grid squares
    if (body[i].y>128){
      body[i].x=this->x;
      body[i].y=this->y;
    }
    
  }
}
bool Piece::move(byte dir){
  bool temp;
  switch(dir){
    case MOVE_RIGHT:
      this->x+=SW;
      this->update();
      temp=this->checkCollision();
      if (temp) { // collision -> back to the previous spot
        this->x-=SW;
        this->update();
        return false;
      }
    break;
    case MOVE_LEFT:
      this->x-=SW;
      this->update();
      temp=this->checkCollision();
      if (temp) { // collision -> back to the previous spot
        this->x+=SW;
        this->update();
        return false;
      }
    break;
    case MOVE_DOWN:
      this->y+=SW;
      this->update();
      temp=this->checkCollision();
      if (temp) { // collision -> back to the previous spot
        this->y-=SW;
        this->update();
        return false;
      }
    break;    
  }
  return true;
}

bool Piece::checkCollision(){ //return true if Piece collides with something
  int temp = this->p1 ? 0:6+9*SW;
  for (int i=0;i<4;i++){
    if ((this->body[i].x>LB1+temp+9*SW)||(this->body[i].x<LB1+temp)||((this->body[i].y>63-SW)&&(this->body[i].y<127)) )
      return true;
    if (this->p1){
      if (occupiedGridP1[getIndice(this->body[i].x,this->body[i].y,true)]!=0){
        return true;
      }
    }
    else {
      if (occupiedGridP2[getIndice(this->body[i].x,this->body[i].y,false)]!=0)
        return true;
    }
  }
  return false;
}

void Piece::turn(){
  byte backUp=this->orientation;
  if (++this->orientation >=4)
    this->orientation=0;
  this->update();
  if (this->checkCollision()){
    this->orientation=backUp;
    this->update();
  }
}

void Piece::draw(){
  for (int i=0;i<4;i++){
    body[i].draw();
  }
}

void resetOccupiedGrids(){
  
  for (int i=0; i<GRID_TOT; i++){
    occupiedGridP1[i]=0;
    occupiedGridP2[i]=0;
  }
  
}

int getIndice(int x, int y, bool p1){
  int temp=p1 ? LB1:LB2;
  temp=(x-temp)/4;
  temp+=(y-UP_BORDER)/4*10;
  return temp;
}
int getXfromI(int i, bool p1){
  return ((p1?LB1:LB2)+i%10*SW);      
}
int getYfromI(int i){
  return (UP_BORDER+i/10*SW);
}

/*
int getIndice(int x, int y){ //from 2PP
  int temp=(x-LB11)/casesLength;
  temp+=(y-upBorder)/casesHeight*casesCol;
  return temp;
}
*/
