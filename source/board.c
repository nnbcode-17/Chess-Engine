#include "../include/board.h"

// Returns a BoardState representing an initial chess board state.
BoardState initBoard()
{
    BoardState state = {.white = 1, .black = 1};
    u8 types[] = { ROOK, KNIGHT, BISHOP, QUEEN, KING };
    i32 values[] = { ROOK_VAL, KNIGHT_VAL, BISHOP_VAL, QUEEN_VAL, 1000 };

    for (i32 i = 0; i < 8; i++) {
        COLOR color = i < 2? BLACK_T : WHITE_T;
        i32 idx = 0;

        for (i32 j = 0; j < 8; j++) {
            Piece piece = {EMPTY};
            if (i == 0 || i == 7) {
                PIECE type = types[idx];
                VALUE value = values[idx];
                piece = (Piece){.type = type, .value = value, .color = color};

                if (j == 4) {
                    idx = 3;
                }

                if (j < 4) {
                    idx++;
                }
                else {
                    idx--;
                }
            }
            else if (i == 1 || i == 6) {
                piece = (Piece){.type = PAWN, .value = PAWN_VAL, .color = color};
            }
            state.board[i][j] = piece;
        }
    }

    return state;
}
