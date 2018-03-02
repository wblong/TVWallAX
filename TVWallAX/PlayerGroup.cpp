// PlayerGroup.cpp : 实现文件
//

#include "stdafx.h"
#include "TVWallAX.h"
#include "PlayerGroup.h"
// CPlayerGroup

IMPLEMENT_DYNAMIC(CPlayerGroup, CWnd)

CPlayerGroup::CPlayerGroup()
{
	m_nCount = 16;
	m_nplayWindowCount = 16;

}

CPlayerGroup::~CPlayerGroup()
{

}


BEGIN_MESSAGE_MAP(CPlayerGroup, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()



// CPlayerGroup 消息处理程序



//子控件的布局
void CPlayerGroup::RecalWndPos()
{
	CRect rcWindow;
	GetClientRect(rcWindow);

	int nWidth;
	int nHeight;
	int nPos;
	//清空所有CRect,并初始化原始状态
	for (nPos = 0; nPos < m_nplayWindowCount; nPos++){

		m_rcWnd[nPos] = CRect(0, 0, 0, 0);
		m_player[nPos].rcWnd = CRect(0, 0, 0, 0);
		m_player[nPos].SetSelected(false);
		m_player[nPos].SetMaxSizeStatus(false);
	}
	//得到最大化CRect
	m_rcWndMax = rcWindow;
	//计算各个显示数量时的CRect

	if (m_nCount == 1)
	{
		rcWindow.InflateRect(0, 0, 0, 0);
		m_rcWnd[0] = rcWindow;
	}

	else if (m_nCount == 4)
	{

		nWidth = rcWindow.Width() / 2;
		nHeight = rcWindow.Height() / 2;
		m_rcWnd[0] = CRect(0, 0, nWidth, nHeight);
		m_rcWnd[1] = CRect(nWidth, 0, rcWindow.Width(), nHeight);
		m_rcWnd[2] = CRect(0, nHeight, nWidth, rcWindow.Height());
		m_rcWnd[3] = CRect(nWidth, nHeight, rcWindow.Width(), rcWindow.Height());

	}
	else if (m_nCount == 6)

	{

		nWidth = rcWindow.Width() / 3;
		nHeight = rcWindow.Height() / 3;

		m_rcWnd[0] = CRect(0, 0, nWidth * 2, nHeight * 2);

		m_rcWnd[1] = CRect(nWidth * 2, 0, rcWindow.Width(), nHeight);

		m_rcWnd[2] = CRect(nWidth * 2, nHeight, rcWindow.Width(), nHeight * 2);

		m_rcWnd[3] = CRect(nWidth * 2, nHeight * 2, rcWindow.Width(), rcWindow.Height());

		m_rcWnd[4] = CRect(0, nHeight * 2, nWidth, rcWindow.Height());

		m_rcWnd[5] = CRect(nWidth, nHeight * 2, nWidth * 2, rcWindow.Height());

	}

	else if (m_nCount == 8)

	{

		nWidth = rcWindow.Width() / 4;
		nHeight = rcWindow.Height() / 4;
		m_rcWnd[0] = CRect(0, 0, nWidth * 3, nHeight * 3);

		m_rcWnd[1] = CRect(nWidth * 3, 0, rcWindow.Width(), nHeight);

		m_rcWnd[2] = CRect(nWidth * 3, nHeight, rcWindow.Width(), nHeight * 2);

		m_rcWnd[3] = CRect(nWidth * 3, nHeight * 2, rcWindow.Width(), nHeight * 3);

		m_rcWnd[4] = CRect(nWidth * 3, nHeight * 3, rcWindow.Width(), rcWindow.Height());

		m_rcWnd[5] = CRect(0, nHeight * 3, nWidth, rcWindow.Height());

		m_rcWnd[6] = CRect(nWidth, nHeight * 3, nWidth * 2, rcWindow.Height());

		m_rcWnd[7] = CRect(nWidth * 2, nHeight * 3, nWidth * 3, rcWindow.Height());

	}

	else if (m_nCount == 9)

	{

		nWidth = rcWindow.Width() / 3;

		nHeight = rcWindow.Height() / 3;

		int x, y;

		for (y = 0; y < 3; y++)

		{

			for (x = 0; x < 3; x++)

			{

				if (y == 2)

				{

					if (x == 2)

					{

						m_rcWnd[x + 3 * y] = CRect(x*nWidth, y*nHeight,

							rcWindow.Width(), rcWindow.Height());

					}

					else

					{

						m_rcWnd[x + 3 * y] = CRect(x*nWidth,

							y*nHeight, (x + 1)*nWidth, rcWindow.Height());

					}

				}

				else

				{

					if (x == 2)

					{

						m_rcWnd[x + 3 * y] = CRect(x*nWidth, y*nHeight,

							rcWindow.Width(), (y + 1)*nHeight);

					}

					else

					{

						m_rcWnd[x + 3 * y] = CRect(x*nWidth,

							y*nHeight, (x + 1)*nWidth, (y + 1)*nHeight);

					}

				}

			}

		}

	}

	else if (m_nCount == 16)

	{

		nWidth = rcWindow.Width() / 4;

		nHeight = rcWindow.Height() / 4;

		int x, y;

		for (y = 0; y < 4; y++)

		{

			for (x = 0; x < 4; x++)

			{

				if (y == 3)

				{

					if (x == 3)

					{

						m_rcWnd[x + 4 * y] = CRect(x*nWidth, y*nHeight,

							rcWindow.Width(), rcWindow.Height());

					}

					else

					{

						m_rcWnd[x + 4 * y] = CRect(x*nWidth,

							y*nHeight, (x + 1)*nWidth, rcWindow.Height());

					}

				}

				else

				{

					if (x == 3)

					{

						m_rcWnd[x + 4 * y] = CRect(x*nWidth, y*nHeight,

							rcWindow.Width(), (y + 1)*nHeight);

					}

					else

					{

						m_rcWnd[x + 4 * y] = CRect(x*nWidth,

							y*nHeight, (x + 1)*nWidth, (y + 1)*nHeight);

					}

				}

			}

		}
	}
	//记录原始大小
	for (int i = 0; i < m_nCount; ++i)
		m_player[i].rcWnd = m_rcWnd[i];
}

BOOL CPlayerGroup::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	rcWindow.OffsetRect(-rcWindow.TopLeft());
	pDC->FillSolidRect(&rcWindow, RGB(100,100, 100));
	return TRUE;
}


int CPlayerGroup::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	
	for (int i = 0; i < m_nplayWindowCount; ++i){
		//m_playerGroup.Create(NULL, _T(""), WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_CUSTOMER + 1);
		m_player[i].Create(NULL, _T(""), WS_CHILD | WS_VISIBLE, CRect(0,0,0,0), this, IDC_CUSTOMER + i+1);
	}
	return 0;
}


void CPlayerGroup::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()
	for (int i = 0; i < m_nplayWindowCount; ++i){
		m_player[i].MoveWindow(m_rcWnd[i]);
	}
}


void CPlayerGroup::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	RecalWndPos();

}


// 设置分屏
void CPlayerGroup::SetScreenCount(int nCount)
{
	m_nCount = nCount;
	//重新分屏
	RecalWndPos();
	Invalidate();
	
}


void CPlayerGroup::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	POINT pt;
	CRect rect;
	GetWindowRect(&rect);

	GetCursorPos(&pt);
	point.x = pt.x - rect.left;
	point.y = pt.y - rect.top;

	for (int i = 0; i < m_nCount; ++i){
		
		if (m_rcWnd[i].PtInRect(point)){

			m_player[i].SetSelected(true);
		}
		else{
			m_player[i].SetSelected(false);
		}
	}
	CWnd::OnLButtonDown(nFlags, point);
}


BOOL CPlayerGroup::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_LBUTTONDOWN){
		/*CWnd*pWnd = FromHandle(pMsg->hwnd);
		::SendMessage(GetParent()->m_hWnd, WM_LBUTTONDOWN, 0, 0);*/
		return TRUE;
	}
	return CWnd::PreTranslateMessage(pMsg);
}


void CPlayerGroup::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	POINT pt;
	CRect rect;
	GetWindowRect(&rect);
	CRect clientRect=rect;
	ScreenToClient(clientRect);

	GetCursorPos(&pt);
	point.x = pt.x - rect.left;
	point.y = pt.y - rect.top;

	int MaxSel;
	for (int i = 0; i < m_nCount; ++i){
		
		if (m_rcWnd[i].PtInRect(point)){
			
			MaxSel = i;
			break;
				
		}
	}

	if (!m_player[MaxSel].GetMaxSizeStatus())//当前正常状态
	{
		m_rcWnd[MaxSel] = clientRect;
		m_player[MaxSel].SetMaxSizeStatus(true);
		for (int i = 0; i < m_nCount; ++i){
			if (i != MaxSel)
				m_rcWnd[i] = CRect(0, 0, 0, 0);
		}
	}
	else{								//当前最大化状态
		m_rcWnd[MaxSel] = m_player[MaxSel].rcWnd;
		m_player[MaxSel].SetMaxSizeStatus(false);
		for (int i = 0; i < m_nCount; ++i){
			if (i != MaxSel)
				m_rcWnd[i] = m_player[i].rcWnd;
		}
	}
	Invalidate();
	CWnd::OnLButtonDblClk(nFlags, point);
}
