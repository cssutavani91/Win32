//header
#include<Windows.h>

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
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	const int StrMax = 255;
	TCHAR Str[StrMax] = TEXT("PLEDGE");
	TCHAR Str2[StrMax] = TEXT("India is my country. All Indians are my brothers and sisters.");
	TCHAR Str3[StrMax] = TEXT("I love my country and I am proud of its rich and varied heritage.");
	TCHAR Str4[StrMax] = TEXT("I shall strive to be worthy of it.");
	TCHAR Str5[StrMax] = TEXT("I shall respect my parents, teachers and all elders, and treat everyone with courtsey.");
	TCHAR Str6[StrMax] = TEXT("To my country and all my people, I plegde my devotion.");
	TCHAR Str7[StrMax] = TEXT("In their well being and prosperity alone lies my happiness.");
	TCHAR Str8[StrMax] = TEXT("JAI HIND.");
	switch (iMsg)
	{
	case WM_PAINT:
		//Get changing rectangle
		GetClientRect(hwnd, &rc);
		//Call the specialist i.e Create HDC
		hdc = BeginPaint(hwnd, &ps);
		//Set the text colour
		SetTextColor(hdc, RGB(2555, 125, 0));
		//Set Background Color
		SetBkColor(hdc, RGB(0, 0, 0));
		//Draw the actual text
		TextOut(hdc, rc.right/2, 5, Str, StrMax);
		TextOut(hdc, 5, 50, Str2, StrMax);
		TextOut(hdc, 5, 75, Str3, StrMax);
		SetTextColor(hdc, RGB(255, 255, 255));
		TextOut(hdc, 5, 100, Str4, StrMax);
		TextOut(hdc, 5, 125, Str5, StrMax);
		SetTextColor(hdc, RGB(0, 255, 0));
		TextOut(hdc, 5, 150, Str6, StrMax);
		TextOut(hdc, 5, 175, Str7, StrMax);
		TextOut(hdc, rc.right/2, 200, Str8, StrMax);
		//DrawText(hdc, Str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
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
