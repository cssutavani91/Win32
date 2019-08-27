//headers
#include<Windows.h>
#include"MyMath.h"

#pragma comment (lib,"DllDef.lib")

//Global Function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR ipszCmdLine, int iCmdShow)
{
	//Variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppname[] = TEXT("MyApp");

	//Code
	//Initialization of WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppname;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//Register above class
	RegisterClassEx(&wndclass);

	//Create Window
	hwnd = CreateWindow(szAppname, TEXT("MyApplication"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//Message Loop
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
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	TCHAR Str[255] = TEXT("Hello World!!!");
	int num = 0, sqr = 0;
	TCHAR Str1[255];
	switch (iMsg)
	{
	case WM_CREATE:
		num = 10;
		sqr = MakeSquare(num);
		wsprintf(Str1, TEXT("The Square of %d is %d"), num, sqr);
		MessageBox(hwnd, Str1, TEXT("Message"), MB_OK);
		DestroyWindow(hwnd);
		break;

	case WM_PAINT:
		//Get changing rectangle
		GetClientRect(hwnd, &rc);
		//Call the specialist i.e Create HDC
		hdc = BeginPaint(hwnd, &ps);
		//Set the text colour
		SetTextColor(hdc, RGB(0, 255, 0));
		//Set Background Color
		SetBkColor(hdc, RGB(0, 0, 0));
		//Draw the actual text
		DrawText(hdc, Str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		//Send back the specialist and stop painting
		EndPaint(hwnd, &ps);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
