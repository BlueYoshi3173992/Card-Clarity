#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>

#include "logger.h"
#include "cards.h"

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
	Card* cardA = testGetCard(0);
	Card* cardB = testGetCard(1);
	Card* cardC = testGetCard(2);
	Card* cardD = testGetCard(3);
	Card* cardE = testGetCard(4);

	HWND cardABase = CreateWindowEx(
		0,
		L"STATIC",
		getGUIDAsLPCWSTR(cardA->guid),
		WS_CHILD | WS_VISIBLE | SS_CENTER | WS_EX_LEFT,
		20, 10, 350, 100,
		hwnd,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	HWND cardAMultipliers = CreateWindowEx(
		0,
		L"STATIC",
		getMultiplierInfo(*cardA),
		WS_CHILD | WS_VISIBLE | WS_EX_LEFT,
		390, 30, 220, 80,
		hwnd,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	HWND cardAInfo = CreateWindowEx(
		0,
		L"STATIC",
		getBaseInfo(*cardA),
		WS_CHILD | WS_VISIBLE | WS_EX_LEFT,
		5, 16, 350, 80,
		cardABase,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	HWND cardBBase = CreateWindowEx(
		0,
		L"STATIC",
		getGUIDAsLPCWSTR(cardB->guid),
		WS_CHILD | WS_VISIBLE | SS_CENTER | WS_EX_LEFT,
		20, 120, 350, 100,
		hwnd,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);


	HWND cardBInfo = CreateWindowEx(
		0,
		L"STATIC",
		getBaseInfo(*cardB),
		WS_CHILD | WS_VISIBLE | WS_EX_LEFT,
		5, 16, 350, 80,
		cardBBase,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	HWND cardBMultipliers = CreateWindowEx(
		0,
		L"STATIC",
		getMultiplierInfo(*cardB),
		WS_CHILD | WS_VISIBLE | WS_EX_LEFT,
		390, 140, 220, 80,
		hwnd,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	HWND cardCBase = CreateWindowEx(
		0,
		L"STATIC",
		getGUIDAsLPCWSTR(cardC->guid),
		WS_CHILD | WS_VISIBLE | SS_CENTER | WS_EX_LEFT,
		20, 230, 350, 100,
		hwnd,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	HWND cardCMultipliers = CreateWindowEx(
		0,
		L"STATIC",
		getMultiplierInfo(*cardC),
		WS_CHILD | WS_VISIBLE | WS_EX_LEFT,
		390, 250, 220, 80,
		hwnd,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	HWND cardCInfo = CreateWindowEx(
		0,
		L"STATIC",
		getBaseInfo(*cardC),
		WS_CHILD | WS_VISIBLE | WS_EX_LEFT,
		5, 16, 350, 80,
		cardCBase,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	HWND cardDBase = CreateWindowEx(
		0,
		L"STATIC",
		getGUIDAsLPCWSTR(cardD->guid),
		WS_CHILD | WS_VISIBLE | SS_CENTER | WS_EX_LEFT,
		20, 340, 350, 100,
		hwnd,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	HWND cardDMultipliers = CreateWindowEx(
		0,
		L"STATIC",
		getMultiplierInfo(*cardD),
		WS_CHILD | WS_VISIBLE | WS_EX_LEFT,
		390, 360, 220, 80,
		hwnd,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	HWND cardDInfo = CreateWindowEx(
		0,
		L"STATIC",
		getBaseInfo(*cardD),
		WS_CHILD | WS_VISIBLE | WS_EX_LEFT,
		5, 16, 350, 80,
		cardDBase,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	HWND cardEBase = CreateWindowEx(
		0,
		L"STATIC",
		getGUIDAsLPCWSTR(cardE->guid),
		WS_CHILD | WS_VISIBLE | SS_CENTER | WS_EX_LEFT,
		20, 450, 350, 100,
		hwnd,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	HWND cardEMultipliers = CreateWindowEx(
		0,
		L"STATIC",
		getMultiplierInfo(*cardE),
		WS_CHILD | WS_VISIBLE | WS_EX_LEFT,
		390, 470, 220, 80,
		hwnd,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);


	HWND cardEInfo = CreateWindowEx(
		0,
		L"STATIC",
		getBaseInfo(*cardE),
		WS_CHILD | WS_VISIBLE | WS_EX_LEFT,
		5, 16, 350, 80,
		cardEBase,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	logMessage("Finished loading window UI.", LOG_INFO);
}

void onWindowCreate(HWND hwnd) {
	loadWindowWidgets(hwnd);
	logMessage("Window UI initialization complete.", LOG_INFO);
}

void onWindowResize(HWND hwnd, int width, int height) {
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
	initTestCards();

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