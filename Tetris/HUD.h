#ifndef TETRIS_WINAPI_HUD_H
#define TETRIS_WINAPI_HUD_H

#include "windows.h"
#include "Functions.h"
#include "Tetromino.h"
#include "Canvas.h"


class HUD {

public:
    const RECT &getRect() const;

    void setRect(const RECT &rect);

    double getTime() const;

    void setTime(double time);

    void draw(HDC hdc, Canvas canvas);

    int getNextTetrominoType() const;

    void setNextTetrominoType(int nextTetrominoType);

    int getScore() const;

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
