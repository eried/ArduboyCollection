#ifndef GAME_H
#define GAME_H

#define NB_PLAYERS 1 //for now... but soon...

#define P1_TURN UP_BUTTON
#define P1_MOVE DOWN_BUTTON

#define P2_TURN A_BUTTON
#define P2_MOVE B_BUTTON

void control(Piece *P);
void playing(Piece* p1, Piece* p2, Piece* nextP1, Piece* nextP2);

#endif
