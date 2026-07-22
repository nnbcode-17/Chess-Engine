#ifndef RENDER_H
#define RENDER_H

#include <raylib.h>
#include "board.h"

Texture2D *loadSprites();
void drawBoard(BoardState *state, Texture2D *sprites);
u8 getPos(Pos *pos);
#endif //RENDER_H
