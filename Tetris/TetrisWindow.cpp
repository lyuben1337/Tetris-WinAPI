#include <ctime>
#include "TetrisWindow.h"

Canvas canvas;
RECT clientRect;
Tetromino tetromino(0, 0, L_TETROMINO);
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
            SetTimer(hWnd, 1, 20, TimerRedrawingProc);

            GetClientRect(hWnd, &clientRect);
            canvas.setRect(GetCanvasRect(clientRect, BLOCK_SIZE));
            break;

        case WM_KEYDOWN: {
            switch (wParam) {
                case VK_DOWN:
                    tetromino.move(D_DOWN, canvas);
                    break;
                case VK_LEFT:
                    tetromino.move(D_LEFT, canvas);
                    break;
                case VK_RIGHT:
                    tetromino.move(D_RIGHT, canvas);
                    break;
                case VK_SPACE:
                    tetromino.rotate(canvas);
                    break;
            }
            break;
        }

        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            canvas.draw(hdc);
            tetromino.draw(hdc, canvas);
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
