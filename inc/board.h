#ifndef BOARD_H
#define BOARD_H
#include <stdint.h>
#include <raylib.h>

#define PAWN_VAL 100
#define KNIGHT_VAL 300
#define BISHOP_VAL 300
#define ROOK_VAL 500
#define QUEEN_VAL 1000
#define KING_VAL 10000


typedef  int32_t i32;
typedef uint8_t u8;

typedef enum {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    EMPTY 
} Piece_t;

typedef struct {
    Piece_t type;
    i32 value;
    u8 color;
    u8 firstMove;
} Piece;

typedef struct {
    Piece board[8][8];
} BoardState;


Texture2D *loadSprites(void);
void drawBoard(void);
void initBoardState(BoardState *board);
void displayBoardState(BoardState *board, Texture2D *sprites);
#endif //BOARD_H
