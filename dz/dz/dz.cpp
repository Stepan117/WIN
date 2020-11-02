// dz.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "dz.h"
#include <math.h>
#include <float.h>
#include <vector> 
#include <commctrl.h>
#include <math.h>
#include <windowsx.h>
#include <string>
#include <stdio.h>
#include <vector>
#include <ctime>

#define MAX_LOADSTRING 100
COLORREF COLOR = RGB(255, 255, 255);

float size = 1; //начальный размер
// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DZ, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DZ));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DZ));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DZ);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    float size = 1;

    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;

    case WM_KEYDOWN:
    {
        switch (wParam)
        {

        case VK_UP: {
            PAINTSTRUCT ps;
            //StopDrawing(hWnd);
            size += 0.5; //увеличение размера
            RECT Window;
            HDC hdc = GetDC(hWnd);
            GetWindowRect(hWnd, &Window);
            FillRect(hdc, &Window, CreateSolidBrush(COLOR));
            //InvalidateRect(hWnd, &Window, FALSE);

            BeginPaint(hWnd, &ps);
            MoveToEx(hdc, 0, 400, NULL);

            LineTo(hdc, 0, 400);
            LineTo(hdc, 10000, 400);

            MoveToEx(hdc, 600, 0, NULL);

            LineTo(hdc, 600, 0);
            LineTo(hdc, 600, 10000);

            TextOut(hdc, 610, 410, _T("0"), 1);
            for (size_t i = 1; i <= 10; i += 1) {
                WCHAR Coord[5];
                wsprintf(Coord, TEXT("-%d"), i);
                TextOut(hdc, 620, 400 + size * 40 * i, Coord, 3);
                TextOut(hdc, 600 - size * 40 * i, 410, Coord, 3);
                wsprintf(Coord, TEXT("%d"), i);
                TextOut(hdc, 600 + size * 40 * i, 410, Coord, 3);
                TextOut(hdc, 620, 400 - size * 40 * i, Coord, 3);
            }
            for (float x = -size * 10; x < size * 10; x += size * 0.01) {
                float y = size * (pow(log10f(fabs(1 / sin(x))), cos(x)) * sin(x));
                if (x == -size * 10)
                    MoveToEx(hdc, 30 * size * x + 600, -40 * size * y + 400, NULL);
                else
                    LineTo(hdc, 30 * size * x + 600, -40 * size * y + 400);
            }

            EndPaint(hWnd, &ps);

            //StartDrawing(hWnd);
        }
                  return 0;
        case VK_DOWN: {
            PAINTSTRUCT ps;
            //StopDrawing(hWnd);
            size -= 0.5; //увеличение размера
            RECT Window;
            HDC hdc = GetDC(hWnd);
            GetWindowRect(hWnd, &Window);
            FillRect(hdc, &Window, CreateSolidBrush(COLOR));
            //InvalidateRect(hWnd, &Window, FALSE);

            BeginPaint(hWnd, &ps);
            MoveToEx(hdc, 0, 400, NULL);

            LineTo(hdc, 0, 400);
            LineTo(hdc, 10000, 400);

            MoveToEx(hdc, 600, 0, NULL);

            LineTo(hdc, 600, 0);
            LineTo(hdc, 600, 10000);

            TextOut(hdc, 610, 410, _T("0"), 1);
            for (size_t i = 1; i <= 10; i += 1) {
                WCHAR Coord[5];
                wsprintf(Coord, TEXT("-%d"), i);
                TextOut(hdc, 620, 400 + size * 30 * i, Coord, 3);
                TextOut(hdc, 600 - size * 30 * i, 410, Coord, 3);
                wsprintf(Coord, TEXT("%d"), i);
                TextOut(hdc, 600 + size * 30 * i, 410, Coord, 3);
                TextOut(hdc, 620, 400 - size * 30 * i, Coord, 3);
            }
            for (float x = -size * 10; x < size * 10; x += size * 0.01) {
                float y = size * (pow(log10f(fabs(1 / sin(x))), cos(x)) * sin(x));
                if (x == -size * 10)
                    MoveToEx(hdc, 30 * size * x + 500, -40 * size * y + 400, NULL);
                else
                    LineTo(hdc, 30 * x + 600, -40 * y + 400);
            }

            EndPaint(hWnd, &ps);
            //StartDrawing(hWnd);
        }
                    return 0;
        }
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        MoveToEx(hdc, 0, 400, NULL);

        LineTo(hdc, 0, 400);
        LineTo(hdc, 10000, 400);

        MoveToEx(hdc, 600, 0, NULL);

        LineTo(hdc, 600, 0);
        LineTo(hdc, 600, 10000);

        TextOut(hdc, 610, 410, _T("0"), 1);
        for (size_t i = 1; i <= 10; i += 1) {
            WCHAR Coord[5];
            wsprintf(Coord, TEXT("-%d"), i);
            TextOut(hdc, 620, 400 + 30 * i, Coord, 3);
            TextOut(hdc, 600 - 30 * i, 410, Coord, 3);
            wsprintf(Coord, TEXT("%d"), i);
            TextOut(hdc, 600 + 30 * i, 410, Coord, 3);
            TextOut(hdc, 620, 400 - 30 * i, Coord, 3);
        }
        for (float x = -10; x < 10; x += 0.01) {
            float y = size * (pow(log10f(fabs(1 / sin(x))), cos(x)) * sin(x));
            if (x == -10)
                MoveToEx(hdc, 30 * x + 600, -40 * y + 400, NULL);
            else
                LineTo(hdc, 30 * x + 600, -40 * y + 400);
        }

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
