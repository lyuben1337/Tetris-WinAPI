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

    int getChosenItem() const;

    void setChosenItem(int chosenItem);

    bool isOpened() const;

    void setOpened(bool opened);

    int getDifficultyLevel() const;

    void setDifficultyLevel(int difficultyLevel);

    void setOpenedAbout(bool openedAbout);

private:
    RECT rect{};
    bool openedAbout = false;
    bool opened = true;
    int chosenItem = MENU_START;
    int difficultyLevel = DIFFICULTY_MEDIUM;

};


#endif //TETRIS_WINAPI_MENU_H
