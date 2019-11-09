
#include<windows.h>
#include"ClassFactoryDllServerWithRegFile.h"

//Global Function Declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Winmain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Variable Declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[] = TEXT("ComClient");
	HRESULT hr;

	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM Library Cannot be initialized.\nProgram will now exit"), TEXT("Program Error"), MB_OK);
		exit(0);
	}

	//WNDCLASSEX initialization
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//Register Windowclass
	RegisterClassEx(&wndclass);

	//Create Window
	hwnd = CreateWindow(AppName, TEXT("Client Of COM DLL Server"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//Message Loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//COM Uninitialization
	CoUninitialize();
	return((int)msg.wParam);
}

//Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wparam, LPARAM lparam)
{
	//Function Declartion
	//void SafeInterfaceRelease(void);

	//Variable Declaration
	HRESULT hr;
	ISum *pISum = NULL;
	ISubtract *pISubtract = NULL;
	int iNum1, iNum2, iSum;
	TCHAR str[255];

	//Code
	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISum Interface Cannot be Obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		iNum1 = 55;
		iNum2 = 45;

		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);

		wsprintf(str, TEXT("Sum of %d and %d = %d"), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		hr = pISum->QueryInterface(IID_ISubtract, (void **)&pISubtract);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISubtract interface cannot be obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		pISum->Release();
		pISum = NULL;

		iNum1 = 155;
		iNum2 = 145;

		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iSum);

		pISubtract->Release();
		pISubtract = NULL;
		
		wsprintf(str, TEXT("Subtraction Of %d from %d = %d"), iNum2, iNum1, iSum);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wparam, lparam));
}

