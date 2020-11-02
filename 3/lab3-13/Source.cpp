#include "include.h"

#define CONTACT_LIST 1001
#define CURRENT_NAME 1002
#define CURRENT_PHONE 1003
#define HANG_BTN 1004
#define CALL_BTN 1005
#define ONE_BTN 1006
#define TWO_BTN 1007
#define THREE_BTN 1008
#define FOUR_BTN 1009
#define FIVE_BTN 1010
#define SIX_BTN 1011
#define SEVEN_BTN 1012
#define EIGHT_BTN 1013
#define NINE_BTN 1014
#define ZERO_BTN 1015
#define CLEAR_BTN 1016
#define CREATE_BTN 1017
#define IN_NUMBER 1018
#define PLUS_BTN 1019
#define CALL_INS_BTN 1020
#define HANG_INS_BTN 1021
#define EXIT_BTN 1023

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR digitsTitle[] = _T("Digits");

static TCHAR szTitle[] = _T("�������");

HINSTANCE hInst;
HINSTANCE digits;
WNDCLASSEX newFrame;

HWND hContactList;
HWND hCurrentName;
HWND hCurrentPhone;
HWND hHangBtn;
HWND hWnd;
HWND hPutNumber;
HWND hInsertDigits;
HWND hOne;
HWND hTwo;
HWND hThree;
HWND hFour;
HWND hFive;
HWND hSix;
HWND hSeven;
HWND hEight;
HWND hNine;
HWND hZero;
HWND hClear;
HWND hEdit;
HWND hCallIns;
HWND hHangIns;  
HWND hExit;

wchar_t phone[13];
wchar_t name[64];
wchar_t outTime[6];

int callSec = 0;
int callMin = 0;
int sec1 = callSec % 10;
int sec2 = callSec / 10;
int min1 = callMin % 10;
int min2 = callMin / 10;

bool isCall = false;
bool isHang = false;
bool isName = false;
bool isPhone = false;

TCHAR callInfo[] = _T("�������");
TCHAR callBegin[] = _T("�������� . . .");
TCHAR callEnd[] = _T("�����");
TCHAR ChildName[] = _T("������-�������");

HDC hdc;
PAINTSTRUCT ps;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    WNDCLASS wch;
    // ����������� ������ ����
    wch.hInstance = hInstance;
    wch.lpszClassName = ChildName;
    wch.lpfnWndProc = ChildProc;
    wch.style = CS_HREDRAW | CS_VREDRAW;
    wch.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wch.hCursor = LoadCursor(NULL, IDC_ARROW);
    wch.lpszMenuName = NULL;
    wch.cbClsExtra = 0;
    wch.cbWndExtra = 0;
    wch.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    if (!RegisterClass(&wch)) return 0;

    if (!RegisterClassEx(&wcex)) // ���� �� ������� ������� ����� ����
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    hInst = hInstance;

    hWnd = CreateWindow(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 500,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd) // ���� �� ������� ������� ����������
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);

   

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        if (isCall) // ���� ������
        {
            TextOut(hdc,
                5, 5,
                callBegin, _tcslen(callBegin));
            TextOut(hdc,
                100, 5,
                outTime, _tcslen(outTime));
        }

        if (isHang) // ���� �������� ������
        {
            TextOut(hdc,
                5, 5,
                callEnd, _tcslen(callEnd));
            TextOut(hdc,
                100, 5,
                outTime, _tcslen(outTime));
            isHang = false;
        }


        EndPaint(hWnd, &ps);
        break;

    case WM_CREATE:

        hContactList = CreateWindow( // �������� ������ ���������
            _T("listbox"),
            NULL,
            WS_CHILD | WS_VISIBLE | LBS_STANDARD |
            LBS_NOTIFY,
            10,
            100,
            300,
            300,
            hWnd,
            (HMENU)CONTACT_LIST,
            hInst,
            NULL);
        // ������� ������� � ������� � ���������� ���������
        SendMessage(hContactList, LB_ADDSTRING, 0,
            (LPARAM)(LPSTR)L"+79154545354 ��������");
        SendMessage(hContactList, LB_ADDSTRING, 0,
            (LPARAM)(LPSTR)L"+79154545666 ��������");
        SendMessage(hContactList, LB_ADDSTRING, 0,
            (LPARAM)(LPSTR)L"+78005553535 �������");

        // �������� ��������� ����� � ��������� � ��� ��������
        hCurrentName = CreateWindow(L"edit", L"��� ��������", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
            10, 40, 200, 20, hWnd, (HMENU)CURRENT_NAME, hInst, 0);
        hCurrentPhone = CreateWindow(L"edit", L"�������", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
            10, 70, 200, 20, hWnd, (HMENU)CURRENT_PHONE, hInst, 0);

        // �������� ������ ������ � ������ ������
        hHangBtn = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"�����",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            310,         // x position 
            40,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)HANG_BTN,
            hInst,
            NULL);      // Pointer not needed.

        hHangBtn = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"���������",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            220,         // x position 
            40,         // y position 
            80,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)CALL_BTN,
            hInst,
            NULL);      // Pointer not needed.

        hPutNumber = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"�������� �����",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            10,         // x position 
            1,         // y position 
            200,        // Button width
            30,        // Button height
            hWnd,     // Parent window
            (HMENU)CREATE_BTN,
            hInst,
            NULL);      // Pointer not needed.
        break;

     case WM_COMMAND:
        if (HIWORD(wParam) == LBN_SELCHANGE || HIWORD(wParam) == LBN_DBLCLK) // ������� �� �������� � ������
        {
            unsigned uSelectedItem; // ����� ��������� ������

            uSelectedItem = (int)SendMessage(hContactList, // ���������� ������ ���������� ������
                LB_GETCURSEL, 0, 0L);

            if (uSelectedItem != LB_ERR) // ���� ������ ���������� ����� ��������� ������
            {
                wchar_t buffer[256];
                SendMessage(hContactList, LB_GETTEXT, // ����������� ������ � ��������� ������ � �������� buffer
                    uSelectedItem, (LPARAM)buffer);

                // ������ ������ �� ���������� ������ � ����� �� bufer �������������
                phone[12] = '\0';
                for (size_t i = 0; i < 12; i++)
                {
                    phone[i] = buffer[i];
                }
                size_t i = 13;
                while (buffer[i] != L'\0')
                {
                    name[i - 13] = buffer[i];
                    i++;
                }
                name[i-1] = '\0';
                // ����� ����������

                isPhone = true;
                isName = true;
                // ��������� ������ ����� �����
                SendMessage(hCurrentName, WM_SETTEXT, NULL, (LPARAM)name);
                SendMessage(hCurrentPhone, WM_SETTEXT, NULL, (LPARAM)phone);
                // ���������� ����� �����
                UpdateWindow(hCurrentName);
                UpdateWindow(hCurrentPhone);

            }
        }

        if (wParam == CALL_BTN) // ������ ����������
        {
            if (isName && isPhone) // ���� ������ �������
            {
                isCall = true;
                isHang = false;
                InvalidateRect(hWnd, NULL, TRUE); // ����������� ����
                SetTimer(hWnd, 1, 1000, NULL); // ��������� �������, ������ ������ �������
            }
            else MessageBox(hWnd,L"�������� ��������!", L"������!", NULL); // ���� ������� �� ������
        }

        if (wParam == HANG_BTN) // ������ ������
        {
            if (isName && isPhone) // ���� ������ ��������
            {
                isHang = true;
                isCall = false;
                InvalidateRect(hWnd, NULL, TRUE); // ����������� ����
                KillTimer(hWnd, 1); // ��������� �������
                callSec = 0;
                callMin = 0;
            }
            else MessageBox(hWnd, L"�������� ��������!", L"������!", NULL); // ���� ������� �� ������
        }
 

        if (wParam == CREATE_BTN)
        {
            CreateWindow(ChildName, _T("����� ������"), WS_VISIBLE, 10, 10, 300, 400, hWnd, 0, hInst, 0);
        }

        break;

     case WM_TIMER: // ����� ������ ������
         callSec++; // ���-�� ������ + 1

         if (callSec == 60) // ��������� ����� �����
         {
             callSec = 0;
             callMin++;
         }

         sec1 = callSec % 10; // ���������� ��� �������� ������ �������
         sec2 = callSec / 10;
         min1 = callMin % 10;
         min2 = callMin / 10;

         swprintf(outTime, L"%i%i:%i%i\0", min2, min1, sec2, sec1); // ����� �������
         InvalidateRect(hWnd, NULL, TRUE);  // ����������� ����
         break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}
wchar_t *insertedNumber = new wchar_t[13];
size_t curPose = 0;
int callInsTime = 0;
wchar_t *outInsText = new wchar_t[6];

LRESULT CALLBACK ChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:

        hOne = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"1",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            10,         // x position 
            100,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)ONE_BTN,
            hInst,
            NULL);      // Pointer not needed.

        hTwo = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"2",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            60,         // x position 
            100,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)TWO_BTN,
            hInst,
            NULL);      // Pointer not needed.

        hThree = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"3",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            110,         // x position 
            100,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)THREE_BTN,
            hInst,
            NULL);      // Pointer not needed.

        hFour = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"4",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            10,         // x position 
            150,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)FOUR_BTN,
            hInst,
            NULL);      // Pointer not needed.

        hFive = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"5",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            60,         // x position 
            150,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)FIVE_BTN,
            hInst,
            NULL);      // Pointer not needed.

        hSix = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"6",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            110,         // x position 
            150,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)SIX_BTN,
            hInst,
            NULL);      // Pointer not needed.

        hSeven = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"7",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            10,         // x position 
            200,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)SEVEN_BTN,
            hInst,
            NULL);      // Pointer not needed.

        hEight = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"8",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            60,         // x position 
            200,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)EIGHT_BTN,
            hInst,
            NULL);      // Pointer not needed.

        hNine = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"9",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            110,         // x position 
            200,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)NINE_BTN,
            hInst,
            NULL);      // Pointer not needed.

        hZero = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"0",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            60,         // x position 
            250,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)ZERO_BTN,
            hInst,
            NULL);      // Pointer not needed.

        hClear = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"<-",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            110,         // x position 
            250,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)CLEAR_BTN,
            hInst,
            NULL);      // Pointer not needed.

        hClear = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"+",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            10,         // x position 
            250,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)PLUS_BTN,
            hInst,
            NULL);      // Pointer not needed.

        hClear = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"+",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            10,         // x position 
            250,         // y position 
            50,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)PLUS_BTN,
            hInst,
            NULL);      // Pointer not needed.

        hCallIns = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"���������",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            170,         // x position 
            100,         // y position 
            120,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)CALL_INS_BTN,
            hInst,
            NULL);      // Pointer not needed.

        hCallIns = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"��������",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            170,         // x position 
            170,         // y position 
            120,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)HANG_INS_BTN,
            hInst,
            NULL);      // Pointer not needed.

        hExit = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"�����",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            170,         // x position 
            300,         // y position 
            120,        // Button width
            50,        // Button height
            hWnd,     // Parent window
            (HMENU)EXIT_BTN,
            hInst,
            NULL);      // Pointer not needed.

        hEdit = CreateWindow(L"edit", L"������� �������", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
            10, 10, 200, 20, hWnd, (HMENU)IN_NUMBER, hInst, 0);

        SendMessage(hEdit, EM_SETREADONLY, TRUE, 0);

        break;

    case WM_COMMAND:
        insertedNumber[12] = L'\0';

        if (wParam == ONE_BTN)
        {
            if (curPose < 11)
            {
                insertedNumber[curPose] = L'1';
                insertedNumber[curPose + 1] = L'\0';
                curPose++;
                SendMessage(hEdit, WM_SETTEXT, NULL, (LPARAM)insertedNumber);
            }
            else MessageBox(hWnd, L"������ ������� ������� �����!", L"������!", NULL);
        }

        if (wParam == TWO_BTN)
        {
            if (curPose < 11)
            {
                insertedNumber[curPose] = L'2';
                insertedNumber[curPose + 1] = L'\0';
                curPose++;
                SendMessage(hEdit, WM_SETTEXT, NULL, (LPARAM)insertedNumber);
            }
            else MessageBox(hWnd, L"������ ������� ������� �����!", L"������!", NULL);
        }

        if (wParam == THREE_BTN)
        {
            if (curPose < 11)
            {
                insertedNumber[curPose] = L'3';
                insertedNumber[curPose + 1] = L'\0';
                curPose++;
                SendMessage(hEdit, WM_SETTEXT, NULL, (LPARAM)insertedNumber);
            }
            else MessageBox(hWnd, L"������ ������� ������� �����!", L"������!", NULL);
        }

        if (wParam == FOUR_BTN)
        {
            if (curPose < 11)
            {
                insertedNumber[curPose] = L'4';
                insertedNumber[curPose + 1] = L'\0';
                curPose++;
                SendMessage(hEdit, WM_SETTEXT, NULL, (LPARAM)insertedNumber);
            }
            else MessageBox(hWnd, L"������ ������� ������� �����!", L"������!", NULL);
        }

        if (wParam == FIVE_BTN)
        {
            if (curPose < 11)
            {
                insertedNumber[curPose] = L'5';
                insertedNumber[curPose + 1] = L'\0';
                curPose++;
                SendMessage(hEdit, WM_SETTEXT, NULL, (LPARAM)insertedNumber);
            }
            else MessageBox(hWnd, L"������ ������� ������� �����!", L"������!", NULL);
        }

        if (wParam == SIX_BTN)
        {
            if (curPose < 11)
            {
                insertedNumber[curPose] = L'6';
                insertedNumber[curPose + 1] = L'\0';
                curPose++;
                SendMessage(hEdit, WM_SETTEXT, NULL, (LPARAM)insertedNumber);
            }
            else MessageBox(hWnd, L"������ ������� ������� �����!", L"������!", NULL);
        }

        if (wParam == SEVEN_BTN)
        {
            if (curPose < 11)
            {
                insertedNumber[curPose] = L'7';
                insertedNumber[curPose + 1] = L'\0';
                curPose++;
                SendMessage(hEdit, WM_SETTEXT, NULL, (LPARAM)insertedNumber);
            }
            else MessageBox(hWnd, L"������ ������� ������� �����!", L"������!", NULL);
        }

        if (wParam == EIGHT_BTN)
        {
            if (curPose < 11)
            {
                insertedNumber[curPose] = L'8';
                insertedNumber[curPose + 1] = L'\0';
                curPose++;
                SendMessage(hEdit, WM_SETTEXT, NULL, (LPARAM)insertedNumber);
            }
            else MessageBox(hWnd, L"������ ������� ������� �����!", L"������!", NULL);
        }

        if (wParam == NINE_BTN)
        {
            if (curPose < 11)
            {
                insertedNumber[curPose] = L'9';
                insertedNumber[curPose + 1] = L'\0';
                curPose++;
                SendMessage(hEdit, WM_SETTEXT, NULL, (LPARAM)insertedNumber);
            }
            else MessageBox(hWnd, L"������ ������� ������� �����!", L"������!", NULL);
        }

        if (wParam == ZERO_BTN)
        {
            if (curPose < 11)
            {
                insertedNumber[curPose] = L'0';
                insertedNumber[curPose + 1] = L'\0';
                curPose++;
                SendMessage(hEdit, WM_SETTEXT, NULL, (LPARAM)insertedNumber);
            }
            else MessageBox(hWnd, L"������ ������� ������� �����!", L"������!", NULL);
        }

        if (wParam == PLUS_BTN)
        {
            if (curPose == 0)
            {
                insertedNumber[curPose] = L'+';
                insertedNumber[curPose + 1] = L'\0';
                curPose++;

                SendMessage(hEdit, WM_SETTEXT, NULL, (LPARAM)insertedNumber);
            }
            else MessageBox(hWnd, L"����� ����� ������ ���������� � \"+\"", L"������!", NULL);
        }

        if (wParam == CLEAR_BTN)
        {
            if (curPose > 0)
            {
                curPose--;
                insertedNumber[curPose] = L'\0';
                SendMessage(hEdit, WM_SETTEXT, NULL, (LPARAM)insertedNumber);
            }
        }

        if (wParam == CALL_INS_BTN)
        {
            if (curPose == 11)
            {
                isCall = true;
                wchar_t temp[] = L"��������. . .";
                SendMessage(hEdit, WM_SETTEXT, NULL, (LPARAM)temp);
                curPose = 0;
            }
            else MessageBox(hWnd, L"������ ������� �������� �����", L"������", NULL);
        }

        if (wParam == HANG_INS_BTN)
        {
            if (isCall)
            {
                isCall = false;
                wchar_t temp[] = L"�����";
                SendMessage(hEdit, WM_SETTEXT, NULL, (LPARAM)temp);
            }
        else MessageBox(hWnd, L"������� ���������", L"������", NULL);
        }

        if (wParam == EXIT_BTN)
        {
            SendMessage(hWnd, WM_CLOSE, 0, 0);
        }
        break;

            break;

    case WM_DESTROY: PostQuitMessage(0);
        break; // ���������� ���������
        // ��������� ��������� �� ���������
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}