//Headers
#include<Windows.h>

//Thread Declaration
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);

//Global Function Declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Winmain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR ipszCmdLine, int iCmdShow)
{
	// Varible Declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	//Code
	//Initialization of WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//register above class
	RegisterClassEx(&wndclass);

	//Create Window
	hwnd = CreateWindow(szAppName, TEXT("My Application"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//Message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//code
	HANDLE hThreadOne = NULL;
	HANDLE hThreadTwo = NULL;
	switch (iMsg)
	{
	case WM_CREATE:
		hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID)hwnd, 0, NULL);
		hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0, NULL);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("Left Mouse Button is clicked"), TEXT("Message"), MB_OK);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProcOne(LPVOID param)
{
	HDC hdc;
	long int i;
	TCHAR Str[255];
	hdc = GetDC((HWND)param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 0));
	for (i = 0; i < 4294967295; i++)
	{
		wsprintf(Str, TEXT("ThreadOne->Increasing:%ld"), i);
		TextOut(hdc, 5, 5, Str, wcslen(Str));
		//TextOut(hdc, 5, 5, Str, lstrlen(Str));
	}
	ReleaseDC((HWND)param, hdc);
	return (0);
}

DWORD WINAPI ThreadProcTwo(LPVOID param)
{
	HDC hdc;
	long int i;
	TCHAR Str1[255];
	hdc = GetDC((HWND)param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 0));
	//MessageBox(HWND(param), TEXT("This is 2"), TEXT("Msg"), MB_OK);
	for (i = 429496729; i > 0 ; i--)
	{
		wsprintf(Str1, TEXT("ThreadTwo->Decreasing:%ld"), i);
		TextOut(hdc, 5, 25, Str1, wcslen(Str1));
		//TextOut(hdc, 5, 5, Str, lstrlen(Str));
	}
	//MessageBox(HWND(param), TEXT("For loop is closed"), TEXT("Msg"), MB_OK);
	ReleaseDC((HWND)param, hdc);
	return (0);
}
