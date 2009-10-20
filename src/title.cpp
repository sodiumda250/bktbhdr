/* $Id: title.cpp,v 1.1.1.1 2005/05/27 09:44:26 woods Exp $ */

static char id[] = "$Id: title.cpp,v 1.1.1.1 2005/05/27 09:44:26 woods Exp $";

#include <stdio.h>
#include <windows.h>

#include "bktbhdr.h"
#include "hookproc.h"

/// 表示ヘッダ名リスト
static char headerbuf[1024];
static char *headerList[512];
static int ListSize = 0;

void InitHeader(const char *szIni)
{
    int len;
    int i, j;

    len = ::GetPrivateProfileString("BkTbHdr", "HeaderList", "X-Mailer",
                          headerbuf, sizeof(headerbuf) - 1, szIni);
    for (i = 0; i < len; i++) {
        for (j = i;
             (j < len) && (headerbuf[j] != ',') && (headerbuf[j] != '\r') && (headerbuf[j] != '\n');
             j++) { /* do nothing */ }
        headerbuf[j] = 0;
        headerList[ListSize++] = headerbuf + i;
        i = j;
    }
}

void ShowHeader(LPCTSTR lpMailID)
{
    int i;
    char buf[1024];
    char str[1024];

    buf[0] = 0;
    if (lpMailID != NULL && lpMailID[0] != 0) {
        for (i = 0; i < ListSize; i++) {
            bka.GetSpecifiedHeader(headerList[i], buf, sizeof(buf) - 1);
            buf[sizeof(buf) - 1] = 0;
            if (buf[0] != 0) {
                break;
            }
        }
    } else {
        buf[0] = 0;
    }

    if (buf[0] != 0) {
        sprintf(str, " %s: %s", headerList[i], buf);
    } else {
        str[0] = 0;
    }

    setTitleString(str, strlen(str) + 1);
}
