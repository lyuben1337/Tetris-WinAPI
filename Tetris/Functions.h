#ifndef TETRIS_WINAPI_FUNCTIONS_H
#define TETRIS_WINAPI_FUNCTIONS_H

#pragma once

#include "windows.h"
#include "Canvas.h"

//Constants:

#define BLOCK_SIZE 50

// Move directions
#define D_BOTTOM    1
#define D_LEFT      2
#define D_RIGHT     3

//Functions:
RECT GetCanvasRect(RECT clientRect, int blockSize);

#endif //TETRIS_WINAPI_FUNCTIONS_H