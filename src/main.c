#include "../inc/render.h"
#include "../inc/board.h"

int main(void) {
    InitWindow(800, 800, "Chess Engine");
    SetTargetFPS(15);

    Texture2D *sprites = loadSprites();
    BoardState board;

    initBoardState(&board);
    //BoardState b = fenToBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    while(!WindowShouldClose()) {
        getInput(&board);

        BeginDrawing();
            displayBoardState(&board, sprites);
        EndDrawing();
    }

    return 0;
}


