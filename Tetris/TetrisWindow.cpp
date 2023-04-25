#include <ctime>
#include "TetrisWindow.h"

Canvas canvas;
Block block1(0, 0, COLOR_ORANGE);
Block block2(1, 0, COLOR_CYAN);
Block block3(0, 1, COLOR_BLUE);
Block block4(1, 1, COLOR_GREEN);
RECT clientRect;
HDC hdc;
PAINTSTRUCT ps;

void TetrisWindow::RunMessageLoop() {
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

TetrisWindow::TetrisWindow(HINSTANCE hInstance, LPCTSTR title) {
    MyRegisterClass(hInstance);
    InitInstance(hInstance, title);
}

LRESULT TetrisWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    switch (message) {
        case WM_CREATE:
            srand(time(NULL));
            SetTimer(hWnd, 1, 50, TimerRedrawingProc);

            GetClientRect(hWnd, &clientRect);
            canvas.setRect(GetCanvasRect(clientRect, BLOCK_SIZE));
            break;

        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            canvas.draw(hdc);
            block1.draw(hdc, canvas);
            block2.draw(hdc, canvas);
            block3.draw(hdc, canvas);
            block4.draw(hdc, canvas);
            EndPaint(hWnd, &ps);
            break;

        case WM_DESTROY:
            KillTimer(hWnd, 1);
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

ATOM TetrisWindow::MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = &TetrisWindow::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_HAND);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "Tetris";
    wcex.hIconSm = NULL;
    return RegisterClassEx(&wcex);
}

BOOL TetrisWindow::InitInstance(HINSTANCE hInstance, LPCTSTR title) {
    hWnd = CreateWindow("Tetris",
                        title,
                        WS_POPUP,
                        0,
                        0,
                        GetSystemMetrics(SM_CXSCREEN),
                        GetSystemMetrics(SM_CYSCREEN),
                        NULL,
                        NULL,
                        hInstance,
                        NULL);
    if (!hWnd) {
        return FALSE;
    }
    ShowWindow(hWnd, SW_SHOWDEFAULT);
    UpdateWindow(hWnd);
    return TRUE;
}

void TetrisWindow::TimerRedrawingProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
    InvalidateRect(hwnd, NULL, TRUE);
}
