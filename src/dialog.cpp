/*
 * $Id: dialog.cpp,v 1.1.1.1 2005/05/27 09:44:26 woods Exp $
 * dialog.cpp : ダイアログ用のプロシージャ定義
 */

static char id[] = "$Id: dialog.cpp,v 1.1.1.1 2005/05/27 09:44:26 woods Exp $";

#include <stdio.h>
#include "resource.h"
#include "dialog.h"
#include "bktbhdr.h"

// グローバル変数:

/// 現在のインスタンス
static HINSTANCE hInstance;

/// 設定ダイアログの表示ヘッダ設定文字列バッファ
static char *setstr;
/// 設定ダイアログの表示ヘッダ設定文字列バッファの大きさ
static int setsize;
/// ウィンドウ自動調整有無
static int adjustwindow;

// このコード モジュールに含まれる関数の前宣言:
extern "C" {
static LRESULT CALLBACK About(HWND, UINT, WPARAM, LPARAM);
static LRESULT CALLBACK Setting(HWND, UINT, WPARAM, LPARAM);
}

/**
 * @brief 設定ダイアログ表示関数
 * @param hInst ダイアログが含まれるインスタンスのハンドル
 * @param hWnd 親ウィンドウのウィンドウハンドル
 * @param str 表示するヘッダ文字列の初期値(カンマ区切り)
 * @param size strバッファの大きさ
 * @param adjust ウィンドウサイズ自動調節フラグ
 *
 * 設定ダイアログを表示する。
 */
int DoSetting(HINSTANCE hInst, HWND hWnd, char *str, int size, UINT *adjust)
{
    setstr = str;
    setsize = size;
    hInstance = hInst;
    ::DialogBox(hInst, (LPCTSTR) IDD_SETTING, hWnd, (DLGPROC) Setting);

    return 0;
}

/**
 * @brief Aboutダイアログ表示関数
 * @param hInst ダイアログが含まれるインスタンスのハンドル
 * @param hWnd 親ウィンドウのウィンドウハンドル
 *
 * Aboutダイアログを表示する。
 */
int DoAbout(HINSTANCE hInst, HWND hWnd)
{
    ::DialogBox(hInst, (LPCTSTR) IDD_ABOUTBOX, hWnd, (DLGPROC) About);
    return 0;
}

/**
 * @brief 設定ダイアログ用メッセージ ハンドラ
 * @param hDlg : ウィンドウハンドル
 * @param message : メッセージ
 * @param wParam : メッセージのパラメータ
 * @param lParam : メッセージのパラメータ
 *
 * 設定ダイアログのウィンドウメッセージを処理する。
 */
static LRESULT CALLBACK
Setting(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UINT length;
    UINT chk;

    switch (message) {
    case WM_INITDIALOG:
        chk = (adjustwindow != 0) ? BST_CHECKED : BST_UNCHECKED;
        ::SetDlgItemText(hDlg, IDC_HEADERS, setstr);
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDOK:
            length =
                ::GetDlgItemText(hDlg, IDC_HEADERS, setstr, setsize);
            ::EndDialog(hDlg, LOWORD(wParam));
            return TRUE;
            break;
        case IDCANCEL:
            ::EndDialog(hDlg, LOWORD(wParam));
            return TRUE;
            break;
        case IDC_ABOUT:
            DoAbout(hInstance, hDlg);
            break;
        }
        break;
    default:
        break;
    }
    return FALSE;
}


/**
 * @brief Aboutダイアログメッセージ ハンドラ
 * @param hDlg : ウィンドウハンドル
 * @param message : メッセージ
 * @param wParam : メッセージのパラメータ
 * @param lParam : メッセージのパラメータ
 *
 * Aboutダイアログのウィンドウメッセージを処理する。
 */
static LRESULT CALLBACK
About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_INITDIALOG:
        return TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
            ::EndDialog(hDlg, LOWORD(wParam));
            return TRUE;
        }
        break;
    }
    return FALSE;
}
