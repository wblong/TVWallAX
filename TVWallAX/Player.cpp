// Player.cpp : 实现文件
//

#include "stdafx.h"
#include "TVWallAX.h"
#include "Player.h"


// CPlayer

IMPLEMENT_DYNAMIC(CPlayer, CWnd)

CPlayer::CPlayer()
: m_bSelected(false)
, m_bIsMaxsize(false)
{
	//RegisterWindowClass();
	m_edgeColor = RGB(255,255,255);
	m_edgeSelColor = RGB(255, 255, 0);
	m_bSelected = false;
	m_bIsMaxsize = false;
}

CPlayer::~CPlayer()
{
}


BEGIN_MESSAGE_MAP(CPlayer, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
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
	CPen penEdge(PS_SOLID, 1, m_edgeColor);
	CPen* cpTemp;
	cpTemp = dc->SelectObject(&penEdge);
	rcTemp.DeflateRect(1, 1);
	if (!m_bSelected)
		dc->Draw3dRect(rcTemp, m_edgeColor, m_edgeColor);
	else
		dc->Draw3dRect(rcTemp, m_edgeSelColor, m_edgeSelColor);
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

int CPlayer::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	UINT id = this->GetDlgCtrlID() - IDC_PLAYER;
	m_playerItem.Create(NULL, _T(""), WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this,IDC_PLAYERITEM+id);
	return 0;
}


void CPlayer::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()
	CRect rect;
	GetClientRect(&rect);
	rect.DeflateRect(6, 6, 6, 6);
	if (m_playerItem){
		m_playerItem.MoveWindow(&rect);
	}
}


void CPlayer::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
}


BOOL CPlayer::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_LBUTTONDOWN){
		
		::SendMessage(GetParent()->m_hWnd, WM_LBUTTONDOWN, 0, 0);
		//return 0;
	}
	if (pMsg->message == WM_LBUTTONDBLCLK){

		::SendMessage(GetParent()->m_hWnd, WM_LBUTTONDBLCLK, 0, 0);
	}
	return CWnd::PreTranslateMessage(pMsg);
}


void CPlayer::SetSelected(bool Selected)
{
	m_bSelected = Selected;
	Invalidate();
}


// 获取最大化状态
bool CPlayer::GetMaxSizeStatus()
{
	return m_bIsMaxsize;
}


// 设置最大化状态
void CPlayer::SetMaxSizeStatus(bool bMaxSize)
{
	m_bIsMaxsize = bMaxSize;
}


void CPlayer::SavePicture()
{
	m_playerItem.SavePicture();
}


bool CPlayer::GetSelectedStatus()
{
	return m_bSelected;
}


// 播放实时视屏
long CPlayer::StartRealPlay(long connectionID, CString cameraId)
{
	return m_playerItem.StartRealPlay(connectionID,cameraId);
}


// 停止实时播放
long CPlayer::StopRealPlay()
{
	return m_playerItem.StopRealPlay();
}


// 录像功能
long CPlayer::StartLocalRecord()
{
	return m_playerItem.StartLocalRecord();
}
