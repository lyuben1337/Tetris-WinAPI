#include <ctime>
#include "TetrisWindow.h"

Canvas canvas;
RECT clientRect;
Tetromino currentTetromino = Tetromino::RandomTetromino();
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
            GetClientRect(hWnd, &clientRect);
            canvas.setRect(GetCanvasRect(clientRect, BLOCK_SIZE));
            SetTimer(hWnd, 1, 20, TimerRedrawingProc);
            SetTimer(hWnd, 2, 1500, TimerFallingProc);
            break;

        case WM_KEYDOWN: {
            switch (wParam) {
                case VK_DOWN:
                    currentTetromino.move(D_DOWN, canvas);
                    break;
                case VK_LEFT:
                    currentTetromino.move(D_LEFT, canvas);
                    break;
                case VK_RIGHT:
                    currentTetromino.move(D_RIGHT, canvas);
                    break;
                case VK_SPACE:
                    currentTetromino.rotate(canvas);
                    break;
            }
            break;
        }

        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            canvas.draw(hdc);
            currentTetromino.draw(hdc, canvas);
            EndPaint(hWnd, &ps);
            break;

        case WM_DESTROY:
            KillTimer(hWnd, 1);
            KillTimer(hWnd, 2);
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
    if(!currentTetromino.canMove(D_DOWN, canvas)) {
        canvas.addBlocks(currentTetromino.getBlocks());
        currentTetromino = Tetromino::RandomTetromino();
        if(!currentTetromino.canMove(D_DOWN, canvas)) {
            DestroyWindow(hwnd);
        }
    }
    InvalidateRect(hwnd, NULL, TRUE);
}

void TetrisWindow::TimerFallingProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
    if(!currentTetromino.canMove(D_DOWN, canvas)) {
        canvas.addBlocks(currentTetromino.getBlocks());
        currentTetromino = Tetromino::RandomTetromino();
        if(!currentTetromino.canMove(D_DOWN, canvas)) {
            DestroyWindow(hwnd);
        }
    }
    currentTetromino.move(D_DOWN, canvas);
}
