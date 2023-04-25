#ifndef TETRIS_WINAPI_TETRISWINDOW_H
#define TETRIS_WINAPI_TETRISWINDOW_H


#include <windows.h>

class TetrisWindow {
public:
    TetrisWindow(HINSTANCE hInstance, LPCTSTR title);

    static void RunMessageLoop();

private:
    HWND hWnd{};

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    static ATOM MyRegisterClass(HINSTANCE hInstance);

    BOOL InitInstance(HINSTANCE hInstance, LPCTSTR title);
};


#endif //TETRIS_WINAPI_TETRISWINDOW_H
