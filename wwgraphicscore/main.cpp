#include <windows.h>
#include <iostream>
#include <chrono>
#include <cmath>
#include "Drawer.h"
#include "../wwmathcore/MMatrix.h"
#include <typeinfo>
#include <windowsx.h>

/* Create nice looking controls */
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#define TESTING 0

/* Name of our class and the title */
const char *clsName = "WinAPI";
char *title = const_cast<char*>("Windows API");

/* Global flag for our message loop */
bool running = true;

/* Handle to the window */
HWND hWnd = NULL;

WWGraphics::Drawer* d;

auto lastTime = std::chrono::high_resolution_clock::now().time_since_epoch();
int countedFps = 0;

void paintStuff(HWND hWnd) {
    //Control code
    RECT rect;
    GetClientRect(hWnd, &rect);
    int w = rect.right - rect.left;
    int h = rect.bottom - rect.top;
    d->prepare(hWnd, w, h);

    //Time in picoseconds
    auto now = std::chrono::high_resolution_clock::now().time_since_epoch();

    auto timePassed = now.count() - lastTime.count();
    countedFps++;

    if(timePassed > 1000000000) {
        lastTime = now;
        std::cout << "Fps: " << countedFps << " " << std::endl;

        countedFps = 0;
    }
}

/* A windows callback procedure. */
LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        /* Message created when the user tries to close the window */

        case WM_SIZE:
            return 0;
        case WM_PAINT:
            paintStuff(hWnd);
            return 0;

        case WM_CREATE:
            d = new WWGraphics::Drawer();
            return 0;

        case WM_CHAR:
            //std::cout << "key down " << char(wParam) <<std::endl;
            return 0;
        case WM_KEYDOWN:
            d->getDownKeys()[wParam] = true;
            return 0;
        case WM_KEYUP:
            d->getDownKeys()[wParam] = false;
            return 0;
        case WM_RBUTTONDOWN:
            d->mouseButtonDown('r', true);
            return 0;
        case WM_RBUTTONUP:
            d->mouseButtonDown('r', false);
            return 0;
        case WM_LBUTTONDOWN:
            d->mouseButtonDown('l', true);
            return 0;
        case WM_LBUTTONUP:
            d->mouseButtonDown('l', false);
            return 0;
        case WM_MOUSEMOVE:
            d->mouseMoved(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            return 0;

        case WM_CLOSE:
            DestroyWindow(hWnd);
            return 0;
        case WM_DESTROY:
            delete d;
            running = false;
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}

void test() {
#if TESTING
    std::cout << "Everything is fine, nothing to test" << std::endl;

    WWGraphics::Screen screen(10, 10);

    screen.drawLine(-10, -10, 5, 5, 0xff00ff);

    std::cout << "Exiting" << std::endl;
    exit(0);
#endif
}

/* Entry point of our application */
int WINAPI WinMain(HINSTANCE hInstance,        /* A handle to the current instance of the application. */
                   HINSTANCE hPrevInstance,    /* A handle to the previous instance of the application. */
                   LPSTR lpCmdLine,            /* The command line for the application, excluding the program name. */
                   int nCmdShow)                /* Controls how the window is to be shown. */
{
    std::srand((unsigned)time(nullptr));

    test();

    WNDCLASSEX WndEx;
    MSG msg;

    WndEx.cbSize = sizeof(WNDCLASSEX);                    /* The size, in bytes, of this structure. */
    WndEx.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;    /* The class style(s) */
    WndEx.lpfnWndProc = (WNDPROC) WndProc;                        /* A pointer to the window procedure. */
    WndEx.cbClsExtra = 0;                                    /* The number of extra bytes to allocate following the window-class structure. */
    WndEx.cbWndExtra = 0;                                    /* The number of extra bytes to allocate following the window instance. */
    WndEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);        /* A handle to the class icon. */
    WndEx.hCursor = LoadCursor(NULL, IDC_ARROW);            /* A handle to the class cursor. */
    WndEx.hbrBackground = NULL;                                    /* A handle to the class background brush. */
    WndEx.lpszMenuName = NULL;                                    /* We're not using a menu here */
    WndEx.lpszClassName = clsName;                                /* A pointer to a string that contains the class name */
    WndEx.hInstance = hInstance;                            /* A handle to the instance that contains the window procedure for the class. */
    WndEx.hIconSm = LoadIcon(NULL,
                             IDI_APPLICATION);        /* A handle to a small icon that is associated with the window class */

    /* Register the windows class */
    if (!RegisterClassEx(&WndEx)) {
        MessageBox(NULL, "Failed to register class", "ERROR", MB_OK);
        return 0;
    }


    if (!(hWnd = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, /* The extended window style *//* Create the window */
                                clsName,                            /* A pointer to a string that contains the class name */
                                title,                                /* A pointer to a string that contains the title of the window */
                                WS_OVERLAPPEDWINDOW |                /* The style of the window being created */
                                WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                                CW_USEDEFAULT, CW_USEDEFAULT,        /* initial x,y position of the window */
                                16*10*2, 9*10*2,                            /* initial x,y size of the window */
                                NULL,                                /* A handle to the parent or owner window */
                                NULL,                                /* A handle to a menu */
                                hInstance,                            /* A handle to the instance of the window */
                                NULL)))                                /* lParam */
    {
        MessageBox(NULL, "Failed to create the window", "ERROR", MB_OK);
        return 0;
    }

    /* The window is initially hidden, we need to show it */
    ShowWindow(hWnd, SW_SHOW);
    /* The main message loop of our program */
    while (running) {
        /* Are there any messages in the message queue? */
        InvalidateRect(hWnd, NULL, 0);
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            /* translate and dispatch the message */
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return msg.wParam;
}
