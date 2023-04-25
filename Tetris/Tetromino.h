#ifndef TETRIS_WINAPI_TETROMINO_H
#define TETRIS_WINAPI_TETROMINO_H


#include "Coordinate.h"
#include "Block.h"
#include "vector"
#include "windows.h"

class Tetromino {
public:
    void draw(HDC hdc);
protected:
    Coordinate coordinate;
    int color;
    std::vector<Block> blocks{};
};


#endif //TETRIS_WINAPI_TETROMINO_H
