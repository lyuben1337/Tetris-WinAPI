#include <string>
#include "HUD.h"

void HUD::draw(HDC hdc, Canvas canvas) {
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
    drawNextTetromino(hdc, canvas);
    drawTime(hdc);
    drawScore(hdc);
}

const RECT &HUD::getRect() const {
    return rect;
}

void HUD::setRect(const RECT &rect) {
    HUD::rect = rect;
}

void HUD::drawNextTetromino(HDC hdc, Canvas canvas) {
    int x;
    switch (this->nextTetrominoType) {
        case I_TETROMINO:
            x = 15;
            break;
        case O_TETROMINO:
            x = 15;
            break;
        case T_TETROMINO:
            x = 14;
            break;
        case S_TETROMINO:
            x = 15;
            break;
        case Z_TETROMINO:
            x = 14;
            break;
        case J_TETROMINO:
            x = 14;
            break;
        case L_TETROMINO:
            x = 15;
            break;
    }
    Tetromino tetromino = Tetromino(x, 9, this->nextTetrominoType);
    tetromino.draw(hdc, canvas);
}

int HUD::getNextTetrominoType() const {
    return nextTetrominoType;
}

void HUD::setNextTetrominoType(int nextTetrominoType) {
    HUD::nextTetrominoType = nextTetrominoType;
}

void HUD::drawTime(HDC hdc) {
    // Создаем новый объект шрифта
    HFONT hFont = CreateFont(32, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                             DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                             CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                             DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));

    // Устанавливаем новый шрифт на контекст устройства
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

    // Рассчитываем значения минут и секунд
    int seconds = this->time / 1000;
    int minutes = seconds / 60;
    seconds %= 60;

    // Форматируем строку с таймером
    std::string timerString = std::to_string(minutes) + ":" +
                              (seconds < 10 ? "0" : "") + std::to_string(seconds);

    // Рисуем текст с таймером на контексте устройства
    SIZE size;
    GetTextExtentPoint32(hdc, timerString.c_str(), strlen(timerString.c_str()), &size);
    TextOut(hdc, (this->rect.left + this->rect.right) / 2 - size.cx / 2, this->rect.top + BLOCK_SIZE, timerString.c_str(), timerString.length());

    // Восстанавливаем старый шрифт и удаляем новый объект шрифта
    SelectObject(hdc, hOldFont);
    DeleteObject(hFont);
}

double HUD::getTime() const {
    return time;
}

void HUD::setTime(double time) {
    HUD::time = time;
}

void HUD::drawScore(HDC hdc) {
    HFONT hFont = CreateFont(32, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                             DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                             CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                             DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));

    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

    std::string scoreString = "Score: " + std::to_string(this->score);

    SIZE size;
    GetTextExtentPoint32(hdc, scoreString.c_str(), strlen(scoreString.c_str()), &size);
    TextOut(hdc, (this->rect.left + this->rect.right) / 2 - size.cx / 2, this->rect.top + 2 * BLOCK_SIZE, scoreString.c_str(), scoreString.length());


    SelectObject(hdc, hOldFont);
    DeleteObject(hFont);
}

int HUD::getScore() const {
    return score;
}

void HUD::setScore(int score) {
    HUD::score = score;
}
