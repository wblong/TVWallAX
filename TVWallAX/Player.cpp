// Player.cpp : 实现文件
//

#include "stdafx.h"
#include "TVWallAX.h"
#include "Player.h"


// CPlayer

IMPLEMENT_DYNAMIC(CPlayer, CWnd)

CPlayer::CPlayer()
{
	//RegisterWindowClass();
}

CPlayer::~CPlayer()
{
}


BEGIN_MESSAGE_MAP(CPlayer, CWnd)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CPlayer 消息处理程序




BOOL CPlayer::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CRect rt;
	GetClientRect(rt);
	pDC->FillSolidRect(rt, RGB(0, 0,0));
	//pDC->TextOut(10,10,_T("Test"));
	DrawEdge(pDC);
	return true;
}



// 绘制边
void CPlayer::DrawEdge(CDC* dc)
{
	CRect rcWindow;
	CRect rcTemp;
	GetWindowRect(&rcWindow);
	rcWindow.OffsetRect(-rcWindow.TopLeft());
	rcTemp = rcWindow;
	//
	CPen penEdge(PS_SOLID, 1, RGB(255, 255, 0));
	CPen* cpTemp;
	cpTemp = dc->SelectObject(&penEdge);
	rcTemp.DeflateRect(1, 1);
   	dc->Draw3dRect(rcTemp, RGB(255, 255, 0), RGB(255, 255, 0));
	dc->SelectObject(cpTemp);
	
}
//BOOL CPlayer::RegisterWindowClass(HINSTANCE hInstance)
//{
//	LPCWSTR className = L"CPlayer";//"CMyWin"控件类的名字   
//	WNDCLASS windowclass;
//
//	if (hInstance)
//		hInstance = AfxGetInstanceHandle();
//
//	if (!(::GetClassInfo(hInstance, className, &windowclass)))
//	{
//		windowclass.style = CS_DBLCLKS;
//		windowclass.lpfnWndProc = ::DefWindowProc;
//		windowclass.cbClsExtra = windowclass.cbWndExtra = 0;
//		windowclass.hInstance = hInstance;
//		windowclass.hIcon = NULL;
//		windowclass.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
//		windowclass.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
//			windowclass.lpszMenuName = NULL;
//		windowclass.lpszClassName = className;
//
//		if (!AfxRegisterClass(&windowclass))
//		{
//			AfxThrowResourceException();
//			return FALSE;
//		}
//	}
//
//	return TRUE;
//}