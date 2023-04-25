//
// Created by lyube on 4/25/2023.
//

#include "Canvas.h"

Canvas::Canvas() {
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 10; ++j) {
            Coordinate coordinate(i, j);
            coordinates[coordinate] = true;
        }
    }
}

const RECT &Canvas::getRect() const {
    return rect;
}

void Canvas::setRect(const RECT &rect) {
    Canvas::rect = rect;
}

void Canvas::draw(HDC hdc) {
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
