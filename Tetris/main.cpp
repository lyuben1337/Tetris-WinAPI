#include <windows.h>
#include "TetrisWindow.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    __attribute__((unused)) TetrisWindow tetrisWindow(hInstance, "Tetris");
    TetrisWindow::RunMessageLoop();
    return 0;
}

