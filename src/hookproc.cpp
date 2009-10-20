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

/// @brief ���̃E�B���h�E�v���V�[�W��
static LONG prevWndProc = 0;
/// @brief �T�u�N���X�������E�B���h�E�̃E�B���h�E�n���h��
HWND hookhwnd = 0;

/// ���X�̃^�C�g��������
static char winText[1024] = "";

/// �w�b�_������
static char headerText[1024] = "";

/// Windows�ɓn���o�b�t�@
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
 * @brief �E�B���h�E�̃T�u�N���X��
 * @param hMainWnd �T�u�N���X������E�B���h�E�̃E�B���h�E�n���h��
 *
 * �w�肳�ꂽ�E�B���h�E���T�u�N���X������B
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
 * @brief �T�u�N���X�E�B���h�E���b�Z�[�W�n���h��
 * @param hwnd �E�B���h�E�̃n���h��
 * @param uMsg ���b�Z�[�W
 * @param wParam ���b�Z�[�W�̒ǉ����1
 * @param lParam ���b�Z�[�W�̒ǉ����2
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
