// TVWallAX.cpp : CTVWallAXApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "comcat.h"
#include "strsafe.h"
#include "objsafe.h"
#include "TVWallAX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CTVWallAXApp theApp;

const GUID CDECL _tlid = { 0xB03F7467, 0xA270, 0x461D, { 0x95, 0x7D, 0x50, 0x39, 0x2D, 0xB5, 0x2C, 0xFA } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;
// CLSID_SafeItem - Necessary for safe ActiveX control
// Id taken from IMPLEMENT_OLECREATE_EX function in xxxCtrl.cpp

const CATID CLSID_SafeItem =
{ 0xC639E623, 0xF7C2, 0x445E, { 0xB8, 0x89, 0x9D, 0x72, 0xB4, 0x67, 0xD4, 0xF4 } };
//0xc639e623, 0xf7c2, 0x445e, 0xb8, 0x89, 0x9d, 0x72, 0xb4, 0x67, 0xd4, 0xf4
//0x0FC6093A, 0x2AAF, 0x4B50, { 0xA5, 0x33, 0x1A, 0x66, 0x18, 0x4E, 0x1C, 0x25 }
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

//HRESULT CreateComponentCategory - Used to register ActiveX control as safe

HRESULT CreateComponentCategory(CATID catid, WCHAR *catDescription)
{
	ICatRegister *pcr = NULL;
	HRESULT hr = S_OK;

	hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr,
		NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);
	if (FAILED(hr))
		return hr;

	// Make sure the HKCR\Component Categories\{..catid...}
	// key is registered.
	CATEGORYINFO catinfo;
	catinfo.catid = catid;
	catinfo.lcid = 0x0409; // english
	size_t len;
	// Make sure the provided description is not too long.
	// Only copy the first 127 characters if it is.
	// The second parameter of StringCchLength is the maximum
	// number of characters that may be read into catDescription.
	// There must be room for a NULL-terminator. The third parameter
	// contains the number of characters excluding the NULL-terminator.
	hr = StringCchLengthW(catDescription, STRSAFE_MAX_CCH, &len);
	if (SUCCEEDED(hr))
	{
		if (len>127)
		{
			len = 127;
		}
	}
	else
	{
		// TODO: Write an error handler;
	}
	// The second parameter of StringCchCopy is 128 because you need 
	// room for a NULL-terminator.    
	hr = StringCchCopyW(catinfo.szDescription, len + 1,
		catDescription);
	// Make sure the description is null terminated.
	catinfo.szDescription[len + 1] = '\0';

	hr = pcr->RegisterCategories(1, &catinfo);
	pcr->Release();

	return hr;
}
// HRESULT RegisterCLSIDInCategory - Register your component categories information

HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid)
{
	// Register your component categories information.
	ICatRegister *pcr = NULL;
	HRESULT hr = S_OK;
	hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr,
		NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);
	if (SUCCEEDED(hr))
	{
		// Register this category as being "implemented" by the class.
		CATID rgcatid[1];
		rgcatid[0] = catid;
		hr = pcr->RegisterClassImplCategories(clsid, 1, rgcatid);
	}

	if (pcr != NULL)
		pcr->Release();

	return hr;
}
// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);
#if 1
	// Mark the control as safe for initializing.
	HRESULT hr = CreateComponentCategory(CATID_SafeForInitializing, L"Controls safely initializable from persistent data!");
	if (FAILED(hr))
		return hr;

	hr = RegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForInitializing);
	if (FAILED(hr))
		return hr;

	// Mark the control as safe for scripting.
	hr = CreateComponentCategory(CATID_SafeForScripting, L"Controls safely scriptable!");
	if (FAILED(hr))
		return hr;

	hr = RegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForScripting);
	if (FAILED(hr))
		return hr;
#endif
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
