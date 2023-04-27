#include "Functions.h"

RECT GetCanvasRect(RECT clientRect, int blockSize) {
    int x = (clientRect.right - clientRect.left) / 2;
    int y = (clientRect.bottom - clientRect.top) / 2;
    int width = blockSize * 10;
    int height = blockSize * 20;
    int left = x - width / 2;
    int top = y - height / 2;
    int right = left + width;
    int bottom = top + height;

    RECT canvasRect = { left, top, right, bottom };

    return canvasRect;
}

HBRUSH CreateBrush(int color) {
    switch (color) {
        case COLOR_YELLOW:
            return CreateSolidBrush(RGB(255, 255, 0));
        case COLOR_CYAN:
            return CreateSolidBrush(RGB(48, 213, 200));
        case COLOR_PURPLE:
            return CreateSolidBrush(RGB(160, 32, 240));
        case COLOR_GREEN:
            return CreateSolidBrush(RGB(0, 255, 0));
        case COLOR_RED:
            return CreateSolidBrush(RGB(255, 0, 0));
        case COLOR_BLUE:
            return CreateSolidBrush(RGB(0, 0, 255));
        case COLOR_ORANGE:
            return CreateSolidBrush(RGB(255, 186, 0));
        default:
            return CreateSolidBrush(RGB(255, 255, 255));
    }
}

RECT GetHUDRect(RECT clientRect, int blockSize) {
    RECT canvasRect = GetCanvasRect(clientRect, blockSize);
    int left = canvasRect.right + 3 * blockSize;
    int top = canvasRect.top + 4 * blockSize;
    int right = left + 5 * blockSize;
    int bottom = top + 10 * blockSize;

    RECT HUDRect = { left, top, right, bottom };

    return HUDRect;
}
