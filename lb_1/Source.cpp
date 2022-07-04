#include <windows.h>
#include "resource.h"

//GLobal
HINSTANCE hInst; //дескриптор
HWND hWnd;
LPCTSTR szWindowClass = "QWERTY";
LPCTSTR szTitle = "Zyablitsev Kelchevskiy";

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char buff[50];

//Основная программа
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;

    MyRegisterClass(hInstance); //регистрация класса окна

    //создание программы
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }
    //цикл обработки сообщений
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS | CS_NOCLOSE; //стиль окна
    wcex.lpfnWndProc = (WNDPROC)WndProc; // оконная процедура
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance; //дескриптор
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION); //иконка
    wcex.hCursor = LoadCursor(NULL, IDC_HELP); // курсор
    wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);//фон
    wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);//меню
    wcex.lpszClassName = szWindowClass;//имя класса
    wcex.hIconSm = NULL;

    return RegisterClassEx(&wcex);//регистрация класса окна
}

//создает окно и сохраняет дескриптор
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; //дескриптор
    hWnd = CreateWindow(szWindowClass,//имя класса окна
        szTitle,//имя
        WS_CAPTION | WS_BORDER | WS_SYSMENU | WS_MINIMIZEBOX,//стиль
        0,//координаты
        0,   
        500,//размер
        200,
        NULL,  //дескриптор окна родителя
        NULL,//дескриптор меню
        hInstance,//дескриптор программы
        NULL);//параметры создания

    if (!hWnd)
    {
        return FALSE;
    }
    ShowWindow(hWnd, SW_SHOWMINIMIZED); //показ окна
    UpdateWindow(hWnd);//обновлдение окна
    return TRUE;
}

int CALLBACK Close(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_CLOSE:
            PostQuitMessage(0);
            EndDialog(hDlg, LOWORD(wParam));
            break;
        case ID_CANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            break;
        }

        break;
    }

    return FALSE;
}

int CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_OK:
            EndDialog(hDlg, LOWORD(wParam));
            break;
        case ID_CLOSE:
            EndDialog(hDlg, LOWORD(wParam));
            break;
        case ID_MORE:
            MessageBox(hWnd, "Zyablitsev \nKelchevckiy", "KIUKIu-21-1", MB_OK);
            break;
        }

        break;
    }

    return FALSE;
}
//оконная процедура. обрабатывает сообщения
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rt;

    switch (message)
    {
    case WM_CREATE: // создание
        break;

    case WM_PAINT://перерисовка 
        hdc = BeginPaint(hWnd, &ps); //графичный ввод
        GetClientRect(hWnd, &rt);//область окна
        DrawText(hdc, "Привіт, світ!", -1, &rt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        EndPaint(hWnd, &ps); //конец граф ввода
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_LBUTTONDBLCLK: //2лкм
        MessageBox(hWnd, "Zyablitsev Kelchevckiy", "KIUKiu-21-1", MB_OK);
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_CHAGNE_SIZE:
            SetWindowPos(hWnd, NULL, 150, 150, 300, 300, SWP_SHOWWINDOW);
            break;

        case ID_CHAGNE_BACKGROUND:
            SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)GetStockObject(WHITE_BRUSH));
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        
        case ID_CHAGNE_CAPTION:
            LoadString(hInst, IDS_STRING102, buff, 50);
            SetWindowText(hWnd, buff);
            break;

        case ID_ABOUT_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, About);
            break;
        }

        break;
    case WM_CLOSE:
        DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, Close);
        break;

    default: // оброботка сообщений, которые не обработанны пользователем
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
