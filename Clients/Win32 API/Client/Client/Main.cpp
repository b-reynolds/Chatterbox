#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>


HINSTANCE ghInst;
const wchar_t* lpClassName = L"WinApp";

#define IDC_BUTTON1		101

HWND hWndTextbox;

// Main window callback function
LRESULT CALLBACK mainWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		CreateWindowA("button", "btn1", WS_CHILD | WS_VISIBLE,
			10, 10, 75, 25, hwnd, (HMENU)IDC_BUTTON1, ghInst, NULL);

		hWndTextbox = CreateWindowA("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE,
			10, 45, 200, 300, hwnd, NULL, ghInst, NULL);

		SetFocus(hWndTextbox);
		break;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wparam) == IDC_BUTTON1)
		{
			MessageBoxA(hwnd, "Hello", "World", MB_OK);
		}

		break;
	}
	case WM_CLOSE:
	{
		DestroyWindow(hwnd);
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return 0;
}

// Main entry point
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	ghInst = hInstance;

	WNDCLASSEX ex;

	ex.cbSize = sizeof(WNDCLASSEX);
	ex.cbClsExtra = 0;
	ex.cbWndExtra = 0;
	ex.hInstance = ghInst;
	ex.style = 0;
	ex.lpszMenuName = NULL;
	ex.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	ex.hCursor = LoadCursor(NULL, IDC_ARROW);
	ex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	ex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	ex.lpszClassName = lpClassName;
	ex.style = NULL;
	ex.lpfnWndProc = mainWndProc;

	RegisterClassEx(&ex);

	HWND hwnd = CreateWindowEx(NULL, lpClassName, L"Windows Application",
		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		200, 200, 500, 500, NULL, NULL, ghInst, NULL);

	ShowWindow(hwnd, nShowCmd);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}