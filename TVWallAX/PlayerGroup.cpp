// PlayerGroup.cpp : 实现文件
//

#include "stdafx.h"
#include "TVWallAX.h"
#include "PlayerGroup.h"
// CPlayerGroup

#define ID_TIMER 1

IMPLEMENT_DYNAMIC(CPlayerGroup, CWnd)

CPlayerGroup::CPlayerGroup()
: m_nCurrentIndex(0)
{
	m_nCount = 4;
	m_nplayWindowCount = 4;
	m_nActivePlayer = 0;
	//默认轮播时间10s
	m_nPlayBatchTime = 10000;
	m_nConnectionID = -1;
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
	ON_WM_TIMER()
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
		m_player[i].Create(NULL, _T(""), WS_CHILD | WS_VISIBLE, CRect(0,0,0,0), this, IDC_PLAYER + i);
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
			m_nActivePlayer = i;
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

	//取得最大化窗口
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


// 获取当前激活的PlayerItem
void CPlayerGroup::SavePicture()
{
	if (m_player[m_nActivePlayer].GetSelectedStatus())
		m_player[m_nActivePlayer].SavePicture();
	else
		MessageBox(_T("请单击选择分屏"),_T("提示"));
}


// 播放实时视频
long CPlayerGroup::StartRealPlay(long connectionID, CString cameraId)
{
	if (m_player[m_nActivePlayer].GetSelectedStatus())
		return m_player[m_nActivePlayer].StartRealPlay(connectionID, cameraId);
	else{
		MessageBox(_T("请单击选择分屏"), _T("提示"));
	}
	return -1;
}


// 停止实时监控
long CPlayerGroup::StopRealPlay()
{
	if (m_player[m_nActivePlayer].GetSelectedStatus())
		return m_player[m_nActivePlayer].StopRealPlay();
	else{
		MessageBox(_T("请单击选择分屏"), _T("提示"));
	}
	return -1;
}


// 录像
long CPlayerGroup::StartLocalRecord()
{
	//可以在playeritem中判断
	if (m_player[m_nActivePlayer].GetSelectedStatus())
		return m_player[m_nActivePlayer].StartLocalRecord();
	else
	{
		MessageBox(_T("请单击选择分屏"), _T("提示"));
	}
	return -1;
}


// 获取分屏数目
long CPlayerGroup::GetScreenCount()
{
	return (long)m_nCount;
}
//分割字符串
void CPlayerGroup::StringSplit(CString source, CStringArray& dest, char division)
{
	if (source.IsEmpty())
	{

	}
	else
	{   //递归调用
		int pos = source.Find(division);
		if (pos == -1)
		{
			dest.Add(source);
		}
		else
		{
			dest.Add(source.Left(pos));
			source = source.Mid(pos + 1);
			StringSplit(source, dest, division);
		}
	}
}

// 设置轮播时间
void CPlayerGroup::SetInterval(long  millisecond)
{
	m_nPlayBatchTime = millisecond;
}

//
void CPlayerGroup::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	BatchPlay(m_nConnectionID);
	CWnd::OnTimer(nIDEvent);
}


// 开始轮播
void CPlayerGroup::StartBatchPlay(int connectionID)
{
	//已经在轮播直接返回
	
	BatchPlay(connectionID);
	//
	SetTimer(ID_TIMER, m_nPlayBatchTime, NULL);
}


// 设置相机列表
void CPlayerGroup::SetCamerasIDS(CString camerasIds)
{	
	if (m_strArrCameras.GetSize() > 0){
		MessageBox("请先关闭轮播！", "提示");
		return;
	}
	StringSplit(camerasIds, m_strArrCameras, ';');
}


// 停止轮播
void CPlayerGroup::StopPlayBatch()
{
	KillTimer(ID_TIMER);
    m_strArrCameras.RemoveAll();
	MessageBox("停止轮播", "提示");
}


// 轮播
void CPlayerGroup::BatchPlay(int connectionID)
{
	int size = m_strArrCameras.GetSize();
	int count = m_nCount;
	//关闭先前的
	for (int i = 0; i < m_nCount; ++i)
		m_player[i].StopRealPlay();
	int i, j;
	CString	index;

	for (i = m_nCurrentIndex; i <= size; ++i){
		j = i%count;
		if (j == 0 && i != m_nCurrentIndex){
			m_nCurrentIndex = i;
			break;
		}
		if (i == size){
			m_nCurrentIndex = i%size;
			break;
		}
		index = m_strArrCameras.GetAt(i);
		m_player[j].StartRealPlay(connectionID, index);
		

	}
}


// 设置连接ID
void CPlayerGroup::SetConnectionID(int connectionID)
{
	m_nConnectionID = connectionID;
}
