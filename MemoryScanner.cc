#include <windows.h>
#include "Scanner.h"

#define ID_BTN 1
#define ID_QUIT 2
#define ID_CLOSE 3

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
	MSG msg;
	WNDCLASSW wc = { 0 };

	Scanner scanner;

	wc.lpszClassName = L"Buttons";
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&wc);
	CreateWindowW(wc.lpszClassName, L"Buttons", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		650, 650, 800, 600, 0, 0, hInstance, &scanner);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		case WM_CREATE: {
			CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)cs->lpCreateParams);

			CreateWindowW(
				L"BUTTON",
				L"Open Notepad",
				WS_VISIBLE | WS_CHILD,
				20, 20, 100, 40,
				hwnd,
				(HMENU)ID_BTN,
				NULL,
				NULL
			);


			CreateWindowW(
				L"BUTTON",
				L"Close",
				WS_VISIBLE | WS_CHILD,
				190, 20, 50, 40,
				hwnd,
				(HMENU)ID_CLOSE,
				NULL,
				NULL
			);

			CreateWindowW(
				L"BUTTON",
				L"QUIT",
				WS_VISIBLE | WS_CHILD,
				400, 20, 100, 40,
				hwnd,
				(HMENU)ID_QUIT,
				NULL,
				NULL
			);

			break;
		}


		case WM_COMMAND: {
			Scanner* scanner = (Scanner*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			if (LOWORD(wParam) == ID_BTN) {
				scanner->loadNotepad();
			}
			else if (LOWORD(wParam) == ID_CLOSE) {
				scanner->closeProcess();
			}
			else if (LOWORD(wParam) == ID_QUIT) {
				//scanner->closeProcess();
				DestroyWindow(hwnd);
				PostQuitMessage(0);
				break;
			}
			break;
		}

		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}

	}

	return DefWindowProc(hwnd, msg, wParam, lParam);

}