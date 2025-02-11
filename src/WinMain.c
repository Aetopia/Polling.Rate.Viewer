#include <windows.h>
#include <hidusage.h>

LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static LARGE_INTEGER cFrequency = {}, cPrevious = {};
    static ULONGLONG cElapsed = {};

    switch (uMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(EXIT_SUCCESS);
        break;

    case WM_CREATE: {
        QueryPerformanceFrequency(&cFrequency);
        QueryPerformanceCounter(&cPrevious);
        cElapsed = GetTickCount64();

        RegisterRawInputDevices(&(RAWINPUTDEVICE){.hwndTarget = hWnd,
                                                  .usUsage = HID_USAGE_GENERIC_MOUSE,
                                                  .usUsagePage = HID_USAGE_GENERIC_POINTER,
                                                  .dwFlags = RIDEV_INPUTSINK},
                                1, sizeof(RAWINPUTDEVICE));
        break;
    }

    case WM_INPUT: {
        LARGE_INTEGER cCurrent;
        QueryPerformanceCounter(&cCurrent);

        if ((GetTickCount64() - cElapsed) >= 1000)
        {
            CHAR szOutput[RESTART_MAX_CMD_LINE + 1] = {};
            wsprintfA(szOutput, "Polling Rate: %ld Hz\n",
                      (ULONG)(1.0 / ((DOUBLE)(cCurrent.QuadPart - cPrevious.QuadPart) / cFrequency.QuadPart)));

            WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), szOutput, lstrlenA(szOutput), NULL, NULL);

            cElapsed = GetTickCount64();
        }

        cPrevious = cCurrent;
        break;
    }
    }

    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

VOID mainCRTStartup()
{
    if (CreateWindowExW(WS_EX_LEFT,
                        (PCWSTR)(INT_PTR)RegisterClassW(&(WNDCLASSW){
                            .hInstance = GetModuleHandleW(NULL), .lpfnWndProc = WndProc, .lpszClassName = L" "}),
                        NULL, WS_OVERLAPPED, (INT){}, (INT){}, (INT){}, (INT){}, HWND_MESSAGE, NULL,
                        GetModuleHandleW(NULL), NULL))
    {
        MSG _ = {};
        
        while (GetMessageW(&_, NULL, (UINT){}, (UINT){}))
        {
            TranslateMessage(&_);
            DispatchMessageW(&_);
        }
    }

    ExitProcess(EXIT_SUCCESS);
}