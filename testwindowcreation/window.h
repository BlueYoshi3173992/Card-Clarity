#pragma once

#include <windows.h>

#ifndef WINDOW_H
#define WINDOW_H

typedef struct {
	HWND hwnd;
	HMENU hMenu;
} Window;

Window createWindow(LPCWSTR classname, LRESULT(*proc)(HWND, UINT, WPARAM, LPARAM), DWORD style, HWND parent, HMENU hMenu, LPCWSTR title, int x, int y, int width, int height);

HINSTANCE getHInstance();

#endif
