#ifndef TETRIS_WINAPI_TETRISWINDOW_H
#define TETRIS_WINAPI_TETRISWINDOW_H


#include <windows.h>
#include "Canvas.h"
#include "Functions.h"
#include "Block.h"
#include "Tetromino.h"


class TetrisWindow {
public:
    TetrisWindow(HINSTANCE hInstance, LPCTSTR title);

    static void RunMessageLoop();

private:
    HWND hWnd{};

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    static ATOM MyRegisterClass(HINSTANCE hInstance);

    BOOL InitInstance(HINSTANCE hInstance, LPCTSTR title);

    static void CALLBACK TimerRedrawingProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

    static void CALLBACK TimerFallingProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

    static void startGame();
};


#endif //TETRIS_WINAPI_TETRISWINDOW_H
