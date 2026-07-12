#ifndef RENDER_H
#define RENDER_H

#include <raylib.h>
#include "board.h"

Texture2D *loadSprites(void);
void drawBoard(void);
void displayBoardState(BoardState *board, Texture2D *sprites);
bool getPosition(Pos *pos);
void getInput(BoardState *board);

#endif // RENDER_H
