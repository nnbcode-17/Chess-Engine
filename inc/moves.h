#ifndef MOVES_H
#define MOVES_H

#include "board.h"

i32 generateMoves(BoardState *board, Pos pos, Pos *moves);
i32 generateKnightMoves(BoardState *board, Pos pos, Pos *moves);
i32 generatePawnMoves(BoardState *board, Pos pos, Pos *moves);
i32 generateRookMoves(BoardState *board, Pos pos, Pos *moves);
i32 generateBishopMoves(BoardState *board, Pos pos, Pos *moves);
i32 generateQueenMoves(BoardState *board, Pos pos, Pos *moves);
i32 generateKingMoves(BoardState *board, Pos pos, Pos *moves);
void swap(BoardState *board , Pos *positions);
#endif // MOVES_H
