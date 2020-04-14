#ifndef BACKGROUND_H
#define BACKGROUND_H

void drawBackground();
void affScore(bool P1);
void zeroPrint(int score);
void drawStillSquares();
void checkFullLines(byte minY, byte maxY, bool p1);
void removeBlinkingLines(bool p1);

#endif
