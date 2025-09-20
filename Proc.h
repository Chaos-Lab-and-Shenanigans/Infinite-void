#pragma once
#include <Windows.h>

struct State {
	UINT index;
	CONST WCHAR** Arr;
	UINT max_ind;
} ;

INT_PTR CALLBACK DlgProc1(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
