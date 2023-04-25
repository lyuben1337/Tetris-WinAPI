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
