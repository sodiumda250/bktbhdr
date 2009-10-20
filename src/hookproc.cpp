/*
 * $Id: hookproc.cpp,v 1.2 2005/05/30 00:53:24 woods Exp $
 */

static char id[] = "$Id: hookproc.cpp,v 1.2 2005/05/30 00:53:24 woods Exp $";

#include <stdio.h>
#include <windows.h>
#include "hookproc.h"

extern "C" {
static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}

/// @brief 元のウィンドウプロシージャ
static LONG prevWndProc = 0;
/// @brief サブクラス化したウィンドウのウィンドウハンドル
HWND hookhwnd = 0;

/// 元々のタイトル文字列
static char winText[1024] = "";

/// ヘッダ文字列
static char headerText[1024] = "";

/// Windowsに渡すバッファ
static char buf[1024] = "";

void redrawTitle(void)
{
    if (hookhwnd) {
        ::SetWindowText(hookhwnd, winText);
    }
}

void setTitleString(char *str, size_t sz)
{
    if (sz >= sizeof(headerText)) {
        sz = sizeof(headerText) - 1;
    }

    memcpy(headerText, str, sz);
    headerText[sz] = 0;

    redrawTitle();
}

/**
 * @brief ウィンドウのサブクラス化
 * @param hMainWnd サブクラス化するウィンドウのウィンドウハンドル
 *
 * 指定されたウィンドウをサブクラス化する。
 */
void hookMailWindow(HWND hMainWnd)
{
    ::GetWindowText(hMainWnd, winText, sizeof(winText));

    prevWndProc = ::SetWindowLong(hMainWnd, GWL_WNDPROC, (LONG)WindowProc);
    if (prevWndProc != 0) {
        hookhwnd = hMainWnd;
    } else {
        hookhwnd = 0;
    }
}

/**
 * @brief サブクラスウィンドウメッセージハンドラ
 * @param hwnd ウィンドウのハンドル
 * @param uMsg メッセージ
 * @param wParam メッセージの追加情報1
 * @param lParam メッセージの追加情報2
 */
static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (hwnd != hookhwnd) {
        return ::CallWindowProc((WNDPROC)prevWndProc, hwnd, uMsg, wParam, lParam);
    }
    switch (uMsg) {
    case WM_GETTEXT:
        // do not hook
        break;
    case WM_SETTEXT:
        strncpy(winText, (char *)lParam, sizeof(winText) - 1);
        winText[sizeof(winText) - 1] = 0;
        _snprintf(buf, sizeof(buf), "%s %s", winText, headerText);
        lParam = (LPARAM)buf;
        break;
    default:
        break;
    }
    return ::CallWindowProc((WNDPROC)prevWndProc, hwnd, uMsg, wParam, lParam);
}
