#include "../inc/moves.h"
#include "../inc/board.h"

// A helper function that connects all the generate moves under one function.
i32 generateMoves(BoardState *state, Pos pos, Pos *moves)
{
    if (state->board[pos.row][pos.col].color == 1) {
        u8 flag = state->board[0][4].type == KING;
        state->castling_b = state->castling_b && flag? 1 : 0;
        flag = state->board[0][0].type == ROOK || state->board[0][7].type == ROOK;
        state->castling_b = state->castling_b && flag? 1 : 0;
    }

    if (state->board[pos.row][pos.col].color == 2){
        u8 flag = state->board[7][4].type == KING;
        state->castling_w = state->castling_w && flag? 1 : 0;
         flag = state->board[7][0].type == ROOK || state->board[7][7].type == ROOK;
        state->castling_w = state->castling_w && flag? 1 : 0;
    }

    switch (state->board[pos.row][pos.col].type) {
        case PAWN:
            return generatePawnMoves(state, pos, moves);
        case KNIGHT:
            return  generateKnightMoves(state, pos, moves);
        case ROOK:
            return generateRookMoves(state, pos, moves);
        case BISHOP:
            return generateBishopMoves(state, pos, moves);
        case QUEEN:
            return generateQueenMoves(state, pos, moves);
        case KING:
            return generateKingMoves(state, pos, moves);
        case EMPTY:
            break;
    }

    return 0;
}

// Generates all valid moves for a knights position on the current board state.
i32 generateKnightMoves(BoardState *state, Pos pos, Pos *moves)
{
    i32 offset[][2] = {
        {-2, 1}, {-2, -1},
        {2, 1}, {2, -1},
        {1, 2}, {-1, 2},
        {1, -2}, {-1, -2}
    };

    i32 count = 0;

    for (i32 i = 0; i < 8; i++) {
        i32 row = pos.row + offset[i][0];
        i32 col = pos.col + offset[i][1];
        if (row > 7 || row < 0 || col > 7 || col < 0) {
            continue;
        }

        if (state->board[row][col].color != state->board[pos.row][pos.col].color) {
            moves[count++] = (Pos){.row = row, .col = col};
        }
    }

    return count;
}

// Generates all valid moves for a pawns position on the current board state
i32 generatePawnMoves(BoardState *state, Pos pos, Pos *moves)
{
    u8 myColor = state->board[pos.row][pos.col].color;
    i32 dir = myColor == 1 ? 1 : -1;

    i32 offset[][2] = {
        {dir, -1}, {dir, 1},
        {dir, 0}, {dir * 2, 0}
    };

    i32 count = 0;
    i32 size = (myColor == 1 && pos.row == 1) || (myColor == 2 && pos.row == 6) ? 4 : 3;
    i32 passant = myColor == 1? 4 : 3;


    for (i32 i = 0; i < size; i++) {
        i32 row = pos.row + offset[i][0];
        i32 col = pos.col + offset[i][1];

        if (row > 7 || row < 0 || col > 7 || col < 0) {
            continue;
        }
        if ( i < 2 && state->board[row][col].color && myColor != state->board[row][col].color) {
            moves[count++] = (Pos){.row = row, .col = col};
        }
        else if ( i > 1 && !state->board[row][col].type){
            moves[count++] = (Pos){.row = row, .col = col};
        }
    }

    // Checking for en passant.
    if (passant == pos.row) {
        if (pos.col - 1 > -1 && state->board[passant][pos.col - 1].type == PAWN && myColor != state->board[passant][pos.col - 1].color) {
            moves[count++] = (Pos){.row = passant + dir, .col = pos.col - 1};
        }
        if (pos.col + 1 < 8 && state->board[passant][pos.col + 1].type == PAWN && myColor != state->board[passant][pos.col + 1].color) {
            moves[count++] = (Pos){.row = passant + dir, .col = pos.col + 1};
        }
    }
    return count;

}

// Generates all valid moves for a rook position on the current board state.
i32 generateRookMoves(BoardState *state, Pos pos, Pos *moves)
{
    i32 offset[][2] = {
        {1,0}, {-1,0},
        {0,1}, {0, -1}
    };
    i32 count = 0;
    u8 myColor = state->board[pos.row][pos.col].color;

    for (i32 i = 0; i < 4; i++) {
        i32 row = pos.row + offset[i][0];
        i32 col = pos.col + offset[i][1];

        while((row > -1 && row < 8) && (col > -1 && col < 8)) {
            if (state->board[row][col].color == myColor) {
                break;
            }
            else if (state->board[row][col].type && myColor != state->board[row][col].color) {
                moves[count++] = (Pos){.row = row, .col = col};
                break;
            }
            else {
                moves[count++] = (Pos){.row = row, .col = col};
            }
            row += offset[i][0];
            col += offset[i][1];
        }
    }
    return count;
}
// Generates all valid move for a bishop position on the current board state.
// Ignoring castling for now.
i32 generateBishopMoves(BoardState *state, Pos pos, Pos *moves)
{
    i32 offset[][2] = {
        {1, 1}, {1, -1},
        {-1, -1}, {-1, 1}
    };

    i32 count = 0;
    u8 myColor = state->board[pos.row][pos.col].color;

    for (i32 i = 0; i < 4; i++) {
        i32 row = pos.row + offset[i][0];
        i32 col = pos.col + offset[i][1];

        while ((row > -1 && row < 8) && (col > -1 && col < 8)) {

            if (state->board[row][col].color == myColor) {
                break;
            }
            else if (state->board[row][col].type && myColor != state->board[row][col].color) {
                moves[count++] = (Pos){.row = row, .col = col};
                break;
            }
            else {
                moves[count++] = (Pos){.row = row, .col = col};
            }
            row += offset[i][0];
            col += offset[i][1];
        }
    }
    return count;
}

//Generate all valid moves for a queen position on the current board state.
i32 generateQueenMoves(BoardState *state, Pos pos, Pos *moves)
{
    i32 offset[][2] = {
        {1,0}, {-1,0},
        {0,1}, {0, -1},
        {1, 1}, {1, -1},
        {-1, -1}, {-1, 1}
    };

    i32 count = 0;
    u8 myColor = state->board[pos.row][pos.col].color;
    
    for (i32 i = 0; i < 8; i++) {
        i32 row = pos.row + offset[i][0];
        i32 col = pos.col + offset[i][1];

        while ((row > -1 && row < 8) && (col > -1 && col < 8)) {

            if (state->board[row][col].color == myColor) {
                break;
            }
            else if (state->board[row][col].type && myColor != state->board[row][col].color) {
                moves[count++] = (Pos){.row = row, .col = col};
                break;
            }
            else {
                moves[count++] = (Pos){.row = row, .col = col};
            }
            row += offset[i][0];
            col += offset[i][1];
        }

    }
    return count;
}

// Generates all valid moves for a kings position on the current board state.
i32 generateKingMoves(BoardState *state, Pos pos, Pos *moves)
{
    u8 castlingActive = 0;
    if (state->board[pos.row][pos.col].color == 1) {
        castlingActive = state->castling_b;
    }
    if (state->board[pos.row][pos.col].color == 2){
        castlingActive = state->castling_w;
    }

    i32 offset[][2] = {
        {0,1}, {0, -1},
        {1, 0}, {-1, 0},
        {1, 1}, {1, -1},
        {-1, -1}, {-1, 1}
    };

    i32 count = 0;
    u8 myColor = state->board[pos.row][pos.col].color;

    for (i32 i = 0; i < 8; i++) {
        i32 row = pos.row + offset[i][0];
        i32 col = pos.col + offset[i][1];

        if (row > 7 || row < 0 || col > 7 || col < 0) {
            continue;
        }
        else if (state->board[row][col].color == myColor) {
            continue;
        }
        else {
            moves[count++] = (Pos){.row = row, .col = col};
        }
    }

    if (castlingActive) {
        i32 i  = pos.col + 1;
        while (i < 8 && state->board[pos.row][i].type == EMPTY) {
            i++;
        }

        if (i <  8 && state->board[pos.row][i].type == ROOK) {
            moves[count++] = (Pos){.row = pos.row, .col = i};
        }

        i = pos.col - 1;

        while (i > -1 && state->board[pos.row][i].type == EMPTY) {
            i--;
        }

        if ( i > -1 && state->board[pos.row][i].type == ROOK) {
            moves[count++] = (Pos){.row = pos.row, .col = i};
        }
    }

    return count;
}

// A function that evaluates a move is a capture or non capture move.
void swap(BoardState *state, Pos *pos)
{
    Piece temp = state->board[pos[0].row][pos[0].col];
    Piece to = state->board[pos[1].row][pos[1].col];
    u8 isCapture = 0;
    u8 flag = 0;
    u8 passant = 0;

    if (temp.color == to.color){
        if (temp.type == KING && to.type == ROOK){
            if (temp.color == 1 && state->castling_b) {
                if (pos[1].col == 0) {
                    state->board[pos[0].row][pos[0].col - 2] = temp;
                    state->board[pos[0].row][pos[0].col - 1] = to;
                }
                else {
                    state->board[pos[0].row][pos[0].col + 1] = to;
                    state->board[pos[0].row][pos[0].col + 2] = temp;
                }
                state->board[pos[0].row][pos[0].col] = (Piece){EMPTY, -1, 0};
                state->board[pos[1].row][pos[1].col] = (Piece){EMPTY, -1, 0};
                state->castling_b = 0;
                return;
            } 
            else if (temp.color == 2 && state->castling_w) {
                if (pos[1].col == 0) {
                    state->board[pos[0].row][pos[0].col - 1] = to;
                    state->board[pos[0].row][pos[0].col - 2] = temp;
                }
                else {
                    state->board[pos[0].row][pos[0].col + 1] = to;
                    state->board[pos[0].row][pos[0].col + 2] = temp;
                }
                state->board[pos[0].row][pos[0].col] = (Piece){EMPTY, -1, 0};
                state->board[pos[1].row][pos[1].col] = (Piece){EMPTY, -1, 0};
                state->castling_w = 0;
                return;
            }
        }

    }

    if (temp.type == PAWN){
        passant = temp.color == 1? 4 : 3;
        flag = passant == pos[0].row;
    }

    if (to.color && temp.color != to.color) {
        isCapture = 1;
    }

    if (flag && to.type == EMPTY) {
        state->board[passant][pos[1].col].type = EMPTY;
        state->board[passant][pos[1].col].color = 0;
        state->board[passant][pos[1].col].value = -1;
        state->board[pos[0].row][pos[0].col] = to;
    }
    else if (isCapture) {
        to.type = EMPTY;
        to.color = 0;
        to.value = -1;
        state->board[pos[0].row][pos[0].col] = to;
    }
    else {
        state->board[pos[0].row][pos[0].col] = to;
    }

    state->board[pos[1].row][pos[1].col] = temp;
}
