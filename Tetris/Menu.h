#ifndef TETRIS_WINAPI_MENU_H
#define TETRIS_WINAPI_MENU_H

#include "windows.h"
#include "Functions.h"

class Menu {

public:
    void draw(HDC hdc);
    void drawItems(HDC hdc);
    void drawAbout(HDC hdc);
    void setRect(const RECT &rect);
    const RECT &getRect() const;
    int getChosenItem() const;
    void setChosenItem(int chosenItem);
    bool isOpened() const;
    void setOpened(bool opened);

private:
    RECT rect{};

    bool openedAbout = false;
public:
    bool isOpenedAbout() const;

    void setOpenedAbout(bool openedAbout);

private:
    bool opened = true;
    int chosenItem = MENU_START;

};


#endif //TETRIS_WINAPI_MENU_H
