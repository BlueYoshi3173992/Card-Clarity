#pragma once

#include <stdio.h>
#include <windows.h>
#include "window.h"

HINSTANCE getHInstance() {
	return GetModuleHandle(NULL);
}

Window createWindow(LPCWSTR classname, LRESULT (*proc)(HWND, UINT, WPARAM, LPARAM), DWORD style, HWND parent, HMENU hMenu, LPCWSTR title, int x, int y, int width, int height) {
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = proc;
	wc.lpszClassName = classname;
	wc.hInstance = getHInstance();

	RegisterClass(&wc);

	HWND hwnd = CreateWindowExW(
		0,
		classname,
		title,
		style,
		x,
		y,
		width,
		height,
		parent,
		hMenu,
		getHInstance(),
		NULL
	);

	Window window = {0};
	window.hwnd = hwnd;
	window.hMenu = hMenu;
	return window;
}