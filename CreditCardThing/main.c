#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>

#include "logger.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define WINDOW_COLOR 0xCFCFCF

COLORREF hexToRGB(INT32 hex) {
	return RGB((hex >> 16) & 0xFF, (hex >> 8) & 0xFF, hex & 0xFF);
}

typedef struct {
	int xOffset;
	float xScale;
	int yOffset;
	float yScale;
} UDim2;

typedef struct {
	HWND hwnd;
	UDim2 position;
	UDim2 size;
} WindowWidget;

WindowWidget testWidget = { 0 };

void alignWidget(WindowWidget widget, int width, int height) {
	bool moveSuccess = SetWindowPos(
		widget.hwnd,
		HWND_TOP,
		widget.position.xOffset + (int)(widget.position.xScale * width),
		widget.position.yOffset + (int)(widget.position.yScale * height),
		widget.size.xOffset + (int)(widget.size.xScale * width),
		widget.size.yOffset + (int)(widget.size.yScale * height),
		SWP_DRAWFRAME
	);

	if (!moveSuccess) {
		logMessage("Failed to align widget.", LOG_ERROR);
	}
}

void loadWindowWidgets(HWND hwnd) {
	HWND widget = CreateWindowExW(
		WS_EX_WINDOWEDGE,
		L"EDIT",
		L"Test",
		WS_CHILD | WS_VISIBLE | ES_LEFT,
		0, 0, 0, 0,
		hwnd,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);
	testWidget.hwnd = widget;
	testWidget.position = (UDim2){ 0, 0.2f, 0, 0.3f };
	testWidget.size = (UDim2){ 0, 0.6f, 0, 0.4f };
	alignWidget(testWidget, WINDOW_WIDTH, WINDOW_HEIGHT);

	logMessage("Finished loading window UI.", LOG_INFO);
}

void onWindowCreate(HWND hwnd) {
	loadWindowWidgets(hwnd);
	logMessage("Window UI initialization complete.", LOG_INFO);
}

void onWindowResize(HWND hwnd, int width, int height) {
	alignWidget(testWidget, width, height);

	InvalidateRect(hwnd, NULL, TRUE);
	UpdateWindow(hwnd);

	return;
}

LRESULT CALLBACK applicationWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CREATE:;
		onWindowCreate(hwnd);
		return 0;
	case WM_SIZE:;
		int width = LOWORD(lParam);
		int height = HIWORD(lParam);
		onWindowResize(hwnd, width, height);
		return 0;
	case WM_PAINT:;
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		HBRUSH brush = CreateSolidBrush(hexToRGB(WINDOW_COLOR));
		FillRect(hdc, &ps.rcPaint, brush);
		DeleteObject(brush);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:;
		PostQuitMessage(0);
		return 0;
	default:;
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

int main(void) {
	initLogger();

	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = applicationWindowProc;
	wc.lpszClassName = L"Credit Card Thing";
	wc.hInstance = GetModuleHandle(NULL);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClassW(&wc);

	HWND hwnd = CreateWindowW(
		wc.lpszClassName,
		L"CardClarity",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		NULL,
		NULL,
		wc.hInstance,
		NULL
	);

	if (!hwnd) {
		logMessage("Failed to start application.", LOG_ERROR);
		return 1;
	}
	else {
		logMessage("Application started successfully.", LOG_INFO);
	}

	ShowWindow(hwnd, SW_SHOW);
	
	while (true) {
		MSG msg = { 0 };
		if (GetMessage(&msg, NULL, 0, 0) <= 0) {
			break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	logMessage("Application closed successfully.", LOG_INFO);

	return 0;
}