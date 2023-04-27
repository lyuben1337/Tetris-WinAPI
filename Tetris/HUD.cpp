#include "HUD.h"

void HUD::draw(HDC hdc) {
    HBRUSH hBrushFill = CreateSolidBrush(RGB(0, 0, 0));
    HBRUSH hBrushBorder = CreateSolidBrush(RGB(255, 255, 255));
    int borderSize = 2;

    RECT borderRect = this->rect;
    borderRect.bottom += borderSize;
    borderRect.left -= borderSize;
    borderRect.top -= borderSize;
    borderRect.right += borderSize;

    FillRect(hdc, &borderRect, hBrushBorder);
    FillRect(hdc, &this->rect, hBrushFill);

    DeleteObject(hBrushFill);
    DeleteObject(hBrushBorder);
}

const RECT &HUD::getRect() const {
    return rect;
}

void HUD::setRect(const RECT &rect) {
    HUD::rect = rect;
}

const CHAR *HUD::getTime() const {
    return time;
}

void HUD::setTime(const CHAR *time) {
    HUD::time = time;
}

void HUD::drawNextTetromino() {
    Tetromino tetromino = Tetromino(15, 9, this->nextTetrominoType);
}
