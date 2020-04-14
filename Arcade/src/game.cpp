
#include "globals.h"
#include "background.h"
#include "square.h"
#include "game.h"

#define MOVE_BUTTON_TRIGGER 3
#define TURN_BUTTON_TRIGGER 5
//p1GoesToTheRight=true;
//p2GoesToTheRight=false;
//prout=true;

void control(Piece* P){
  if (ab.justPressed(LEFT_BUTTON)){
    ab.setCursor(40,20);
    ab.print(F("* pause *"));
    ab.display();
    delay(100);
    while(!ab.pressed(LEFT_BUTTON));
  }
  if (P->p1){
    if (ab.pressed(P1_TURN)){
      if (++buttonTimerTurnP1>TURN_BUTTON_TRIGGER){
        buttonTimerTurnP1=-3;
        while (P->move(MOVE_DOWN));
        P->stick();
        return;
      }
    }
    if (ab.pressed(P1_MOVE)){
      //if (buttonTimerMoveP1>=MOVE_BUTTON_TRIGGER){
      if ((0==buttonTimerMoveP1)||(buttonTimerMoveP1>=MOVE_BUTTON_TRIGGER)){
        if (p1GoesToTheRight){
          if (!P->move(MOVE_RIGHT)){
            p1GoesToTheRight=false;
          }
        }
        else{
          if (!P->move(MOVE_LEFT)){
            p1GoesToTheRight=true;
          }      
        }
      }
      buttonTimerMoveP1++;
    }
    if (ab.justReleased(P1_MOVE)){
      buttonTimerMoveP1=0;
    }
    if (ab.justReleased(P1_TURN)){
      buttonTimerTurnP1=0;
      P->turn();
    }
  } 
  else {// do the same for p2...
    if (ab.pressed(P2_TURN)){
      if (++buttonTimerTurnP2>TURN_BUTTON_TRIGGER){
        buttonTimerTurnP2=-3;
        while (P->move(MOVE_DOWN));
        P->stick();
        return;
      }
    }
    if (ab.pressed(P2_MOVE)){
      //if (buttonTimerMoveP1>=MOVE_BUTTON_TRIGGER){
      if ((0==buttonTimerMoveP2)||(buttonTimerMoveP2>=MOVE_BUTTON_TRIGGER)){
        if (p2GoesToTheRight){
          if (!P->move(MOVE_RIGHT)){
            p2GoesToTheRight=false;
          }
        }
        else{
          if (!P->move(MOVE_LEFT)){
            p2GoesToTheRight=true;
          }      
        }
      }
      buttonTimerMoveP2++;
    }
    if (ab.justReleased(P2_MOVE)){
      buttonTimerMoveP2=0;
    }
    if (ab.justReleased(P2_TURN)){
      buttonTimerTurnP2=0;
      P->turn();
    }  
  }
}

void playing(Piece* p1, Piece* p2, Piece* nextP1, Piece* nextP2){

  drawBackground();
  
  if (0!=blinkingLinesP1){
    
    if (-1==blinkingLinesP1){ // new Piece
      blinkingLinesP1=0;
      p1->reInit(nextP1->shape);
      p1->orientation=0;
      p1->update();
      if (p1->checkCollision()){ //game over
        //ab.display();
        blinkingLinesP1=-2;
      }
      //p1.shape=nextP1.shape;
      for (int i=0; i<4; i++){
        p1->body[i].type=nextP1->body[i].type;
      }
      nextP1->shapeShift();
      nextP1->update();
    }
    else if (blinkingLinesP1>0){  
      if (0==BlinkingTimerP1--){
        int temp=blinkingLinesP1*blinkingLinesP1;                       // score P1
        if ((scoreP1+temp)/SPEED_THRESHOLD>scoreP1/SPEED_THRESHOLD){
          if (fallingTimerInitP1>MAX_SPEED)
            fallingTimerInitP1--;
        }
        scoreP1+=blinkingLinesP1*blinkingLinesP1;          
        if (1==(globalSettings&1)){         //   ****   'gift'
          if (--blinkingLinesP1>0){
            int temp=blinkingLinesP1*10;
            for (int i=0; i<GRID_TOT; i++) {
              if (i-temp>=0){
                occupiedGridP2[i-temp]=occupiedGridP2[i];
              }
            }
            for (int i=GRID_TOT-1; i>=GRID_TOT-temp; i--) { 
              occupiedGridP2[i]=TYPE_FILLED;
            }
            temp=random(10);            
            for (int i=GRID_TOT-1; i>GRID_TOT-1-blinkingLinesP1*10; i-=10){ //remove a column from the gift
              occupiedGridP2[i-temp]=TYPE_EMPTY;
            }
          }
          p2->y-=blinkingLinesP1*SW;
        }
        removeBlinkingLines(true);     
        blinkingLinesP1=-1;
      }
    }
    else { //BlinkingP1== -2 or less
      ab.setCursor(LB1-7,30);
      ab.print(F("Busted !"));
    }
  }
  else {
      //if (ab.everyXFrames(fallingTimeP1)){
    if (0==fallingTimerP1--){
      fallingTimerP1=fallingTimerInitP1;
      if (!p1->move(MOVE_DOWN)){
        p1->stick();
        randomSeed(timer*321);
      }
    }
  }
  
  if (0!=blinkingLinesP2){
    
    if (-1==blinkingLinesP2){ // new Piece
      blinkingLinesP2=0;
      p2->reInit(nextP2->shape);
      p2->orientation=0;
      p2->update();
      if (p2->checkCollision()){ //game over
        //ab.display();
        blinkingLinesP2=-2;
      }
      //p1.shape=nextP1.shape;
      for (int i=0; i<4; i++){
        p2->body[i].type=nextP2->body[i].type;
      }
      nextP2->shapeShift();
      nextP2->update();
    }
    else if (blinkingLinesP2>0){ 
      if (0==BlinkingTimerP2--){
        int temp=blinkingLinesP2*blinkingLinesP2;                  // score P2
        if ((scoreP2+temp)/SPEED_THRESHOLD>scoreP2/SPEED_THRESHOLD){
          if (fallingTimerInitP2>MAX_SPEED)
            fallingTimerInitP2--;
        }
        scoreP2+=blinkingLinesP2*blinkingLinesP2;           
        if (1==(globalSettings&1)){         //   ****   'gift'
          if (--blinkingLinesP2>0){
            int temp=blinkingLinesP2*10;
            for (int i=0; i<GRID_TOT; i++) {
              if (i-temp>=0){
                occupiedGridP1[i-temp]=occupiedGridP1[i];
              }
            }
            for (int i=GRID_TOT-1; i>=GRID_TOT-temp; i--) { 
              occupiedGridP1[i]=TYPE_FILLED;
            }
            temp=random(10);            
            for (int i=GRID_TOT-1; i>GRID_TOT-1-blinkingLinesP2*10; i-=10){ //remove a column
              occupiedGridP1[i-temp]=TYPE_EMPTY;
            }
          }
          p1->y-=blinkingLinesP2*SW;
        }        
        removeBlinkingLines(false);
        blinkingLinesP2=-1;
      }
    }
    else { //BlinkingP1== -2 or less
      ab.setCursor(65,30);
      ab.print(F("Busted !"));
    }
  }
  else {
      //if (ab.everyXFrames(fallingTimeP1)){
    if (0==fallingTimerP2--){
      fallingTimerP2=fallingTimerInitP2;
      if (!p2->move(MOVE_DOWN)){
        p2->stick();
        randomSeed(timer*321);
      }
    }
  }

  if (blinkingLinesP2!=-2){
    control(p2);
    nextP2->draw();
    p2->update();
    p2->draw();
  }
  if (blinkingLinesP1!=-2){
    control(p1);
    nextP1->draw();
    p1->update();
    p1->draw();
  }
}
