#include "Menu.h"

void Menu::draw(HDC hdc) {
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

    if(openedAbout) {
        drawAbout(hdc);
    } else {
        drawItems(hdc);
    }
}

void Menu::drawAbout(HDC hdc) {
    HBRUSH hBrushFill = CreateSolidBrush(RGB(255, 255, 255));
    HFONT hFont = CreateFont(48, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                             DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                             CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                             DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
    SetBkMode(hdc, TRANSPARENT);

    // START GAME
    SIZE size;
    LPCSTR str = "Created by Vladyslav Liubchyk";
    SetTextColor(hdc, RGB(255, 255, 255));
    GetTextExtentPoint32(hdc, str, strlen(str), &size);
    TextOut(hdc, (this->rect.left + this->rect.right) / 2 - size.cx / 2,
            (this->rect.top + this->rect.bottom) / 2 - size.cy / 2, str,
            strlen(str));

    SelectObject(hdc, hOldFont);
    DeleteObject(hFont);
}

void Menu::drawItems(HDC hdc) {
    HBRUSH hBrushFill = CreateSolidBrush(RGB(255, 255, 255));
    HFONT hFont = CreateFont(80, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                             DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                             CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                             DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
    SetBkMode(hdc, TRANSPARENT);

    // START GAME
    SIZE size;
    SetTextColor(hdc, this->chosenItem == MENU_START ? RGB(255, 0, 0) : RGB(255, 255, 255));
    GetTextExtentPoint32(hdc, "START GAME", strlen("START GAME"), &size);
    TextOut(hdc, (this->rect.left + this->rect.right) / 2 - size.cx / 2,
            (this->rect.top + this->rect.bottom) / 2 - 2 * BLOCK_SIZE - size.cy / 2, "START GAME",
            strlen("START GAME"));

    // ABOUT
    SetTextColor(hdc, this->chosenItem == MENU_ABOUT ? RGB(255, 0, 0) : RGB(255, 255, 255));
    GetTextExtentPoint32(hdc, "ABOUT", strlen("ABOUT"), &size);
    TextOut(hdc, (this->rect.left + this->rect.right) / 2 - size.cx / 2,
            (this->rect.top + this->rect.bottom) / 2 - size.cy / 2, "ABOUT",
            strlen("ABOUT"));

    // EXIT
    SetTextColor(hdc, this->chosenItem == MENU_EXIT ? RGB(255, 0, 0) : RGB(255, 255, 255));
    GetTextExtentPoint32(hdc, "EXIT", strlen("EXIT"), &size);
    TextOut(hdc, (this->rect.left + this->rect.right) / 2 - size.cx / 2,
            (this->rect.top + this->rect.bottom) / 2 + 2 * BLOCK_SIZE - size.cy / 2, "EXIT",
            strlen("EXIT"));

    SelectObject(hdc, hOldFont);
    DeleteObject(hFont);

}

void Menu::setRect(const RECT &rect) {
    Menu::rect = rect;
}

const RECT &Menu::getRect() const {
    return rect;
}

int Menu::getChosenItem() const {
    return chosenItem;
}

void Menu::setChosenItem(int chosenItem) {
    Menu::chosenItem = chosenItem;
}

bool Menu::isOpened() const {
    return opened;
}

void Menu::setOpened(bool opened) {
    Menu::opened = opened;
}

bool Menu::isOpenedAbout() const {
    return openedAbout;
}

void Menu::setOpenedAbout(bool openedAbout) {
    Menu::openedAbout = openedAbout;
}


