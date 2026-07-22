#ifndef BOARD_H
#define BOARD_H
#include <stdint.h>

#define EMPTY 0

typedef uint8_t u8;
typedef int32_t i32;

// Using enums to represent piece type
typedef enum {
    PAWN = 1, KNIGHT, BISHOP, ROOK, QUEEN, KING 
} PIECE;

// Using enum to represent color
typedef enum {
    WHITE_T = 1, BLACK_T
} COLOR;

// Using enum to represent the values of the pieces
typedef enum {
    PAWN_VAL = 100,
    KNIGHT_VAL = 300,
    BISHOP_VAL = 350,
    ROOK_VAL = 500,
    QUEEN_VAL = 900
} VALUE;

typedef enum {
    CAPTURE = 1, PASSANT, CASTLING
} Move_flags;

// A struct to contains all the information about a piece; (type, color, value)
typedef struct {
    u8 type, color, value;
} Piece;

// Struct to represent board
typedef struct {
    Piece board[8][8];
    u8 white;
    u8 black;
} BoardState;

// A struct to represent a position on the board.
typedef struct {
    i32 row, col;
} Pos;

// A struct that contains information about a move.
typedef struct {
    Pos from, to;
    u8 flag;
} Move;

BoardState initBoard();
BoardState fenToBoard();
#endif //BOARD_H
