#ifndef TETRIS_WINAPI_HUD_H
#define TETRIS_WINAPI_HUD_H

#include "windows.h"
#include "Functions.h"
#include "Tetromino.h"
#include "Canvas.h"


class HUD {

public:
    void setRect(const RECT &rect);

    void setTime(double time);

    void draw(HDC hdc, Canvas canvas);

    void setNextTetrominoType(int nextTetrominoType);

    void setScore(int score);

private:
    RECT rect;
    double time;
    int score;
    int nextTetrominoType;

    void drawNextTetromino(HDC hdc, Canvas canvas);

    void drawTime(HDC hdc);

    void drawScore(HDC hdc);

};


#endif //TETRIS_WINAPI_HUD_H
