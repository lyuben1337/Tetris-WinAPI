#ifndef TETRIS_WINAPI_TETROMINO_H
#define TETRIS_WINAPI_TETROMINO_H


#include "Coordinate.h"
#include "Block.h"
#include "vector"
#include "windows.h"
#include "Canvas.h"

class Tetromino {
public:
    Tetromino(int x, int y, int type = O_TETROMINO);
    void draw(HDC hdc, const Canvas& canvas);
private:
    int type{};
    Coordinate coordinate{};
    int color{};
    std::vector<Block> blocks{};
};


#endif //TETRIS_WINAPI_TETROMINO_H
