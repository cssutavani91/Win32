//Headers
#include<Windows.h>

//Macros
#define MyTimer 101

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
	HBRUSH hBrush = NULL;
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc,rcTemp;
	//TCHAR Str[255] = TEXT("Hello World !!!");*/
	static int iPaintFlag = 0;
	switch (iMsg)
	{
	case WM_CREATE:
		SetTimer(hwnd, MyTimer, 2000, NULL);
		//MessageBox(hwnd, TEXT("WM_CREATE message is sent"), TEXT("Message"), MB_OK);
		break;

	case WM_TIMER:
		KillTimer(hwnd, MyTimer);
		iPaintFlag++;
		if (iPaintFlag > 8)
			iPaintFlag = 1;
		InvalidateRect(hwnd, NULL, FALSE);
		SetTimer(hwnd, MyTimer, 2000, NULL);
		break;

		/*case WM_MOVE:
			MessageBox(hwnd, TEXT("WM_MOVE message is sent"), TEXT("Message"), MB_OK);
			break;

		case WM_SIZE:
			MessageBox(hwnd, TEXT("WM_SIZE message is sent"), TEXT("Message"), MB_OK);
			break;

		case WM_KEYDOWN:
			MessageBox(hwnd, TEXT("WM_KEYDOWN message is sent"), TEXT("Message"), MB_OK);
			break;

	case WM_CHAR:
		switch (LOWORD(wParam))
		{
		case 'r':
		case 'R':
			iPaintFlag = 1;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case 'g':
		case 'G':
			iPaintFlag = 2;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case 'b':
		case 'B':
			iPaintFlag = 3;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case 'c':
		case 'C':
			iPaintFlag = 4;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case 'm':
		case 'M':
			iPaintFlag = 5;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case 'y':
		case 'Y':
			iPaintFlag = 6;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case 'k':
		case 'K':
			iPaintFlag = 7;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		case 'w':
		case 'W':
		default:
			iPaintFlag = 8;
			InvalidateRect(hwnd, NULL, FALSE);
		}
		break;*/

	case WM_PAINT:
		//Get changing rectangle
		GetClientRect(hwnd, &rc);
		//Call the specialist i.e Create HDC
		hdc = BeginPaint(hwnd, &ps);
		switch (iPaintFlag)
		{
		case 1:
			rcTemp.top = rc.top;
			rcTemp.bottom = rc.bottom;
			rcTemp.left = rc.left;
			rcTemp.right = rc.right / 8;
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
			break;
		case 2:
			rcTemp.top = rc.top;
			rcTemp.bottom = rc.bottom;
			rcTemp.left = rc.right / 8;
			rcTemp.right = rc.right / 4;
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
			break;
		case 3:
			rcTemp.top = rc.top;
			rcTemp.bottom = rc.bottom;
			rcTemp.left = rc.right / 4;
			rcTemp.right = (rc.right / 8) * 3;
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
			break;
		case 4:
			rcTemp.top = rc.top;
			rcTemp.bottom = rc.bottom;
			rcTemp.left = (rc.right / 8) * 3;
			rcTemp.right = rc.right / 2;
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
			break;
		case 5:
			rcTemp.top = rc.top;
			rcTemp.bottom = rc.bottom;
			rcTemp.left = rc.right / 2;
			rcTemp.right = (rc.right / 8) * 5;
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
			break;
		case 6:
			rcTemp.top = rc.top;
			rcTemp.bottom = rc.bottom;
			rcTemp.left = (rc.right / 8) * 5;
			rcTemp.right = (rc.right / 8) * 6;
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
			break;
		case 7:
			rcTemp.top = rc.top;
			rcTemp.bottom = rc.bottom;
			rcTemp.left = (rc.right / 8) * 6;
			rcTemp.right = (rc.right / 8) * 7;
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
			break;
		case 8:
			rcTemp.top = rc.top;
			rcTemp.bottom = rc.bottom;
			rcTemp.left = (rc.right / 8) * 7;
			rcTemp.right = rc.right;
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
			break;
		}

		//Send back the specialist and stop painting
		EndPaint(hwnd, &ps);
		DeleteObject(hBrush);
		break;

		/*case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_ESCAPE:
				DestroyWindow(hwnd);
				break;
			}
			break;*/

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
