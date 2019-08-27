//Headers
#include<Windows.h>
#include"MyMath1.h"

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
	HINSTANCE hDll;
	typedef int(*makeSquareFn)(int);
	makeSquareFn pfn = NULL;
	int i=25, j;
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	TCHAR Str[255] = TEXT("Hello World !!!");
	//int num = 0, sqr = 0;
	TCHAR Str1[255];
	switch (iMsg)
	{
	case WM_CREATE:
		hDll = LoadLibrary(TEXT("MyMath1.dll"));
		if (hDll == NULL)
			MessageBox(hwnd, TEXT("The Library is not loaded"), TEXT("Message"), MB_OK);
		pfn = (makeSquareFn)GetProcAddress(hDll, "MakeSquare");
		if(pfn==NULL)
			MessageBox(hwnd, TEXT("Function not found"), TEXT("Message"), MB_OK);
		j = pfn(i);
		//num = 10;
		wsprintf(Str1, TEXT("num= %d"), i);
		MessageBox(hwnd, Str1, TEXT("Message"), MB_OK);
		wsprintf(Str1, TEXT("The square of %d is %d"), i, j);
		MessageBox(hwnd, Str1, TEXT("Message"), MB_OK);
		FreeLibrary(hDll);
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
