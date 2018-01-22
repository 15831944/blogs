// SDK ����ṹ
#include <Windows.h>
#include <stdio.h>

// ��������
LRESULT CALLBACK MyWindowProc(
	HWND	hwnd,
	UINT	uMsg,
	WPARAM	wParam,
	LPARAM	lParam
	);

// �������
int WINAPI WinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR		lpCmdline,
	int			nCmdShow
	)
{
	LPCWSTR	myWndClsasName = TEXT("MyWndClassName");
	LPCWSTR	myWindowName = TEXT("MyWindowName");

	// ��Ʋ�ע�ᴰ����
	WNDCLASS	wndcls;
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndcls.hCursor = LoadCursor(NULL, IDC_CROSS);
	wndcls.hIcon = LoadIcon(NULL, IDI_ERROR);
	wndcls.hInstance = hInstance;
	wndcls.lpfnWndProc = MyWindowProc;
	wndcls.lpszClassName = myWndClsasName;
	wndcls.lpszMenuName = NULL;
	wndcls.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndcls);

	// ������ʾ���´���
	HWND hwnd;
	hwnd = CreateWindow(myWndClsasName, myWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 600, 400, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);

	// ��Ϣѭ��
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

// ���ڹ��̺���
LRESULT CALLBACK MyWindowProc(
	HWND	hwnd,
	UINT	uMsg,
	WPARAM	wParam,
	LPARAM	lParam
	)
{
	switch (uMsg)
	{
	case WM_CHAR:
		char szChar[20];
		sprintf(szChar, "Input Char is %c", wParam);
		MessageBoxA(hwnd, szChar, "���°���", MB_OK);
		break;
	case WM_LBUTTONDOWN:
		MessageBoxA(hwnd, "Mouse Clicked", "������", MB_OK);
		HDC hdc;
		hdc = GetDC(hwnd);
		TextOut(hdc, 0, 50, TEXT("AAA"), 3);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_PAINT:
		HDC hdc2;
		PAINTSTRUCT ps;
		hdc2 = BeginPaint(hwnd, &ps);
		TextOut(hdc2, 0, 50, TEXT("BBB"), 3);
		EndPaint(hwnd, &ps);
		break;
	case WM_CLOSE:
		if (IDYES == MessageBoxA(hwnd, "Close Window", "�رմ���", MB_YESNO))
		{
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}