#include <raylib.h>
#include <stdlib.h>
#include "../inc/render.h"
#include "../inc/moves.h"

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

    for (i32 i = 0; i < 8; i++) {
        char coord[2] = {0, '\0'};
         coord[0] = 'A' + i;
        DrawText(coord, i * 100 + 85, 785, 15, BLACK);
        coord[0] = '8' - i;
        DrawText(coord, 5,i * 100 + 5, 15, BLACK);
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

            if (p.color == 1) {
                i32 idx = (p.type - 1) * 2;
                img = sprites[idx + 1];
                DrawTexture(img, j * 100 + 5, i * 100 + 5, WHITE);
            }
            else if (p.color == 2){
                i32 idx = (p.type - 1) * 2;
                img = sprites[idx];
                DrawTexture(img, j * 100 + 5, i * 100 + 5, WHITE);
            }

            DrawTexture(img, j * 100 + 5, i * 100 + 5, WHITE);
        }
    }
}

// If the left mouse button is pressed it returns a struct containing the position in terms of array indexing row and col.
bool getPosition(Pos *pos)
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 px = GetMousePosition();
        *pos = (Pos){
            .row = px.y / 100,
            .col = px.x / 100
        };
        return true;
    }

    return false;
}
void getInput(BoardState *board){
    static Pos posArr[2] = {};
    static u8 idx = 0;
    static Pos movesList[27] = {};
    static i32 size = 0;
    static u8 color;

    Pos curr;

    if (getPosition(&curr)){
        if (idx == 0 && board->board[curr.row][curr.col].type) {
            posArr[idx++] = curr;
            color = board->board[curr.row][curr.col].color;
            size = generateMoves(board, curr, movesList);
        }
        else if (idx == 1 && curr.row == posArr[0].row && posArr[0].col == curr.col){
            color = 0;
            idx = 0;
        }
        else if (idx == 1 && board->board[curr.row][curr.col].color == color) {
            posArr[idx - 1] = curr;
            size = generateMoves(board, curr, movesList);
        }
        else {
            for (i32 i = 0; i < size; i++) {
                if (curr.row == movesList[i].row && curr.col == movesList[i].col) {
                    posArr[idx++] = curr;
                    break;
                }
            }
        }
    }

    if (idx == 2) {
         swap(board, posArr);
        idx = 0;
        color = 0;
        size = 0;
    }

}

