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
    static Tetromino RandomTetromino();
    void draw(HDC hdc, const Canvas& canvas);
    void move(int direction, Canvas canvas);
    void rotate(Canvas canvas);
    bool canMove(int direction, Canvas canvas);
    const std::vector<Block> &getBlocks() const;
    int getType() const;

private:
    int type{};
    int rotation{};
    Coordinate coordinate{};
    int color{};
    std::vector<Block> blocks{};
    bool canRotate(Canvas canvas);
};


#endif //TETRIS_WINAPI_TETROMINO_H
