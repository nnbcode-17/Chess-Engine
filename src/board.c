#include "../inc/board.h"
#include <stdio.h>

// This function takes in a pointer to a BoardState struct and sets up the Chess Board
BoardState initBoardState()
{
    Piece_t types[] = {ROOK, KNIGHT, BISHOP, QUEEN, KING, PAWN};
    int values[] = {ROOK_VAL, KNIGHT_VAL, BISHOP_VAL, QUEEN_VAL, KING_VAL, PAWN_VAL};
    BoardState state = {.castling_b = 1, .castling_w = 1};

    for (i32 i = 0; i < 8; i++) {
        i32 k = 0;
        for (i32 j = 0; j < 8; j++) {
            if (i == 0 || i == 7) {
                Piece_t type = types[k % 5];
                int value = values[k % 5];
                u8 color = i == 0 ? 1 : 2;
                Piece p = {.type = type, .value = value, .color = color};
                state.board[i][j] = p;
                if (j < 4){
                    k++;
                }
                else if (j == 4) {
                    k = 2;
                }
                else {
                    k--;
                }
            }
            else if(i == 1 || i == 6) {
                Piece_t type = types[5];
                u8 color = i == 1? 1 : 2;
                int value = values[5];
                Piece p = {.type = type, .value = value, .color = color};
                state.board[i][j] = p;
            }
            else {
                Piece p = {.type = EMPTY, .value = -1, .color = 0};
                state.board[i][j] = p;
            }
        }
    }

    return state;
}

// This is a prototype for testing out different boardstates using FEN strings.
BoardState fenToBoard(const char *str)
{
    BoardState board = {};
    i32 row = 0;
    const char *def = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    if (str == NULL) {
        str = def;
    }

    while(*str) {

        for (i32 col = 0; col <= 8; col++) {

            if (*str - '0' >= 1 && *str - '0' <= 8) {
                printf("Triggered\n");
                i32 value = *str - '0';
                str++;
                for(i32 i = 0; i < value && col < 8; col++, i++) {
                    printf("col: %d \n", col);
                    board.board[row][col] = (Piece){EMPTY, -1, 0};
                }
            }
            if (col == 8) break;

            switch(*str) {
                case 'p':
                    board.board[row][col] = (Piece){PAWN, PAWN_VAL, 1};
                    str++;
                    break;
                case 'n':
                    board.board[row][col] = (Piece){KNIGHT, KNIGHT_VAL, 1};
                    str++;
                    break;
                case 'b':
                    board.board[row][col] = (Piece){BISHOP, BISHOP_VAL, 1};
                    str++;
                    break;
                case 'r':
                    board.board[row][col] = (Piece){ROOK, ROOK_VAL, 1};
                    str++;
                    break;
                case 'q':
                    board.board[row][col] = (Piece){QUEEN, QUEEN_VAL, 1};
                    str++;
                    break;
                case 'k':
                    board.board[row][col] = (Piece){KING, KING_VAL, 1};
                    str++;
                    break;
                case 'P':
                    board.board[row][col] = (Piece){PAWN, PAWN_VAL, 2};
                    str++;
                    break;
                case 'N':
                    board.board[row][col] = (Piece){KNIGHT, KNIGHT_VAL, 2};
                    str++;
                    break;
                case 'B':
                    board.board[row][col] = (Piece){BISHOP, BISHOP_VAL, 2};
                    str++;
                    break;
                case 'R':
                    board.board[row][col] = (Piece){ROOK, ROOK_VAL, 2};
                    str++;
                    break;
                case 'Q':
                    board.board[row][col] = (Piece){QUEEN, QUEEN_VAL, 2};
                    str++;
                    break;
                case 'K':
                    board.board[row][col] = (Piece){KING, KING_VAL, 2};
                    str++;
                    break;
                case '/':
                    row++;
                    str++;
                    col = 8;
                    break;
            }
        }
    }
    return board;
}

