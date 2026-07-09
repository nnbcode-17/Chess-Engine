#include "../inc/board.h"
#include <stdlib.h>
#include <raylib.h>

// Loads the png imgs into an array of Textures and returns the array.
Texture2D *loadSprites(void)
{
     char *fileNames[] = {
        "assests/pawn_w.png", "assests/pawn_b.png", "assests/knight_w.png", "assests/knight_b.png",
        "assests/bishop_w.png", "assests/bishop_b.png", "assests/rook_w.png", "assests/rook_b.png",
        "assests/queen_w.png", "assests/queen_b.png", "assests/king_w.png", "assests/king_b.png"
    };
    Texture2D *imgs = malloc(sizeof(Texture2D) * 12);

    for (i32 i = 0; i < 12; i++)  {
        imgs[i] = LoadTexture(fileNames[i]);
    }

    return imgs;
}

// This function simply draws the checkboard pattern onto the window.
void drawBoard(void)
{
    int boardSize = 800;
    int dimensions = 8;
    int cellSize = boardSize / dimensions;
    Color light = WHITE;
    Color dark = BEIGE;

    for( i32 i = 0; i < dimensions; i++) {
        for(i32 j = 0; j < dimensions; j++) {
            int xpos = j * cellSize;
            int ypos = i * cellSize;

            if ((i + j) % 2 == 0) {
                DrawRectangle(xpos, ypos, cellSize, cellSize, light);
            }
            else {
                DrawRectangle(xpos, ypos, cellSize, cellSize, dark);
            }
        }
    }
}

// This function takes in a pointer to a BoardState struct and sets up the Chess Board
void initBoardState(BoardState *board)
{
    Piece_t types[] = {ROOK, KNIGHT, BISHOP, QUEEN, KING, PAWN};
    int values[] = {ROOK_VAL, KNIGHT_VAL, BISHOP_VAL, QUEEN_VAL, KING_VAL, PAWN_VAL};

    for (i32 i = 0; i < 8; i++) {
        i32 k = 0;
        for (i32 j = 0; j < 8; j++) {
            if (i == 0 || i == 7) {
                Piece_t type = types[k % 5];
                int value = values[k % 5];
                u8 color = i == 0 ? 1 : 0;
                Piece p = {.type = type, .value = value, .color = color, .firstMove = true};
                board->board[i][j] = p;
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
                u8 color = i == 1? 1 : 0;
                int value = values[5];
                Piece p = {.type = type, .value = value, .color = color, .firstMove = true};
                board->board[i][j] = p;
            }
            else {
                Piece p = {.type = EMPTY, .value = -1, .color = 0, .firstMove = false};
                board->board[i][j] = p;
            }
        }
    }
}

// This function takes a pointer to a BoardState struct and an array of Texture2D to display current state of the board.
void displayBoardState(BoardState *board, Texture2D *sprites)
{
    drawBoard();

    for( i32 i = 0; i < 8; i++) {
        for (i32 j = 0; j < 8; j++) {
            Piece p = board->board[i][j];
            Texture2D img;
            if (p.type == EMPTY) continue;

            i32 idx = p.type * 2;
            if (p.color) {
                img = sprites[idx + 1];
            }
            else {
                img = sprites[idx];
            }

            DrawTexture(img, j * 100 + 5, i * 100 + 5, WHITE);
        }
    }
}
