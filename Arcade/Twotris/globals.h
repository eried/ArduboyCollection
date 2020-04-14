#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduboy2.h>
#include "square.h"

#define LB1 23 //left border 
#define LB2 LB1+2+10*SW

#define GRID_TOT 150
#define UP_BORDER 3

#define MAX_SPEED 4  //the less, the faster
#define SPEED_THRESHOLD 50

#define TL1 30 // Title line 1
#define TL2 TL1-SW // Title line 1
#define TL3 TL1-2*SW 
#define TL4 TL1-3*SW 
#define TL5 TL1-4*SW 
#define TL6 TL1-5*SW 
#define TL7 TL1-6*SW 
#define TL8 TL1-7*SW 

#define TR1 -3 // Title Row 1

#define MOVE_RIGHT 1
#define MOVE_DOWN 2
#define MOVE_LEFT 3
#define MAXS 110

#define MENU_START 1
#define MENU_SETTINGS 2
#define MENU_INFO 3
#define MENU_CREDIT 4
#define MENU_BACK 9

extern Arduboy2 ab;
extern int timer;
extern int fallingTimerP1;
extern int fallingTimerP2;
extern int fallingTimerInitP1;
extern int fallingTimerInitP2;
extern int buttonTimerTurnP1;
extern int buttonTimerTurnP2;
extern int buttonTimerMoveP1;
extern int buttonTimerMoveP2;
extern bool p1GoesToTheRight;
extern bool p2GoesToTheRight;
extern int blinkingLinesP1;
extern int blinkingLinesP2;
extern int BlinkingTimerP1;
extern int BlinkingTimerP2;
extern int scoreP1;
extern int scoreP2;
extern byte occupiedGridP1[GRID_TOT];
extern byte occupiedGridP2[GRID_TOT];
//extern int NbStillSquaresP1;
//extern int NbStillSquaresP2;
//extern class Square stillSquaresP1 [MAXS];
//extern class Square stillSquaresP2 [MAXS];

extern byte globalSettings;
/*       
    bit 0: Gift enabled, bit 1: grid P2, bit 2: grid P1
*/
#endif
