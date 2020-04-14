/*   TWOTRIS  a two players tetris for Arduboy
 *    Written by Cédric Martin
 * 
 */

//#include <Arduboy2.h>
#include "globals.h"
#include "square.h"
#include "background.h"
#include "game.h"
#include "title.h"
#include "menu.h"

#define INTRO 1
#define MENU 2
#define SETTINGS 3
#define INFO 4
#define CREDIT 5
#define GAME 10
 
//Piece p1(LB+3*SW,3,SHAPE_T, true);
//Piece p1(LB,3,SHAPE_T, true);
Piece p1(true);
Piece p2(false);
Piece nextP1(7,13,0,true);
Piece nextP2(113,13,0,false);

byte state=INTRO;

void setup() {
  ab.begin();
  ab.setFrameRate(60);
  
  ab.initRandomSeed();
  randomSeed(3309);
  timer=0;

  //test
  //scoreP1=1234;
  //scoreP2=9876;

}

void loop() {
  if (!(ab.nextFrame()))
    return;
    
  timer++;
  ab.clear();
  ab.pollButtons(); 

  switch (state){

    case INTRO :
      affTitle(timer/20);
    
      if (ab.justPressed(A_BUTTON)||(ab.justPressed(B_BUTTON))){
        state=MENU;
      }
    break;

    case MENU :      
     
      switch (menu()){
        case MENU_START:        
          randomSeed(timer*987);
          resetOccupiedGrids();
          nextP1.shapeShift();
          nextP1.update();
          nextP2.shapeShift();
          nextP2.update();  
            
          state=GAME;
        break;
        case MENU_INFO:
            state=INFO;
        break;
        case MENU_CREDIT:
            state=CREDIT;
        break;
        case MENU_SETTINGS:
           state=SETTINGS;
        break;
        default:
        break;
      }      
    break;

    case SETTINGS :
      if (MENU_BACK==settings()){
        state=MENU;
      }
    break;
    case INFO :
      if (MENU_BACK==info()){
        state=MENU;
      }
    break;
    case CREDIT :
      if (MENU_BACK==credit()){
        state=MENU;
      }
    break;
    
    case GAME:
    
      playing(&p1, &p2, &nextP1, &nextP2);
 /*   
      control(&p1);
      control(&p2);
      
      nextP1.draw();
      nextP2.draw();
      
      p1.update();
      p1.draw();
      p2.update();
      p2.draw();
*/
    break;   
    
    default :
      ab.print(F("oups... State not defined"));
      if (ab.justPressed(A_BUTTON)||(ab.justPressed(B_BUTTON))){
        state=MENU;
      }
    break;
  }
  ab.display();

}
