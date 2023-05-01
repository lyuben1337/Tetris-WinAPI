#include <ctime>
#include "TetrisWindow.h"
#include "Game.h"
#include "HUD.h"
#include "Menu.h"

Menu menu;
Game game;
RECT clientRect;
HDC hdc;
PAINTSTRUCT ps;
HUD hud;

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
        case WM_CREATE: {
            GetClientRect(hWnd, &clientRect);
            menu.setRect(GetMenuRect(clientRect, BLOCK_SIZE));
            menu.setOpened(true);
            SetTimer(hWnd, 1, 20, TimerRedrawingProc);
        }
            break;

        case WM_KEYDOWN: {
            if (menu.isOpened()) {
                if (menu.getChosenItem() == MENU_START) {
                    switch (wParam) {
                        case VK_LEFT:
                            if (menu.getDifficultyLevel() > DIFFICULTY_EASY) {
                                menu.setDifficultyLevel(menu.getDifficultyLevel() - 1);
                            }
                            break;
                        case VK_RIGHT:
                            if (menu.getDifficultyLevel() < DIFFICULTY_HARD) {
                                menu.setDifficultyLevel(menu.getDifficultyLevel() + 1);
                            }
                            break;
                    }
                }
                switch (wParam) {
                    case VK_DOWN:
                        if (menu.getChosenItem() < MENU_EXIT) {
                            menu.setChosenItem(menu.getChosenItem() + 1);
                        }
                        break;
                    case VK_UP:
                        if (menu.getChosenItem() > MENU_START) {
                            menu.setChosenItem(menu.getChosenItem() - 1);
                        }
                        break;
                    case VK_ESCAPE:
                        menu.setOpenedAbout(false);
                        break;
                    case VK_RETURN: {
                        switch (menu.getChosenItem()) {
                            case MENU_START:
                                menu.setOpened(false);
                                startGame();
                                SetTimer(hWnd, 2, 3000 / (game.getDifficulty() * 2), TimerFallingProc);
                                break;
                            case MENU_EXIT:
                                DestroyWindow(hWnd);
                                break;
                            case MENU_ABOUT:
                                menu.setOpenedAbout(true);
                                break;
                        }
                    }
                        break;
                }
            } else {
                switch (wParam) {
                    case VK_DOWN:
                        game.currentTetromino.move(DIRECTION_DOWN, game.canvas);
                        break;
                    case VK_LEFT:
                        game.currentTetromino.move(DIRECTION_LEFT, game.canvas);
                        break;
                    case VK_RIGHT:
                        game.currentTetromino.move(DIRECTION_RIGHT, game.canvas);
                        break;
                    case VK_SPACE:
                        game.currentTetromino.rotate(game.canvas);
                        break;
                    case VK_ESCAPE:
                        menu.setOpened(true);
                        KillTimer(hWnd, 2);
                        break;
                }
            }
            break;
        }

        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            if (menu.isOpened()) {
                menu.draw(hdc);
            } else {
                game.canvas.draw(hdc);
                hud.draw(hdc, game.canvas);
                game.currentTetromino.draw(hdc, game.canvas);
            }
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
    if (!menu.isOpened()) {
        if (!game.currentTetromino.canMove(DIRECTION_DOWN, game.canvas)) {
            game.canvas.addBlocks(game.currentTetromino.getBlocks());
            game.setScore(game.getScore() + game.canvas.breakLines());
            game.currentTetromino = game.nextTetromino;
            game.nextTetromino = Tetromino::RandomTetromino();
            hud.setNextTetrominoType(game.nextTetromino.getType());
            hud.setScore(game.getScore());
            if (!game.currentTetromino.canMove(DIRECTION_DOWN, game.canvas)) {
                menu.setOpened(true);
                MessageBoxA(hwnd, "GAME OVER!", "GAME OVER!", NULL);
            }
        }
        hud.setTime(game.getGameTime());
    }
    InvalidateRect(hwnd, NULL, TRUE);
}

void TetrisWindow::TimerFallingProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
    if (!menu.isOpened()) {
        game.currentTetromino.move(DIRECTION_DOWN, game.canvas);
    }
}

void TetrisWindow::startGame() {
    game = Game();
    hud = HUD();
    game.canvas = GetCanvasRect(clientRect, BLOCK_SIZE);
    game.setDifficulty(menu.getDifficultyLevel());
    hud.setRect(GetHUDRect(clientRect, BLOCK_SIZE));
    hud.setNextTetrominoType(game.nextTetromino.getType());
    hud.setTime(0);
    hud.setScore(0);
}