/*
 * $Id: bktbhdr.h,v 1.1.1.1 2005/05/27 09:44:26 woods Exp $
 */

#ifndef BKHDPNL_H
#define BKHDPNL_H

#include <stdlib.h>

#include "PluginSDK/BeckyAPI.h"

/// @brief Becky! API�p�C���X�^���X
extern CBeckyAPI bka;

/// @brief DLL�̃C���X�^���X�n���h��
extern HINSTANCE g_hInstance;

/// @brief ini�t�@�C���̃p�X��
extern char szIni[_MAX_PATH+2]; // Ini file to save your plugin settings.

#endif /* BKHDPNL_H */