#ifndef TETRIS_WINAPI_TETRISWINDOW_H
#define TETRIS_WINAPI_TETRISWINDOW_H


#include <windows.h>
#include "Canvas.h"
#include "Functions.h"


class TetrisWindow {
public:
    TetrisWindow(HINSTANCE hInstance, LPCTSTR title);

    void RunMessageLoop();

private:
    HWND hWnd;

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    ATOM MyRegisterClass(HINSTANCE hInstance);

    BOOL InitInstance(HINSTANCE hInstance, LPCTSTR title);

    static void CALLBACK TimerRedrawingProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
};


#endif //TETRIS_WINAPI_TETRISWINDOW_H
