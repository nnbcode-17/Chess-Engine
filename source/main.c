#include <raylib.h>
#include <stdio.h>
#include "../include/constants.h"
#include "../include/render.h"

int main()
{
    printf("Hello from new Engine\n");
    InitWindow(LENGTH, LENGTH, "Chess Engine");
    SetTargetFPS(15);

    BoardState state =  initBoard();
    Texture2D *sprites = loadSprites();

    while (!WindowShouldClose()) {
        
        BeginDrawing();
            ClearBackground(WHITE);
            drawBoard(&state, sprites);
        EndDrawing();
    }
    return 0;
}
