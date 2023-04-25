#ifndef TETRIS_WINAPI_CANVAS_H
#define TETRIS_WINAPI_CANVAS_H
#include "windows.h"
#include "map"
#include "Coordinate.h"
#include "vector"
#include "Block.h"

class Block;

class Canvas {
public:
    Canvas();

    void draw(HDC hdc);

    const RECT &getRect() const;

    void setRect(const RECT &rect);

    bool isCoordinateFree(const Coordinate &coordinate);

private:
    RECT rect{};
    std::map<Coordinate, bool> coordinates{};
    std::vector<Block> blocks{};
};


#endif //TETRIS_WINAPI_CANVAS_H
