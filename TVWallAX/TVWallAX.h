#pragma once

// TVWallAX.h : TVWallAX.DLL 的主头文件

#if !defined( __AFXCTL_H__ )
#error "在包括此文件之前包括“afxctl.h”"
#endif

#include "resource.h"       // 主符号


// CTVWallAXApp : 有关实现的信息，请参阅 TVWallAX.cpp。

class CTVWallAXApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
	static LRESULT CALLBACK GetMessageProc(int nCode, WPARAM wParam, LPARAM lParam);
	HHOOK m_hHook;
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

