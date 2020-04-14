// the part of the pieces

#include "globals.h"
#include "square.h"
#include "background.h"
#include "game.h"
//#include "Tinyfont.h"
//Tinyfont tinyfont = Tinyfont(ab.sBuffer, Arduboy2::width(), Arduboy2::height());

void drawBackground(){
  ab.fillRect(0,0,128,66,1);
  ab.fillRect(LB1,0,10*SW,63,0);
  ab.fillRect(LB2,0,10*SW,63,0);
  
  //score
  affScore(true);
  affScore(false);
  
  //tinyfont.print("bonjour102");
  //arrows
  ab.drawChar(4,30,p1GoesToTheRight? 26:27,1,0,1);
  ab.drawChar(118,30,p2GoesToTheRight? 26:27,1,0,1);
  
  //next
  ab.fillRect(3,4,4*SW,5*SW,0);
  ab.fillRect(109,4,4*SW,5*SW,0);

  if((globalSettings&4)==4){ //P1 Grid
    for (int i=0; i<9; i++){
      for (int j=0; j<15; j++){
        ab.drawPixel(LB1+(1+i)*SW,UP_BORDER+j*SW,1);
      }
    }
  }
  if((globalSettings&2)==2){ //P2 Grid
    for (int i=0; i<9; i++){
      for (int j=0; j<15; j++){
        ab.drawPixel(LB2+(1+i)*SW,UP_BORDER+j*SW,1);
      }
    }
  }  
  drawStillSquares();

  //debug
  //ab.print(fallingTimerInitP1);
  
}

void affScore(bool P1){
  if (P1){    
    if (scoreP1>=1000){
      ab.setCursor(3,44);
      ab.print(scoreP1/1000);      
      ab.setCursor(9,44);
      ab.print(F("K+"));

      ab.setCursor(3,52);
      zeroPrint(scoreP1-1000);
    }
    else {
      ab.setCursor(3,52);
      zeroPrint(scoreP1);
    }    
  }
  else {
    if (scoreP2>=1000){
      ab.setCursor(107,44);
      ab.print(scoreP2/1000);      
      ab.setCursor(113,44);
      ab.print(F("K+"));

      ab.setCursor(107,52);
      zeroPrint(scoreP2-1000);
    }    
    else {
      ab.setCursor(107,52);
      zeroPrint(scoreP2);
    }
  }
}

void zeroPrint(int score){
  if (score<10){
    ab.print(F("00"));    
  }
  else if (score <100){
    ab.print(F("0"));  
  }
  ab.print (score);
}

void drawStillSquares(){
Square StillSquaresDrawer(LB1,UP_BORDER,0);

  for(int i=0;i<GRID_TOT;i++){
    if(occupiedGridP1[i]!=0){
      StillSquaresDrawer.x=getXfromI(i,true);//(LB1+i%10*SW);
      StillSquaresDrawer.y=getYfromI(i);//(upBorder+i/10*SW);
      StillSquaresDrawer.type=occupiedGridP1[i];
      StillSquaresDrawer.draw();
    }
    if(occupiedGridP2[i]!=0){
      StillSquaresDrawer.x=getXfromI(i,false);//(LB2+i%10*SW);
      StillSquaresDrawer.y=getYfromI(i);//(upBorder+i/10*SW);
      StillSquaresDrawer.type=occupiedGridP2[i];
      StillSquaresDrawer.draw();
    }    
  }
}

void checkFullLines(byte minY, byte maxY, bool p1){ //let's start again
  int nbSameY[4]={0,0,0,0};
  int temp;
  //if (p1&&blinkingLinesP1!=0){ //this should not happend
  /*if(false){
    ab.clear();
    ab.print(F("minY=");
    ab.print(minY);
    ab.display();
    delay(500);
  }*/
  if (p1){
    for(int j=0; j<(maxY-minY)/SW+1; j++){
      temp=getIndice(LB1,minY+j*SW,true);
      for(int i=temp;i<temp+10;i++){
        if (occupiedGridP1[i]!=0) {
          nbSameY[j]++;
        }
      }
      if (10==nbSameY[j]){
        //blinkingLinesP1+=1<<(14-((minY-3)/SW+j));  // less significant bit is bottom line
        blinkingLinesP1+=1; //was used to transmit wich lines was blinking. Now it just has to be >0 -> used for score now
        for(int i=temp;i<temp+10;i++){
          occupiedGridP1[i]=TYPE_BLINKING;
        }
        BlinkingTimerP1=10;
      }
    }  
    if (0==blinkingLinesP1)
      blinkingLinesP1=-1;
  }
  else { //p2
    for(int j=0; j<(maxY-minY)/SW+1; j++){
      temp=getIndice(LB2,minY+j*SW,false);
      for(int i=temp;i<temp+10;i++){
        if (occupiedGridP2[i]!=0) {
          nbSameY[j]++;
        }
      }
      if (10==nbSameY[j]){
        blinkingLinesP2+=1;//<<(14-((minY-UP_BORDER)/SW+j));  // less significant bit is bottom line
        for(int i=temp;i<temp+10;i++){
          occupiedGridP2[i]=TYPE_BLINKING;
        }
        BlinkingTimerP2=10;
      }
    }  
    if (0==blinkingLinesP2)
      blinkingLinesP2=-1;
  }
}

void removeBlinkingLines(bool p1){
  if (p1){
    for (int i=GRID_TOT-1;i>=0;i--){
      while (TYPE_BLINKING==occupiedGridP1[i]){
        for (int j=i;j>=0;j--){
          if (j-10<0)
            occupiedGridP1[j]=0;
          else
            occupiedGridP1[j]=occupiedGridP1[j-10];
        }
      }
    }
    blinkingLinesP1=0;
  }
  else { //p2
    for (int i=GRID_TOT-1;i>=0;i--){
      while (TYPE_BLINKING==occupiedGridP2[i]){
        for (int j=i;j>=0;j--){
          if (j-10<0)
            occupiedGridP2[j]=0;
          else
            occupiedGridP2[j]=occupiedGridP2[j-10];
        }
      }
    }
  }  
}
