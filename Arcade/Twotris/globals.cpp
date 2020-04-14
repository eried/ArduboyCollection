#include "globals.h"
//#include "square.h"

Arduboy2 ab;
int timer=0;

int fallingTimerP1=16;
int fallingTimerP2=16;
int fallingTimerInitP1=16;
int fallingTimerInitP2=16;

int buttonTimerTurnP1=0;
int buttonTimerTurnP2=0;
int buttonTimerMoveP1=0;
int buttonTimerMoveP2=0;

bool p1GoesToTheRight=true;
bool p2GoesToTheRight=false;

int blinkingLinesP1=0;
int blinkingLinesP2=0;

int BlinkingTimerP1=0;
int BlinkingTimerP2=0;
int scoreP1=0;
int scoreP2=0;
byte occupiedGridP1[GRID_TOT];
byte occupiedGridP2[GRID_TOT];
//int NbStillSquaresP1=0;
//int NbStillSquaresP2=0;

byte globalSettings=1;
