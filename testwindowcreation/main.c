#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <math.h>

#include "window.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800


int x = 0;
int y = 0;

void drawCardBackground(HDC hdc) {	
	HBRUSH fillBrushA = CreateSolidBrush(RGB(180, 180, 180));

	HBRUSH fillBrushB = CreateSolidBrush(RGB(255, 0, 0));

	RECT bgRect = { 60, 20, 400, 740 };
	FillRect(hdc, &bgRect, fillBrushA);

	HGDIOBJ oldBrush = SelectObject(hdc, fillBrushB);

	Ellipse(hdc, x + 25, y + 25, x - 25, y - 25);

	DeleteObject(fillBrushA);
	DeleteObject(fillBrushB);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_PAINT: {
		PAINTSTRUCT ps = { 0 };
		HDC hdc = BeginPaint(hwnd, &ps);

		HBRUSH bgBrush = CreateSolidBrush(RGB(230, 230, 230));
		FillRect(hdc, &ps.rcPaint, bgBrush);

		drawCardBackground(hdc);

		DeleteObject(bgBrush);
		EndPaint(hwnd, &ps);
		return 0;
	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		return 0;
	}
	case WM_KEYDOWN: {
		switch (wParam) {
		case (VK_LEFT):
			x -= 10;
			break;
		case (VK_RIGHT):
			x += 10;
			break;
		case (VK_UP):
			y -= 10;
			break;
		case (VK_DOWN):
			y += 10;
			break;
		}

		InvalidateRect(hwnd, NULL, TRUE);
		return 0;
	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int main(void) {
	Window window = createWindow(
		L"cool window",
		WindowProc,
		WS_OVERLAPPEDWINDOW,
		NULL,
		NULL,
		L"My Window",
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WINDOW_WIDTH,
		WINDOW_HEIGHT
	);

	ShowWindow(window.hwnd, SW_SHOWDEFAULT);

	MSG msg = {0};
	while (GetMessageW(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return 0;
}