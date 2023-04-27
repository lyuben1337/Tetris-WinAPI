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

    Canvas(RECT rect);

    void draw(HDC hdc);

    const RECT &getRect() const;

    void setRect(const RECT &rect);

    bool isCoordinateFree(const Coordinate &coordinate);

    void addBlocks(const std::vector<Block>& blocks);

    int breakLines();

    const std::vector<Block> &getBlocks() const;

private:

    void breakLine(const int& i);

    RECT rect{};
    std::map<Coordinate, bool> coordinates{};
    std::vector<Block> blocks{};
};


#endif //TETRIS_WINAPI_CANVAS_H
