#include <windows.h>
#include "TetrisWindow.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    SetProcessDpiAwareness(PROCESS_SYSTEM_DPI_AWARE);
    TetrisWindow tetrisWindow(hInstance, "Tetris");
    TetrisWindow::RunMessageLoop();
    return 0;
}

