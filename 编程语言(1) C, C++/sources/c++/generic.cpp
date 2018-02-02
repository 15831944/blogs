#include <windows.h>
#include "resource.h"		// resource IDs
#include "generic.h"

HINSTANCE	_hInst;		// Instance handle
HWND			_hWnd;

char _szAppName[] = "Generic";						// 程序名称
char _szTitle[]   = "Generic Sample Application";	// 窗口标题

/*********************************
	WinMain windows 程序进入点
*********************************/
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	/* 避免编译时的警告 */
	UNREFERENCED_PARAMETER(lpCmdLine);
	
	/* 窗口类的注册, 只有该程序的第1个实例才会进入 */
	if (!hPreInstance)								// 其值由系统传入, win32系统中，其值永远为0, 因此每个实例都会进入
		if (!InitApplication(hInstance))
			return FALSE;
	
	/* 窗口的产生 */
	if (!InitInstance(hInstance, nCmdShow))
		return FALSE;
	
	/* 消息循环 */
	while (GetMessage(&msg, NULL, 0, 0))	// 具备多任务能力
	{
		TranslateMessage(&msg);		// 转换键盘消息
		DispatchMessage(&msg);		// 分派消息给窗口函数	
	}

	return (msg.wParam);			// 传回 PostQuitMessage 参数
}

/*********************************
	InitApplication 注册窗口类
*********************************/
BOOL InitApplication(HINSTANCE hInstance)
{
	/* 窗口类 */
	WNDCLASS wc;

	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = (WNDPROC)WndProc;					// 指定窗口函数(窗口接收到消息的行为)
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(hInstance, "jjhouricon");
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = GetSockObject(WHITE_BRUSH);			// 窗口后台颜色
	wc.lpszMenuName  = "GenericMenu";						// .RC 所定义的窗体
	wc.lpszClassName = _szAppName;

	return (RegisterClass(&wc));							// 设定窗口属性
}

/******************************
	InitInstance 产生窗口
		任何实例都会进入
		创建窗口
		显示窗口
		绘制窗口
******************************/
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	_hInst = hInstance;		// 全局变量
	_hWnd  = CreateWindow {				// 创建窗口
				_szAppName,
				_szTitle,
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				NULL,
				NULL,
				hInstance,
				NULL
	};

	if (!_hWnd)
		return FALSE;

	ShowWindow(_hWnd, nCmdShow);		// 显示窗口
	UpdateWindow(_hWnd);				// 送出 WM_PAINT 驱动窗口的绘图操作
	return TRUE;
}

/******************************
	WndProc 窗口函数
		被系统调用
******************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wnEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(_hInst, "AboutBox", hWnd, (DLGPROC)About);	//	对话框资源名称，父窗口，对话框函数名称
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return (DefWindowProc(hWnd, message, wParam, lParam));
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return (DefWindowProc(hWnd, message, wParam, lParam));	// 系统默认的消息处理函数
	}
	return 0;
}

/*************************
	About 对话框函数
*************************/
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCALCEL)
		{
			EndDialog(hDlg, TRUE);
			return TRUE;
		}
		break;
	}
	return FALSE;
}