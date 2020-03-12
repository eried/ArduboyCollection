/*  Welcome to my first Arduboy Game.

        Sorry for not splitting the code in parts but it was written mainly on 
        https://felipemanga.github.io/ProjectABE/?url=new
        and I couldnt find out how to include a .h file
        
    Don't hesitate to write me if you have a question or a feedback:
    Cédric Martin  
    skaterced@hotmail.com
    
    About the Games :
    
      Menu:
        left and right to change game, A to select, B for the settings menu where
        You can change global DIFFICULTY. It will affect Trace and Pong speed, and MEMO ammount of cards (from 3X8 to 6x11)
        
      CONTROLS : As it was developped (and will surely be played often) with the Emulator, the controls are optimized for Emulator OR Arduboy
                You can change defaut Controls settings by commenting or decommenting some lines -> look for "bool forEmulator"
          Emulator (PC) :
            Pong, Trace and ReflX are played with A and B for player 1 and UP and DOWN for player 2
          Arduboy :
            Pong, Trace and ReflX are played with UP and DOWN for player 1 and A and B for player 2
            
          MEMO : Arrows for moving the cursor, A to select a card
          MILL : Arrows for moving the cursor, A to select a Stone, B to cancel selection

      RULES:
        
        Pong:   Do I Really have to explain ?
        Trace:  Survive longer than your opponent
        ReflX:  Before each round there is a new rule (normal or inverted) for the 2 kind of arrows (White on Black BackGround or Black on White Bg)
                after both players are ready and have pressed "down" (cf CONTROLS) they wait a random time and then the arrow appears.
                +1 point if you press the correct direction depending on the rule, and -1 if you press the wrong one.
                Both players can press at the same time and get the point (or lose it).
        MEMO:   select a card and flip it with button A. Flip a second card and if they math you get the point. When there is no more card,
                the player with more pointsw wins. Note: the cards are bigger if you select the minimal difficulty (3x8)
        MILL:   Th first 9 Stones can be placed anywhere. After that you must select a stone with A and place it in a free adjacent space.
                Align 3 stones on the same line to form a "mill". If you do so you can remove an oppenent stone, except if it's part of a mill.
                If you only have 3 stones left, you can move not only by following the lines but where you want.
                You win if your opponent has only 2 stones left OR if he is "stuck" with nowhere to move any of his stones.
                Look up for "Nine Men's Morris" for more information
          
          
      Hope you'll enjoy !


    Special thanks to my brother Jean-Philippe who taught me how to code and wrote the "original" Trace inspired by the movie TRON
*/

#include <Arduboy2.h>
//#include <stdlib.h>
 
Arduboy2 arduboy;
 
#define downWall 64
#define upWall 0
#define scoreTimerInit 60
#define TRACE_WAIT_ROUND 2000
//#define TRACE_FPS 10
#define PRESSED_DOWN true
#define PRESSED_UP false
#define MEMO_WAIT 3000
#define EMPTY 0
#define BLACK_STONE 1 // (P1)
#define WHITE_STONE 2 // (P2)
#define MENU 0
#define MENU2 1
#define PONG 2
#define TRACE 3
#define REFLX 4
#define MEMO 5
#define MILL 6
 
const unsigned char PROGMEM picture[] =
{
// width, height,
//128, 48,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x1f, 0x0f, 0x07, 0x07, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x07, 0x07, 0x07, 0x0f, 0x1f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x07, 0x03, 0x03, 0x03, 0x83, 0xe3, 0xe3, 0x63, 0x03, 0x03, 0x03, 0x03, 0x03, 0x87, 0xff, 0x1f, 0x07, 0x03, 0x03, 0x03, 0x83, 0xf3, 0xff, 0x7f, 0x7f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x7f, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0x7f, 0x7f, 0x7f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x7f, 0x3f, 0x3f, 0x3f, 0xbf, 0xff, 0x7f, 0x7f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0xc0, 0xc0, 0xc0, 0xe0, 0xf0, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0x7f, 0x1f, 0x07, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xe0, 0xf1, 0xf1, 0xf0, 0xf0, 0xf0, 0xf8, 0xfc, 0x3c, 0x1f, 0x03, 0x00, 0x00, 0x00, 0xc0, 0x70, 0x1e, 0x0f, 0x0f, 0x05, 0x04, 0x44, 0x46, 0x46, 0x02, 0x02, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x01, 0x81, 0xc0, 0xe0, 0xf0, 0xfc, 0x0e, 0x03, 0x01, 0x00, 0x00, 0x00, 0x24, 0x24, 0x26, 0x26, 0x20, 0xa0, 0xe0, 0xe0, 0x70, 0x1f, 0x03, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xf8, 0xfc, 0xfc, 0x3c, 0x3e, 0x3f, 0x30, 0x20, 0x00, 0x00, 0x00, 0x04, 0x04, 0x9c, 0xfc, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xf0, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x3f, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3f, 0x3f, 0x7e, 0xfe, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x06, 0x07, 0x0f, 0x0f, 0x07, 0x80, 0x80, 0x80, 0xc0, 0xe0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3e, 0x3e, 0x3e, 0x3c, 0x3c, 0xbc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x1f, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x38, 0x3c, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1e, 0x1e, 0x0e, 0x00, 0x80, 0x80, 0xc0, 0xe0, 0xf8, 0x7f, 0x4f, 0x47, 0x67, 0x63, 0x23, 0x23, 0x03, 0x03, 0x03, 0x03, 0x07, 0xc7, 0xff, 0x3f, 0x1f, 0x0f, 0x0f, 0x07, 0x83, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xff, 0x3f, 0x07, 0x01, 0x00, 0x00, 0x00, 0x10, 0x18, 0x0f, 0x07, 0x03, 0xc3, 0xc3, 0xe3, 0xf3, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xc3, 0xc0, 0xc0, 0xc0, 0xc0, 0xf0, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xc1, 0xc0, 0xc0, 0xc0, 0xc4, 0xc4, 0xc4, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf0, 0xff, 0xff, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc7, 0xc7, 0xc7, 0xe3, 0xf3, 0xff, 0xc7, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0xfe, 0xf0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xeb, 0xe3, 0xff, 0xb3, 0xaf, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0x9d, 0xbe, 0xbe, 0xbe, 0xc7, 0xab, 0xab, 0xa5, 0xbd, 0xcf, 0xb7, 0x97, 0xc1, 0xbf, 0x83, 0xf7, 0xfb, 0xff, 0x85, 0xff, 0xcf, 0xb7, 0xb7, 0xff, 0xff, 0xff, 0x80, 0xf9, 0xf3, 0xf9, 0x80, 0xff, 0xdf, 0xab, 0xab, 0xc7, 0xbf, 0x83, 0xf7, 0xfb, 0xff, 0xfb, 0xc1, 0xbb, 0xff, 0x85, 0xff, 0x83, 0xf7, 0xfb, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 
};
//char c=0;
int scoreTimer=0;
int timer=0;
byte difficulty=2;  //must be between 1-4
int game=MENU;
int temp=0;
bool p1Playing=true; //false: p2's turn
bool selected=false; //MILL and MEMO - when a player has selected something - ReflX True: bold arrow
int selectedI=-1;
bool removing=false;
bool blink=true;
int blinkTimer=0;
bool arrowInverted=false;
bool boldArrowInverted=false;
bool pointDown=false;
byte casesLength=8;
byte casesHeight=11;
byte casesCol=7+difficulty;
byte casesRow=2+difficulty;
int leftBorder=30;
int upBorder=-1;

#if (THIS_IS_REAL_HARDWARE == 1) 
#define TRACE_FPS 5
#else
#define TRACE_FPS 10
#endif


  //Controls designed for Arduboy
bool forEmulator = false;  // ToDo : remove this and change Menu. No more need for this bool
byte P1_LEFT=UP_BUTTON;
byte  P1_RIGHT=DOWN_BUTTON;
byte  P2_RIGHT=B_BUTTON;
byte  P2_LEFT=A_BUTTON;

/*
  //Controls designed for Emulator
bool forEmulator = true;
byte P2_RIGHT=UP_BUTTON;
byte P1_LEFT=A_BUTTON;
byte P1_RIGHT=B_BUTTON;
byte P2_LEFT=DOWN_BUTTON; 
*/
 
class Player {
  public :
    int x,y;
    int length;
    byte dir;
    int score;
    Player(int X, int Y);
};
Player::Player(int X, int Y)
{
  this->x=X;
  this->y=Y;
  this->length=14;  //becomes "Number of Stones left" in MILL
  this->dir=0;
  this->score=0;
}
class Balle {
  public :
    int x,y, vx,vy;
    void affiche (void);
    void stop (void);
    void init (void);
    Balle (void);
    Balle (int X, int Y, int vx, int vy);
};
Balle::Balle(int X, int Y, int vx, int vy)
{
  this->x=X;
  this->y=Y;
  this->vx=vx;
  this->vy=vy;  
}
Balle::Balle(void)  //not working
{
  this->init(); 
}
void Balle::init(void){  //to do: add random
  this->x=64;
  this->y=30;
  //srand(p1.y);
  int temp=-2+rand()%5;
  if (0==temp){ 
    if (rand()%2>=1){
      temp++;
    }
    else {
      temp--;
    }
  }
  this->vx=temp;
  temp=-2+rand() %5;
  this->vy=temp;
}
void Balle::affiche (void)
{
  arduboy.fillCircle(this->x,this->y,2);
}
void Balle::stop(void){
  this->vx=0;
  this->vy=0;
}
 
class Player p1(4,0);
class Player p2(122,20);
//class Balle balle();
class Balle balle(12,20,1,-2);
//balle.init(); // Y U no work ???!!
char symbolArray [66]={(char)228,(char)228 ,(char)15,(char)15,(char)10,(char)10,(char)14,(char)14,(char)232,(char)168,(char)197,
                      (char)225,(char)225,(char)240,(char)240,(char)175,(char)175,(char)206,(char)206,(char)232,(char)168,(char)197,
                      (char)64,(char)64,(char)35,(char)35,(char)236,(char)236,(char)25,(char)3,(char)3,(char)25,(char)12,
                      (char)247,(char)247,(char)12,/*->medium*/(char)234,(char)18,(char)18,(char)2,(char)2,(char)20,(char)20,(char)234,
                      (char)38,(char)38,(char)5,(char)5,(char)24,(char)24,/*->hard*/(char)36,(char)36,(char)37,(char)37,(char)237,
                      (char)156,(char)156,(char)174,(char)174,(char)4,(char)4,(char)155,(char)155,(char)157,(char)157,(char)237};
void newTraceGame(void){
  arduboy.clear();
  arduboy.setCursor(40,30);
  arduboy.print(p1.score);
  arduboy.print(" : ");
  arduboy.print(p2.score);
  arduboy.display();
  delay(TRACE_WAIT_ROUND);
  arduboy.clear();
  p1.x=10;
  p1.y=30;
  p1.dir=1;
  p2.x=118;
  p2.y=30;
  p2.dir=3;
  arduboy.drawRect(0,0,128,64,1);
}
void newReflXGame(void){
  arduboy.clear();
  arduboy.setCursor(0,0);
  arduboy.print("Next Round :");
  arduboy.drawChar(1,11,24,1,0,1);
  arduboy.drawChar(8,11,25,1,0,1);
  arduboy.setCursor(16,11);
  if (random(100)>=50){
    arduboy.print(" are normal");
    arrowInverted=false;
  }
  else{
    arduboy.print(" are inverted");
    arrowInverted=true;
  }
  arduboy.fillRect(0,21,15,8,1);
  arduboy.drawChar(1,21,24,0,1,1);
  arduboy.drawChar(8,21,25,0,1,1);
  arduboy.setCursor(16,20);
  if (random(100)>=50){
    arduboy.print(" are normal");
    boldArrowInverted=false;
  }
  else{
    arduboy.print(" are inverted");
    boldArrowInverted=true;
  }
  arduboy.setCursor(0,45);
  arduboy.print("Press both 'down'");
  arduboy.setCursor(0,55);
  arduboy.print("buttons when ready");
  arduboy.display();
  while (!(arduboy.pressed(P1_RIGHT)&&arduboy.pressed(P2_LEFT))){
    delay(10);
  }
  arduboy.clear();
  timer=10+random(600);
}

void drawCurs(int x, int y, bool print){
  byte temp=0;
  if (difficulty>1){
    temp=1;
  }
  arduboy.drawRect(p1.x,p1.y,casesLength+temp,casesHeight+temp,print? 1:0);
}

void drawCard(int i, byte face){ //2: symbol, 1: back, other: empty
  byte temp=1;
    if (1==difficulty){
    temp=2;
  }
  
  if (1==face){
    arduboy.drawRect(leftBorder+1+i%casesCol*casesLength,i/casesCol*casesHeight+upBorder+1,casesLength-temp,casesHeight-temp,0);
    arduboy.drawChar(leftBorder+2+(i%casesCol)*casesLength,i/casesCol*casesHeight+2+upBorder,symbolArray[i],1,0,temp); 
  }
  else if (2==face){
    arduboy.drawChar(leftBorder+2+(i%casesCol)*casesLength,i/casesCol*casesHeight+upBorder+2,(char)178,1,0,temp); 
    arduboy.drawRect(leftBorder+1+i%casesCol*casesLength,i/casesCol*casesHeight+upBorder+1,casesLength-temp,casesHeight-temp,1);
  }
  else {
    arduboy.fillRect(leftBorder+2+i%casesCol*casesLength,i/casesCol*casesHeight+upBorder+2,casesLength-temp,casesHeight-temp,0);
  }  
}
int getIndice(int x, int y){ //TO DO
  //arduboy.fillRect(x+1,y+1,7,10,fill);
  int temp=(x-leftBorder)/casesLength;
  temp+=(y-upBorder)/casesHeight*casesCol;//  divided by 11 multiplied by 11 (coincidence)
  return temp;
}
void shuffle (int size){
  char c=0;
  int r1,r2=0;
  for (int i=0; i<200; i++){
    r1=random(size);
    r2=random(size);
    c=symbolArray[r1];
    symbolArray[r1]=symbolArray[r2];
    symbolArray[r2]=c;
  }
}  
void turnUpdate(void){ /////////////////////////////////////// score ///////////////////////  score ///////////////////////
  if ((MEMO==game)&&(1==difficulty)) { // for MEMO that have bigger cards in difficulty 1
    arduboy.fillRect(0,0,17,64,0);
    if (p1Playing){
      arduboy.setCursor(1,6);
      arduboy.print("P1");
    }
    else{
      arduboy.setCursor(1,39);
      arduboy.print("P2");
    }
  }
  else {
    arduboy.fillRect(0,0,26,64,0);
    if (p1Playing){
      arduboy.setCursor(1,6);
      arduboy.print("P1's");
      arduboy.setCursor(1,14);
      arduboy.print("turn");
    }
    else{
      arduboy.setCursor(1,39);
      arduboy.print("P2's");
      arduboy.setCursor(1,47);
      arduboy.print("turn");
    }
  }
  arduboy.setCursor(5,24);
  arduboy.print(p1.score);
  arduboy.setCursor(5,57);
  arduboy.print(p2.score);
  if (MILL==game){
    if (removing){
      arduboy.setCursor(1,30);
      arduboy.print("Removing");
    }
    arduboy.drawCircle(20,27,3,1);
    arduboy.fillCircle(20,60,3,1);
  }
}

bool checkPressed(bool down){
  if (selected){ //bold arrow
    if (!boldArrowInverted){
      if (down==pointDown){
        return true;
      }
      else return false;
    }
    else { //bold arrow is inverted
      if (down!=pointDown){
        return true;
      }
      else return false;
    }
  }
  else { //normal arrow
    if (!arrowInverted){
      if (down==pointDown){
        return true;
      }
      else return false;
    }
    else { //bold arrow is inverted
      if (down!=pointDown){
        return true;
      }
      else return false;
    }
  }
}

void drawSelector(int i){
  int x=(i%7)*8+58;
  int y=(i/7)*8+8;
  arduboy.drawLine(x-4,y-4,x-2,y-2,0);
  arduboy.drawLine(x-4,y+4,x-2,y+2,0);
  arduboy.drawLine(x+2,y+2,x+4,y+4,0);
  arduboy.drawLine(x+2,y-2,x+4,y-4,0);
}
int drawStone(int i, bool color){ //black 0 white 1
  int x=(i%7)*8+58;
  int y=(i/7)*8+8;
  arduboy.fillCircle(x,y,3,0);
  if (color){
    arduboy.fillCircle(x,y,2,1);
  }
}
void drawMill(void){
  arduboy.fillRect(50,0,65,65,1);
  arduboy.drawRect(58,8,49,49,0);
  arduboy.drawRect(66,16,33,33,0);
  arduboy.drawRect(74,24,17,17,0);
  arduboy.drawLine(82,8,82,56,0);
  arduboy.drawLine(58,32,105,32,0);
  arduboy.fillRect(75,25,15,15,1);  
}
void drawStones(void){
  for (int i=0; i<49; i++){
    if (i==selectedI){
      if (blink) {
        if (BLACK_STONE==symbolArray[i]){
          drawStone(i,0);
        }
        else if (WHITE_STONE==symbolArray[i]){
          drawStone(i,1);
        }
      }
    }
    else {
      if (BLACK_STONE==symbolArray[i]){
      drawStone(i,0);
      }
      else if (WHITE_STONE==symbolArray[i]){
        drawStone(i,1);
      }
    }
  }
}
bool checkMill(int ind, int color){ //check if same line (or col) as ind, has two other same colored stones
  byte xR,xC=0;
  int temp=0;
  for (int i=0; i<49; i++){ // check col.
    if (ind%7==i%7){
      if (i%7==3) {
        if ((24-i)*(24-ind)>0){
          if (symbolArray[i]==color)
            xC++;
        }
      }
      else {
        if (symbolArray[i]==color)
          xC++;
      }
    }
    if (ind/7==i/7) { // check rows
      if (i/7==3){
        if ((24-i)*(24-ind)>0){
          if (symbolArray[i]==color)
            xR++;
        }
      }   
      else {
        if (symbolArray[i]==color)
          xR++;
      }
    }
  }
  if ((xR==3)||(xC==3)){
    return true;
  }
  return false;
}
bool checkLegalMove(int i1, int i2, bool canJump){
  if (symbolArray[i2]!=EMPTY){
    return false;
  }
  if (canJump){
    return true; 
  }
  int temp=i1/7;
  if (i2/7==temp){ //same row
    if ((temp==0)||(temp==6)){
      if (abs(i1-i2)==3){
        return true;
      }
    }
    else if ((temp==1)||(temp==5)){
      if (abs(i1-i2)==2){
        return true;
      }
    }
    else if ((temp==2)||(temp==4)){
      if ((i2%7>1)&&(i2%7<5)&&(abs(i1-i2)==1)){
        return true;
      }
    }
    else if (temp==3){ // temp==3 symbolArray[22]=4
      if (abs(i1-i2)==1){
        return true;
      }
    }
  }
  temp=i1%7;
  if (i2%7==temp){ // same col.
    if ((temp==0)||(temp==6)){
      if (abs(i1/7-i2/7)==3){
        return true;
      }
    }
    else if ((temp==1)||(temp==5)){
      if (abs(i1/7-i2/7)==2){
        return true;
      }
    }
    else if ((temp==2)||(temp==4)){
      if ((i2/7>1)&&(i2/7<5)&&(abs(i1/7-i2/7)==1)){
        return true;
      }
    }
    else if (temp==3){ // temp==3 symbolArray[22]=4
      if (abs(i1/7-i2/7)==1){
        return true;
      }
    }
  }
  return false;
}
bool checkLose(int color){
  int temp=0;
  for (int i=0;i<49;i++){
    if (symbolArray[i]==color){
      temp++;
      for (int j=0;j<49;j++){
        if (checkLegalMove(i,j,false)) { 
          return false;
        }
      }
    }
  }
  if (temp==3){ //because you can't get stuck if you can jump
    return false;
  }
  return true;
}
bool checkRemoving (int color) { // check if one or more stone(s) is removable (not in a mill)
  for (int i=0;i<49;i++){
    if (symbolArray[i]==color){
      if (!checkMill(i,color)){
        return true;
      }
    }
  }
  return false;
}
 
void setup() { // SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS  Setup SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
  
  if (0==game){
    arduboy.begin();
    arduboy.setFrameRate(60);
  }
  else if (PONG==game){
    arduboy.setFrameRate(30+difficulty*5);
    p1.x=4;
    p1.y=20;
    p2.x=122;
    p2.y=20;
  }
  else if (TRACE==game){
    arduboy.setFrameRate(TRACE_FPS+difficulty*5);
    newTraceGame();
  }
  else if (REFLX==game){
    newReflXGame();
  }
  else if (MEMO==game){
    arduboy.clear();
    casesCol=7+difficulty;
    casesRow=2+difficulty;
    
    if (1==difficulty){
      leftBorder-=12;
      upBorder=1;
      casesHeight=20;
      casesLength=14;
    }
    p1.x=leftBorder;
    p1.y=upBorder;    
    int temp=casesCol*casesRow;
    for (int i=temp; i<66; i++){
      symbolArray[i]=0;
    }
    shuffle(temp);
    for (int i=0; i<temp; i++){
      drawCard(i,2);
    }
    turnUpdate();
  }
  else if (MILL==game){
    p1.score=p1.length=9; //Score is the nb of stone to put down. length is the total number of stones per player
    p2.score=p2.length=9;
    p1.x=50;
    p1.y=8;
    casesCol=7;
    casesRow=7;
    casesHeight=8;
    leftBorder=50;
    upBorder=8;
    for (int i=0; i<49; i++){
      if ((((0==i%7)||(6==i%7))&&((i/7==0)||(i/7==6)))||
         (((1==i%7)||(5==i%7))&&((i/7==1)||(i/7==5)))||
         (((2==i%7)||(4==i%7))&&((i/7==2)||(i/7==4)))||
         (i/7==3)||(i%7==3)  )    {
        symbolArray[i]=EMPTY;
      }
      else {
        symbolArray[i]=4;
      }
      symbolArray[24]=4;
    }
  }
  else {
    arduboy.clear();
  }
}
 
void loop() {
  //testP++; //for .h testing (doesn't work )
  //timer++;
  //arduboy.pollButtons();  
 
  if (!(arduboy.nextFrame()))
    return;
    
  arduboy.pollButtons();    
    
  if ((MENU==game)||(MENU2==game)||(PONG==game)||(MILL==game)){
    arduboy.clear(); //IF NOT MEMO
  }
  if (MENU==game){  
    timer++;
    arduboy.drawBitmap(0,0,picture,128,48,WHITE);
    arduboy.drawChar(2,50,17,1,0,1);
    arduboy.setCursor(10,49);
    switch(p1.x){
      case (PONG):
        arduboy.print("      Pong  ----");
      break;
      case (TRACE):
        arduboy.print("    - Trace ---");
      break;
      case (REFLX):
        arduboy.print("   -- ReflX --");
      break;
      case (MEMO):
        arduboy.print("  --- Memo -");
      break;
      case (MILL):
        arduboy.print(" ---- Mill");
      break;
    }
    //arduboy.print(TRACE_FPS);
    
    arduboy.drawChar(120,50,16,1,0,1);
    arduboy.setCursor(1,57);
    arduboy.print("A: Select    B: Param");
  
    if (arduboy.justPressed(RIGHT_BUTTON))
    {
      if (p1.x<MILL){
        p1.x++;
      }
    }
    if (arduboy.justPressed(LEFT_BUTTON))
    {
      if (p1.x>PONG){
        p1.x--;
      }
    }
    if (arduboy.justPressed(B_BUTTON))
    {
      game=MENU2;
      arduboy.clear();
    }    
    if (arduboy.justPressed(A_BUTTON))
    {
      arduboy.initRandomSeed();
      randomSeed(timer*37);
      game=p1.x;
      setup();
    }  
  }
  else if (MENU2==game){  
    timer++;
    arduboy.setCursor(10,10);
    arduboy.print("Difficulty : ");
    arduboy.print(difficulty);
    arduboy.setCursor(10,20);
    arduboy.print("Controls : " );
    arduboy.print(forEmulator ? "PC":"Arduboy");
    arduboy.setCursor(10,40);
    arduboy.print("No sound");
    arduboy.setCursor(1,55);
    arduboy.print("A: Change    B: Back");
    
    arduboy.drawChar(0,p1.y*10+10,16,1,0,1);
 
  
    if (arduboy.justPressed(DOWN_BUTTON))
    {
      if (p1.y<1){
        p1.y++;
      }
    }
    if (arduboy.justPressed(UP_BUTTON))
    {
      if (p1.y>0){
        p1.y--;
      }
    }
    if (arduboy.justPressed(A_BUTTON))
    {
      switch (p1.y){
        case 0:
          if (++difficulty==5)
            difficulty=1;
        break;
        case 1:
          forEmulator = !forEmulator;
          if (forEmulator) {
            P2_RIGHT=UP_BUTTON;
            P1_LEFT=A_BUTTON;
            P1_RIGHT=B_BUTTON;
            P2_LEFT=DOWN_BUTTON;
          }
          else {
            P1_LEFT=UP_BUTTON;
            P1_RIGHT=DOWN_BUTTON;
            P2_RIGHT=B_BUTTON;
            P2_LEFT=A_BUTTON;
          }
        break;
      }
      
    }
    if (arduboy.justPressed(B_BUTTON))
    {
      game=MENU;
      arduboy.clear();
    }     
  } 
  else if (PONG==game){     //  ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||    Pong   |||||||||||||||||||||||||||||||||||||||||
    
    arduboy.drawRect(0,0,128,64,1);
    arduboy.fillRect(p1.x,p1.y,2,p1.length,1);
    arduboy.fillRect(p2.x,p2.y,2,p2.length,1);
    
   if (arduboy.pressed(P1_LEFT))
    {
      if (p1.y>upWall+1){
        p1.y--;
      }
    }
   if (arduboy.pressed(P1_RIGHT))
    {
      if (p1.y+p1.length<downWall-1){
        p1.y++;
      }
    }
    
   if (arduboy.pressed(P2_RIGHT))
    {
      if (p2.y>upWall+1){
        p2.y--;
      }
    }
   if (arduboy.pressed(P2_LEFT))
    {
      if (p2.y+p2.length<downWall-1){
        p2.y++;
      }
    }
    
    if (scoreTimer>0){ // *********** someone scored ****
      if (0<=scoreTimer--){
        balle.init();
      }
      arduboy.setCursor(50,45);
      arduboy.print(p1.score);
      arduboy.print(" - ");
      arduboy.print(p2.score);
    }
    // *************  calculate Ball position
    else {
      balle.x+=balle.vx;
      balle.y+=balle.vy;
      
      if (balle.y<upWall){ // upper wall
        balle.y*=-1;
        balle.vy*=-1;
      }
      if (balle.y>downWall){ // down wall
        balle.y=balle.y-2*(balle.y-downWall);
        balle.vy*=-1;
      }
      
      if (0>=balle.x)
      {
        balle.stop();
        p2.score++;
        scoreTimer=scoreTimerInit;
      }
      if (128<=balle.x)
      {
        balle.stop();
        p1.score++;
        scoreTimer=scoreTimerInit;
      }      
      if (balle.x<p1.x+2){
        if ((balle.y>p1.y)&&(balle.y<p1.y+p1.length)){ //  left player
          balle.x=balle.x+2*(p1.x+2-balle.x);
          balle.vx*=-1;
        }
        else if (balle.y==p1.y) {
          balle.vy=balle.vy==0 ? -1 : abs(balle.vy)*(-1);
          balle.vx*=-1;
        }
        else if (balle.y==p1.y+p1.length) {
          balle.vy=balle.vy==0 ? 1 : abs(balle.vy);
          balle.vx*=-1;
        }
      }
      if (balle.x>p2.x){
        if ((balle.y>p2.y)&&(balle.y<p2.y+p2.length)){ //  right player
          balle.x=balle.x+2*(p2.x+2-balle.x);
          balle.vx*=-1;
        }
        else if (balle.y==p2.y) {
          balle.vy=balle.vy==0 ? -1 : abs(balle.vy)*(-1);
          balle.vx*=-1;
        }
        else if (balle.y==p2.y+p2.length) {
          balle.vy=balle.vy==0 ? 1 : abs(balle.vy);
          balle.vx*=-1;
        }
      }
    }
    balle.affiche();
  }
  
  else if (game==TRACE) // ---------------------------------------------------------------- Trace  -----------------------------
  {
    if (arduboy.justPressed(P1_LEFT)){
      if (0==p1.dir){
        p1.dir=3;
      }
      else {
        p1.dir--;
      }
    }
    if (arduboy.justPressed(P1_RIGHT)){
      p1.dir++;
      if (p1.dir>3){
        p1.dir=0;
      }
    }
    if (arduboy.justPressed(P2_LEFT)){
      if (0==p2.dir){
        p2.dir=3;
      }
      else {
        p2.dir--;
      }
    }
    if (arduboy.justPressed(P2_RIGHT)){
      p2.dir++;
      if (p2.dir>3){
        p2.dir=0;
      }
    }    
      switch(p1.dir){   //player 1 moves
        case 0:
          p1.y--;
        break;
        case 1:
          p1.x++;
        break;
        case 2:
          p1.y++;
        break;
        case 3:
          p1.x--;
        break;
      }
      switch(p2.dir){   //player 2 moves
        case 0:
          p2.y--;
        break;
        case 1:
          p2.x++;
        break;
        case 2:
          p2.y++;
        break;
        case 3:
          p2.x--;
        break;
      }
      
      if((p1.x==p2.x)&&(p1.y==p2.y)){ //draw
        p1.score++;
        p2.score++;
        newTraceGame();
      }
      
      if(arduboy.getPixel(p1.x,p1.y)){
        //arduboy.print("BLAM!");  //for now...
        p2.score++;
        newTraceGame();
      }
      if(arduboy.getPixel(p2.x,p2.y)){
        //arduboy.print("BIM!");  //for now...
        p1.score++;
        newTraceGame();
      }
      arduboy.drawPixel(p1.x,p1.y,1);
      arduboy.drawPixel(p2.x,p2.y,1);
  }
  else if (REFLX==game){ // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ReflX xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  byte scoreChange=0; // ( 0 no change, 1 correct, 2 false ) for p1 <<2 for p2
    if (!((arduboy.pressed(DOWN_BUTTON))||(arduboy.pressed(UP_BUTTON))||(arduboy.pressed(A_BUTTON))||(arduboy.pressed(B_BUTTON)))){
      timer--;
    }
    if (0==timer){
      if (random(100)>50){
        selected=false; // normal arrow
        if (random(100)>50){
          pointDown=false;
          arduboy.drawChar(55,22,24,1,0,3);
        }
        else {
          pointDown=true;
          arduboy.drawChar(55,22,25,1,0,3);
        }
      }
      else {
        selected=true;
        if (random(100)>50){
          pointDown=false;
          arduboy.drawChar(52,22,0,0,1,3);  
          arduboy.drawChar(55,22,24,0,1,3);
        }
        else {
          pointDown=true;
          arduboy.drawChar(52,22,0,0,1,3);
          arduboy.drawChar(55,22,25,0,1,3);
        }
      }
    }
    if ((timer<0)&&(0==scoreChange)){
      if ((arduboy.justPressed(DOWN_BUTTON)||arduboy.justPressed(UP_BUTTON))||(arduboy.justPressed(B_BUTTON)||arduboy.justPressed(A_BUTTON))) { 
        if (arduboy.justPressed(P1_RIGHT)||arduboy.justPressed(P1_LEFT)) { //only p1 has pressed
           if (arduboy.justPressed(P1_RIGHT)){
             if (checkPressed(PRESSED_DOWN)){
               scoreChange+=1;
             }
             else {
               scoreChange+=2;
             }
           }
           else if (arduboy.justPressed(P1_LEFT)){
             if (checkPressed(PRESSED_UP)){
               scoreChange+=1;
             }
             else {
               scoreChange+=2;
             }
           }
        }
        if (arduboy.justPressed(P2_RIGHT)||arduboy.justPressed(P2_LEFT)) { //only p1 has pressed
          if (arduboy.justPressed(P2_LEFT)){
            if (checkPressed(PRESSED_DOWN)){
            scoreChange+=4;
            }
            else {
            scoreChange+=8;
            }
          }
          else if (arduboy.justPressed(P2_RIGHT)) {
            if (checkPressed(PRESSED_UP)){
             scoreChange+=4;
            }
            else {
             scoreChange+=8;
            }
          }
        }
      }
      if (scoreChange!=0){
        if ((scoreChange&2)==2){
          p1.score--;
          arduboy.drawChar(2,45,'x',1,0,1);
        }
        if ((scoreChange&1)==1){
          p1.score++;
          //arduboy.drawChar(2,45,'v',1,0,1);
          arduboy.drawLine(3,47,5,49,1);
          arduboy.drawLine(5,49,9,40,1);
        }
        if ((scoreChange&4)==4){
          p2.score++;
          //arduboy.drawChar(115,45,'v',1,0,1);
          arduboy.drawLine(117,47,119,49,1);
          arduboy.drawLine(119,49,123,40,1);
        }
        if ((scoreChange&8)==8){
          p2.score--;
          arduboy.drawChar(115,45,'x',1,0,1);
        }
        arduboy.setCursor(49,10);
        arduboy.print(p1.score);
        arduboy.print(" : ");
        arduboy.print(p2.score);
        //arduboy.print(scoreChange);
          
        arduboy.display();
        delay(3000);
        newReflXGame();
      }
    }
  }
  
  else if (MEMO==game){  // ############################################  MEMO #################################
    if (arduboy.justPressed(UP_BUTTON)){
      if (p1.y>upBorder){
        drawCurs(p1.x,p1.y,false);
        p1.y-=casesHeight;
      }
    }
    if (arduboy.justPressed(DOWN_BUTTON)){
      if (p1.y<50){ //?
        drawCurs(p1.x,p1.y,false);
        p1.y+=casesHeight;
      }
    }
    if (arduboy.justPressed(RIGHT_BUTTON)){
      if (p1.x<105){
        drawCurs(p1.x,p1.y,false);
        p1.x+=casesLength;
      }
    }
    if (arduboy.justPressed(LEFT_BUTTON)){
      if (p1.x>leftBorder){
        drawCurs(p1.x,p1.y,false);
        p1.x-=casesLength;
      }
      
    }
    if (arduboy.justPressed(A_BUTTON)){
      int temp=0;
      if (!selected){
        
        if(selectedI!=getIndice(p1.x,p1.y)){
          selectedI=getIndice(p1.x,p1.y);
          if (symbolArray[selectedI]!=0){
            drawCard(selectedI,1);
            selected=true;
          }
        }
      }
      else { //if (selected){
        temp=getIndice(p1.x,p1.y);
        if ((temp!=selectedI)&&(symbolArray[temp]!=0)){
          drawCard(temp,1);
          arduboy.display();
          delay(MEMO_WAIT);
          if (symbolArray[temp]==symbolArray[selectedI]){ // win a point
            symbolArray[temp]=symbolArray[selectedI]=0;
           drawCard(temp,0);
            drawCard(selectedI,0);
            arduboy.display();
            selected=false;
            if (p1Playing){
              p1.score++;
            }
            else {
              p2.score++;
            }
            if (p1.score+p2.score==casesCol*casesRow/2){
              arduboy.clear();
              arduboy.setCursor(24,30);
              if (p1.score==p2.score){
                arduboy.print("   Draw !");
              }
              else {
                arduboy.print("Player ");
                arduboy.print(p1.score>p2.score ? "1":"2");
                arduboy.print(" wins");
              }
              arduboy.display();
              while("why write a symbolArrayInit when you can infite loop and reset"); 
            }
          }
          else {  //2nd card is different
            drawCard(temp,2);
            drawCard(selectedI,2);
            p1Playing=!p1Playing;
            //nselectedI=0;
            selected=false;            
          }
        }
        turnUpdate();
      }
    }
    drawCurs(p1.x,p1.y,blink ? true:false);
    //arduboy.drawRect(p1.x,p1.y,casesLength+1,casesHeight+1,blink ? 1:0);
    if (blinkTimer++>10) { // Blink speed ?
      blink=!blink;
      blinkTimer=0;
    }
  }
  
  else if (MILL==game){  // -----------------++--+--++-+-------+-----+-+----++ MILL ++--+-++--++--++--+---++-++
    if (arduboy.justPressed(UP_BUTTON)){
      if (p1.y>8){
        p1.y-=8;
      }
    }
    if (arduboy.justPressed(DOWN_BUTTON)){
      if (p1.y<56){ 
        p1.y+=8;
      }
    }
    if (arduboy.justPressed(RIGHT_BUTTON)){
      if (p1.x<98){
        p1.x+=8;
      }
    }
    if (arduboy.justPressed(LEFT_BUTTON)){
      if (p1.x>50){
        p1.x-=8;
      }
    }
    if (arduboy.justPressed(B_BUTTON)){
      selected=false;
      selectedI=-1;
    }
    if (arduboy.justPressed(A_BUTTON)){
      int temp=getIndice(p1.x,p1.y);
      if (removing){
        if (!checkMill(temp,p1Playing? WHITE_STONE : BLACK_STONE)){
          removing=false;
          symbolArray[temp]=EMPTY;
          if (p1Playing){
            p2.length--;
            if (p2.length<3){
              arduboy.setCursor(20,30);
              arduboy.print("P1 Wins");
              arduboy.display();
              while("Never gonna give you up");
            }
          }
          else {
            p1.length--;
            if (p1.length<3){
              arduboy.setCursor(20,30);
              arduboy.print("P2 Wins");
              arduboy.display();
              while("Never gonna let you down");
            }
          }      
          p1Playing=!p1Playing;
        }
      }
      else if (p1.score+p2.score>0){
        if (checkLegalMove(0,temp,true)){
          if (p1Playing){
            symbolArray[temp]= BLACK_STONE ;
            p1.score--;
            if (checkMill(temp,BLACK_STONE)){
              if (checkRemoving(WHITE_STONE)){
                removing=true;
              }
              else{
                arduboy.print("Can't remove Stone");
                arduboy.display();
                delay(2000);
                p1Playing=false;
              }
            }
            else {
              p1Playing=false;
            }
          }
          else {
            symbolArray[temp]= WHITE_STONE ;
            p2.score--;
            if (checkMill(temp,WHITE_STONE)){
              if (checkRemoving(BLACK_STONE)){
                removing=true;
              }
              else{
                arduboy.print("Can't remove Stone");
                arduboy.display();
                delay(2000);
                p1Playing=false;
              }
            }
            else {
              p1Playing=true;
            }
          }
        }
      }
      else  {
        if (!selected){
          if (((p1Playing)&&symbolArray[temp]==BLACK_STONE)||((!p1Playing)&&symbolArray[temp]==WHITE_STONE)){
            selectedI=temp;
            selected=true;
          }
        }
        else {
          if (checkLegalMove(selectedI,temp,p1Playing? p1.length==3:p2.length==3)){
            symbolArray[temp]=symbolArray[selectedI];
            symbolArray[selectedI]=EMPTY;
            selectedI=-1;
            selected=false;
            if (checkMill(temp,p1Playing? BLACK_STONE : WHITE_STONE )){
              if (checkRemoving(p1Playing? WHITE_STONE : BLACK_STONE)){
                removing=true;
              }
              else{
                arduboy.print("no stone available");
                arduboy.display();
                delay(2000);
                p1Playing=!p1Playing;
              }
            }
            if (checkLose(p1Playing? WHITE_STONE : BLACK_STONE)){
              drawMill();
              drawStones();
              arduboy.print("Player");
              arduboy.println(p1Playing? 2:1);
              arduboy.println("can't move");
              arduboy.println("");
              arduboy.print("Player");
              arduboy.println(p1Playing? 1:2);
              arduboy.println("won !");
              arduboy.display();
              while(true); //inite loop: see infinite loop
            }
            if (!removing) {
              p1Playing=!p1Playing;
            }
          }
        }
      }
    }
    drawMill();
    turnUpdate();
    drawStones();
 
    if (blinkTimer++>10){
      blinkTimer=0;
      blink=!blink;
    }
    if (blink){
      drawSelector(getIndice(p1.x,p1.y));
    }
    if (temp>48)
      temp=0;
  }
  else {
    arduboy.print("game not implemented yet");
  }
  arduboy.display();
}
