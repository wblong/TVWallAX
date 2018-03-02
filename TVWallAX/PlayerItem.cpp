// PlayerItem.cpp : 实现文件
//

#include "stdafx.h"
#include "TVWallAX.h"
#include "PlayerItem.h"


// CPlayerItem

IMPLEMENT_DYNAMIC(CPlayerItem, CWnd)

CPlayerItem::CPlayerItem()
{

}

CPlayerItem::~CPlayerItem()
{
}


BEGIN_MESSAGE_MAP(CPlayerItem, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CPlayerItem 消息处理程序




BOOL CPlayerItem::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	rcWindow.OffsetRect(-rcWindow.TopLeft());
	pDC->FillSolidRect(&rcWindow,RGB(120,120,120));
	return true;
	//return CWnd::OnEraseBkgnd(pDC);
}


void CPlayerItem::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
}


void CPlayerItem::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	//::SendMessage(GetParent()->m_hWnd, WM_LBUTTONDOWN, 0, 0);
	CWnd::OnLButtonDown(nFlags, point);
}


BOOL CPlayerItem::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_LBUTTONDOWN){
		
		::SendMessage(GetParent()->m_hWnd, WM_LBUTTONDOWN, 0, 0);
	}
	if (pMsg->message == WM_LBUTTONDBLCLK){
		
		::SendMessage(GetParent()->m_hWnd,WM_LBUTTONDBLCLK,0,0);
	}
	return CWnd::PreTranslateMessage(pMsg);
}
