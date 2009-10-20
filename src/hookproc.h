/*
 * $Id: hookproc.h,v 1.1.1.1 2005/05/27 09:44:26 woods Exp $
 */

#ifndef HOOKPROC_H
#define HOOKPROC_H

void setTitleString(char *str, size_t sz);
void redrawTitle(void);
void hookMailWindow(HWND hMainWnd);

#endif /* HOOKPROC_H */
