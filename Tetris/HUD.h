#ifndef TETRIS_WINAPI_HUD_H
#define TETRIS_WINAPI_HUD_H

#include "windows.h"
#include "Functions.h"
#include "Tetromino.h"


class HUD {

public:
    const RECT &getRect() const;

    void setRect(const RECT &rect);

    const CHAR *getTime() const;

    void setTime(const CHAR *time);

    void draw(HDC hdc);

private:
    RECT rect;
    LPCSTR time;
    int nextTetrominoType;

    void drawNextTetromino();
};


#endif //TETRIS_WINAPI_HUD_H
