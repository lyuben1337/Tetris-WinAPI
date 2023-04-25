#ifndef TETRIS_WINAPI_CANVAS_H
#define TETRIS_WINAPI_CANVAS_H
#include "windows.h"
#include "map"
#include "Coordinate.h"

class Canvas {
public:
    Canvas();

    void draw(HDC hdc);

    const RECT &getRect() const;

    void setRect(const RECT &rect);

private:
    RECT rect{};
    std::map<Coordinate, bool> coordinates{};
};


#endif //TETRIS_WINAPI_CANVAS_H
