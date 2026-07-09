#include "../inc/board.h"
#include <raylib.h>
#include <stdbool.h>


int main(void) {
    InitWindow(800, 800, "Chess Engine");
    SetTargetFPS(15);

    Texture2D *sprites = loadSprites();
    BoardState board;
    initBoardState(&board);

    while(!WindowShouldClose()) {

        BeginDrawing();
            displayBoardState(&board, sprites);
        EndDrawing();

    }

    return 0;
}
