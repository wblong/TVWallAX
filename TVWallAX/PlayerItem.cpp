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
