#include <raylib.h>
#include <stdlib.h>
#include "../include/render.h"
#include "../include/constants.h"

// Loads sprites in to an array and returns the array.
Texture2D *loadSprites()
{
    const char *files[] = {
        "assets/pawn.png", "assets/Pawn.png",
        "assets/knight.png", "assets/Knight.png",
        "assets/bishop.png", "assets/Bishop.png",
        "assets/rook.png", "assets/Rook.png",
        "assets/queen.png", "assets/Queen.png",
        "assets/king.png", "assets/King.png"
    };

    Texture2D *sprites = malloc(sizeof(Texture2D) * 13);

    for(i32 i = 0; i < 13; i++) {
        sprites[i] = LoadTexture(files[i]);
    }
    return sprites;
}

// Draws board and pieces.
void drawBoard(BoardState *state, Texture2D *sprites)
{
    for (i32 i = 0; i < 8; i++) {
        for (i32 j = 0; j < 8; j++) {
            Color color = (i + j) % 2 == 0? BLACK : LIGHTGRAY;
            Piece piece = state->board[i][j];
            DrawRectangle(j * SQUARE_LEN, i * SQUARE_LEN, SQUARE_LEN, SQUARE_LEN, color);

            if (piece.type) {
                i32 id = piece.type - 1;
                i32 idx = piece.color == BLACK_T? id * 2 : id * 2 + 1 ;
                DrawTexture(sprites[idx], j * SQUARE_LEN, i * SQUARE_LEN , WHITE);
            }
        }
    }
}

// Gets mouse x and y position and converts it to an array index for board.
u8 getPos(Pos *pos)
{
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        Vector2 coord = GetMousePosition();
        pos->row = coord.y / 100;
        pos->col = coord.x / 100;
        return 1;
    }

    return 0;
}
