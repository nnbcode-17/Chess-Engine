#ifndef BOARD_H
#define BOARD_H
#include <stdint.h>

#define PAWN_VAL 100
#define KNIGHT_VAL 300
#define BISHOP_VAL 300
#define ROOK_VAL 500
#define QUEEN_VAL 1000
#define KING_VAL 10000


typedef  int32_t i32;
typedef uint8_t u8;

typedef enum {
    EMPTY, 
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
} Piece_t;

typedef struct {
    Piece_t type;
    i32 value;
    u8 color;
} Piece;

typedef struct {
    Piece board[8][8];
    u8 castling_b;
    u8 castling_w;
} BoardState;

typedef struct {
    i32 row, col;
} Pos;

void initBoardState(BoardState *board);
BoardState fenToBoard(const char *str);
#endif //BOARD_H
