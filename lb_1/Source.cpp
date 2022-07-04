#include <windows.h>
#include "resource.h"

//GLobal
HINSTANCE hInst; //����������
HWND hWnd;
LPCTSTR szWindowClass = "QWERTY";
LPCTSTR szTitle = "Zyablitsev Kelchevskiy";

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char buff[50];

//�������� ���������
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;

    MyRegisterClass(hInstance); //����������� ������ ����

    //�������� ���������
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }
    //���� ��������� ���������
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
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS | CS_NOCLOSE; //����� ����
    wcex.lpfnWndProc = (WNDPROC)WndProc; // ������� ���������
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance; //����������
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION); //������
    wcex.hCursor = LoadCursor(NULL, IDC_HELP); // ������
    wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);//���
    wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);//����
    wcex.lpszClassName = szWindowClass;//��� ������
    wcex.hIconSm = NULL;

    return RegisterClassEx(&wcex);//����������� ������ ����
}

//������� ���� � ��������� ����������
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; //����������
    hWnd = CreateWindow(szWindowClass,//��� ������ ����
        szTitle,//���
        WS_CAPTION | WS_BORDER | WS_SYSMENU | WS_MINIMIZEBOX,//�����
        0,//����������
        0,   
        500,//������
        200,
        NULL,  //���������� ���� ��������
        NULL,//���������� ����
        hInstance,//���������� ���������
        NULL);//��������� ��������

    if (!hWnd)
    {
        return FALSE;
    }
    ShowWindow(hWnd, SW_SHOWMINIMIZED); //����� ����
    UpdateWindow(hWnd);//����������� ����
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
//������� ���������. ������������ ���������
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rt;

    switch (message)
    {
    case WM_CREATE: // ��������
        break;

    case WM_PAINT://����������� 
        hdc = BeginPaint(hWnd, &ps); //��������� ����
        GetClientRect(hWnd, &rt);//������� ����
        DrawText(hdc, "�����, ���!", -1, &rt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        EndPaint(hWnd, &ps); //����� ���� �����
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_LBUTTONDBLCLK: //2���
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

    default: // ��������� ���������, ������� �� ����������� �������������
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
