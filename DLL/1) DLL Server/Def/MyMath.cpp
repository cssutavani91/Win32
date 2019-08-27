#include<Windows.h>

//extern "C" BOOL IsNoNegative(int);

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

extern "C" int MakeSquare(int num)
{
	/*HWND hwnd;
//	int i;
	TCHAR Str[255];
	//i = IsNoNegative(num);
	if (i == FALSE)
	{
		wsprintf(Str, TEXT("The Number is negative"));
		MessageBox(hwnd, Str, TEXT("Message"), MB_OK);*/
	return (num*num);
}

/*extern "C" BOOL IsNoNegative(int num)
{
	if (num < 0)
		return TRUE;
	else
		return FALSE;
}*/
