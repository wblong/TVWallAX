// TVWallAX.cpp : CTVWallAXApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "TVWallAX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CTVWallAXApp theApp;

const GUID CDECL _tlid = { 0xB03F7467, 0xA270, 0x461D, { 0x95, 0x7D, 0x50, 0x39, 0x2D, 0xB5, 0x2C, 0xFA } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;

LRESULT CALLBACK CTVWallAXApp::GetMessageProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	LPMSG lpMsg = (LPMSG)lParam;

	if (AfxGetApp()->PreTranslateMessage(lpMsg))
	{
		lpMsg->message = WM_NULL;
		lpMsg->lParam = 0L;
		lpMsg->wParam = 0;
	}

	// Passes the hook information to the next hook procedure in  
	// the current hook chain.  
	return ::CallNextHookEx(theApp.m_hHook, nCode, wParam, lParam);
}



// CTVWallAXApp::InitInstance - DLL 初始化

BOOL CTVWallAXApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO:  在此添加您自己的模块初始化代码。
		m_hHook = ::SetWindowsHookEx(
			WH_GETMESSAGE,
			GetMessageProc,
			AfxGetInstanceHandle(),
			GetCurrentThreadId());

		return CWinApp::InitInstance();
	}

	return bInit;
}



// CTVWallAXApp::ExitInstance - DLL 终止

int CTVWallAXApp::ExitInstance()
{
	// TODO:  在此添加您自己的模块终止代码。
	UnhookWindowsHookEx((HHOOK)m_hHook);
	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
