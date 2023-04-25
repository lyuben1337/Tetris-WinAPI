#ifndef TETRIS_WINAPI_BLOCK_H
#define TETRIS_WINAPI_BLOCK_H

#include "windows.h"
#include "Functions.h"
#include "Coordinate.h"
#include "Canvas.h"

class Canvas;

class Block {
public:
    Block(int x, int y, int color);
    void draw(HDC hdc, const Canvas& canvas);

    const Coordinate &getCoordinate() const;

    void setCoordinate(const Coordinate &coordinate);

private:
    Coordinate coordinate;
    int color;
};


#endif //TETRIS_WINAPI_BLOCK_H
