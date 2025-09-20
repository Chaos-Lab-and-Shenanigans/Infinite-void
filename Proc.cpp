#include "Proc.h"
#include "resource.h"
#include <stdio.h>

State* s = NULL;
INT_PTR CALLBACK DlgProc2(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
void InitComboBox(HWND);

INT_PTR CALLBACK DlgProc1(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {


    switch (msg) {
    case WM_INITDIALOG:
        s = (State*)lParam;
        InitComboBox(hDlg);

        return (INT_PTR)TRUE;

    case WM_CLOSE:
        DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc1, (LPARAM)s);
        return (INT_PTR)TRUE;


    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDCANCEL:
            DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc1, (LPARAM)s);
            break;

        case IDSEEFUTURE:
            WCHAR check1[150];
            WCHAR check2[150];

            GetDlgItemText(hDlg, IDC_EDIT1, check1, 150);
            GetDlgItemText(hDlg, IDC_EDIT1, check2, 150);
            
            if (lstrlen(check1) == 0 || lstrlen(check2) == 0) {
                MessageBox(hDlg, L"Fill the fucking fields peasant 🙂", L"Error", MB_OK);
                return (INT_PTR)TRUE;
            }
            DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_DIALOG2), NULL, DlgProc2, (LPARAM)s);

            return (INT_PTR)TRUE;
        }
        return (INT_PTR)TRUE;

    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK DlgProc2(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {

     case WM_INITDIALOG: {
        s = (State*)lParam;
        UINT index = s->index % s->max_ind;
        SetDlgItemText(hDlg, (IDC_STATIC1), s->Arr[index]);
        s->index++;

        return (INT_PTR)TRUE;
    }

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDOK:
        case IDCLOSE:
            DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_DIALOG2), NULL, DlgProc2, (LPARAM)s);
            break;
        }
        return (INT_PTR)TRUE;

    case WM_CLOSE:
        DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_DIALOG2), NULL, DlgProc2, (LPARAM)s);
        return (INT_PTR)TRUE;
    }
    return (INT_PTR)FALSE;
}

void InitComboBox(HWND hDlg) {
    HWND hCombo = GetDlgItem(hDlg, IDC_COMBO1);
    SendMessage(hCombo, CB_ADDSTRING, NULL, (LPARAM)L"January");
    SendMessage(hCombo, CB_ADDSTRING, NULL, (LPARAM)L"February");
    SendMessage(hCombo, CB_ADDSTRING, NULL, (LPARAM)L"April");
    SendMessage(hCombo, CB_ADDSTRING, NULL, (LPARAM)L"May");
    SendMessage(hCombo, CB_ADDSTRING, NULL, (LPARAM)L"June");
    SendMessage(hCombo, CB_ADDSTRING, NULL, (LPARAM)L"July");
    SendMessage(hCombo, CB_ADDSTRING, NULL, (LPARAM)L"August");
    SendMessage(hCombo, CB_ADDSTRING, NULL, (LPARAM)L"September");
    SendMessage(hCombo, CB_ADDSTRING, NULL, (LPARAM)L"October");
    SendMessage(hCombo, CB_ADDSTRING, NULL, (LPARAM)L"November");
    SendMessage(hCombo, CB_ADDSTRING, NULL, (LPARAM)L"December");

    SendMessage(hCombo, CB_SETCURSEL, 4, 0);     //Default January selected, have no idea why its at 4 
}
