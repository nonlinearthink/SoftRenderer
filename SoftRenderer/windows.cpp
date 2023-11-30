#ifdef _WIN32

#include "Windows.h"

#include "renderer.h"

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam,
                                 LPARAM lparam) {
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, msg, wparam, lparam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "SoftRenderer Window Class";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProcedure;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    HWND hWnd = CreateWindowEx(0,                    // Optional window styles.
                               CLASS_NAME,           // Window class
                               "SoftRenderer",       // Window text
                               WS_OVERLAPPEDWINDOW,  // Window style

                               // Size and position
                               CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                               CW_USEDEFAULT,

                               NULL,       // Parent window
                               NULL,       // Menu
                               hInstance,  // Instance handle
                               NULL        // Additional application data
    );

    if (hWnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hWnd, nCmdShow);

    RECT rect;
    int width, height;
    if (GetWindowRect(hWnd, &rect)) {
        width = rect.right - rect.left;
        height = rect.bottom - rect.top;
    } else {
        MessageBox(NULL, "Get Window Rect Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    SoftRenderer renderer(width, height, hWnd);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        renderer.update(hWnd);
    }

    return (int)msg.wParam;
}

#else

#include <iostream>

int main() {
    std::cout << "Unsupported operating systems." << std::endl;
    return 0;
}

#endif
