#include <windows.h>
#include "TetrisWindow.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    auto* tetrisWindow = new TetrisWindow(hInstance, "Tetris");
    tetrisWindow->RunMessageLoop();
    delete tetrisWindow;
    return 0;
}

