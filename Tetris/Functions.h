#ifndef TETRIS_WINAPI_FUNCTIONS_H
#define TETRIS_WINAPI_FUNCTIONS_H

#pragma once

#include "windows.h"

// Constants
#define BLOCK_SIZE 50

// Difficulty level
#define DIFFICULTY_EASY   1
#define DIFFICULTY_MEDIUM 2
#define DIFFICULTY_HARD   3

// Move directions
#define D_DOWN  1
#define D_LEFT  2
#define D_RIGHT 3

// Block colors
#define COLOR_CYAN      1
#define COLOR_YELLOW    2
#define COLOR_PURPLE    3
#define COLOR_GREEN     4
#define COLOR_RED       5
#define COLOR_BLUE      6
#define COLOR_ORANGE    7

// Tetromino types
#define I_TETROMINO 1
#define O_TETROMINO 2
#define T_TETROMINO 3
#define S_TETROMINO 4
#define Z_TETROMINO 5
#define J_TETROMINO 6
#define L_TETROMINO 7

// Tetromino rotations
#define ROTATION_0      1
#define ROTATION_90     2
#define ROTATION_180    3
#define ROTATION_270    4



// Functions
RECT GetCanvasRect(RECT clientRect, int blockSize);
HBRUSH CreateBrush(int color);

#endif //TETRIS_WINAPI_FUNCTIONS_H