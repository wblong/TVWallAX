// TVWallAXCtrl.cpp : CTVWallAXCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "TVWallAX.h"
#include "TVWallAXCtrl.h"
#include "TVWallAXPropPage.h"
#include "afxdialogex.h"

#define WM_THREADFIREEVENT WM_APP+101

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CTVWallAXCtrl, COleControl)

// 消息映射

BEGIN_MESSAGE_MAP(CTVWallAXCtrl, COleControl)
	ON_MESSAGE(OCM_COMMAND, &CTVWallAXCtrl::OnOcmCommand)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_CONTROL_RANGE(BN_CLICKED,IDC_ONESCREEN,IDC_SIXTEENSCREEN,OnScreenBtnClicked)
	ON_CONTROL(BN_CLICKED,IDC_FULLSCREEN,OnFullScreenBtnClicked)
	ON_CONTROL(BN_CLICKED,IDC_SCREENSHOT,OnScreenShotBtnClicked)
	ON_WM_WINDOWPOSCHANGING()
	ON_MESSAGE(WM_THREADFIREEVENT,OnFireEventForThread)
END_MESSAGE_MAP()

// 调度映射

BEGIN_DISPATCH_MAP(CTVWallAXCtrl, COleControl)
	DISP_FUNCTION_ID(CTVWallAXCtrl, "SetScreenNum", dispidSetScreenNum, SetScreenNum, VT_EMPTY, VTS_I4)
END_DISPATCH_MAP()

// 事件映射

BEGIN_EVENT_MAP(CTVWallAXCtrl, COleControl)
	EVENT_CUSTOM_ID("calljs", eventidcalljs, calljs, VTS_I2)
END_EVENT_MAP()

// 属性页

// TODO:  按需要添加更多属性页。  请记住增加计数!
BEGIN_PROPPAGEIDS(CTVWallAXCtrl, 1)
	PROPPAGEID(CTVWallAXPropPage::guid)
END_PROPPAGEIDS(CTVWallAXCtrl)

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CTVWallAXCtrl, "TVWALLAX.TVWallAXCtrl.1",
	0xc639e623, 0xf7c2, 0x445e, 0xb8, 0x89, 0x9d, 0x72, 0xb4, 0x67, 0xd4, 0xf4)

// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CTVWallAXCtrl, _tlid, _wVerMajor, _wVerMinor)

// 接口 ID

const IID IID_DTVWallAX = { 0x287392D1, 0xCAFD, 0x4EBA, { 0x9B, 0x4C, 0xE8, 0x7C, 0x49, 0x1F, 0x36, 0x38 } };
const IID IID_DTVWallAXEvents = { 0x8E0C406E, 0xDBCD, 0x4EE0, { 0x8F, 0x89, 0x61, 0x8C, 0xBD, 0xEF, 0x47, 0x65 } };

// 控件类型信息

static const DWORD _dwTVWallAXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CTVWallAXCtrl, IDS_TVWALLAX, _dwTVWallAXOleMisc)

// CTVWallAXCtrl::CTVWallAXCtrlFactory::UpdateRegistry -
// 添加或移除 CTVWallAXCtrl 的系统注册表项

BOOL CTVWallAXCtrl::CTVWallAXCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO:  验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_TVWALLAX,
			IDB_TVWALLAX,
			afxRegApartmentThreading,
			_dwTVWallAXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


// CTVWallAXCtrl::CTVWallAXCtrl - 构造函数

CTVWallAXCtrl::CTVWallAXCtrl()
	: m_a(0)
{
	InitializeIIDs(&IID_DTVWallAX, &IID_DTVWallAXEvents);
	// TODO:  在此初始化控件的实例数据。
	m_bFullScreenFlag = false;
}

// CTVWallAXCtrl::~CTVWallAXCtrl - 析构函数

CTVWallAXCtrl::~CTVWallAXCtrl()
{
	// TODO:  在此清理控件的实例数据。
}

// CTVWallAXCtrl::OnDraw - 绘图函数

void CTVWallAXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& /* rcInvalid */)
{
	if (!pdc)
		return;
	//背景颜色
	pdc->FillSolidRect(rcBounds,RGB(0,0,0));

	if (m_playerGroup)
	{
		CRect rect = rcBounds;
		rect.DeflateRect(0, 0, 0, 50);
		m_playerGroup.MoveWindow(rect);///2
		
		int margin_left = 5, margin_top = 5 , width = 40, height = 40;

		for (int i = 0; i < 8; ++i){

			GetDlgItem(IDC_ONESCREEN+i)->MoveWindow(CRect(rect.left + margin_left*(i+1)+width*i, rect.bottom + margin_top, 
				rect.left + margin_left * (i + 1) + width* (i+1), rect.bottom + height+margin_top-2));
		}
		/*GetDlgItem(IDC_ONESCREEN)->MoveWindow(CRect(rect.left+2,rect.bottom+2,rect.left+52,rect.bottom+42));
		GetDlgItem(IDC_FOURSCREEN)->MoveWindow(CRect(rect.left + 2, rect.bottom + 2, rect.left + 52, rect.bottom + 42));
		GetDlgItem(IDC_SIXSCREEN)->MoveWindow(CRect(rect.left + 2, rect.bottom + 2, rect.left + 52, rect.bottom + 42));
		GetDlgItem(IDC_EIGHTSCREEN)->MoveWindow(CRect(rect.left + 2, rect.bottom + 2, rect.left + 52, rect.bottom + 42));
		GetDlgItem(IDC_NINESCREEN)->MoveWindow(CRect(rect.left + 2, rect.bottom + 2, rect.left + 52, rect.bottom + 42));
		GetDlgItem(IDC_SIXTEENSCREEN)->MoveWindow(CRect(rect.left + 2, rect.bottom + 2, rect.left + 52, rect.bottom + 42));*/
	}
	//DoSuperclassPaint(pdc, rcBounds);
}

// CTVWallAXCtrl::DoPropExchange - 持久性支持

void CTVWallAXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO:  为每个持久的自定义属性调用 PX_ 函数。
}


// CTVWallAXCtrl::GetControlFlags -
// 自定义 MFC 的 ActiveX 控件实现的标志。
//
DWORD CTVWallAXCtrl::GetControlFlags()
{
	DWORD dwFlags = COleControl::GetControlFlags();


	// 在活动和不活动状态之间进行转换时，
	// 不会重新绘制控件。
	dwFlags |= noFlickerActivate;
	return dwFlags;
}


// CTVWallAXCtrl::OnResetState - 将控件重置为默认状态

void CTVWallAXCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO:  在此重置任意其他控件状态。
}


// CTVWallAXCtrl::PreCreateWindow - 修改 CreateWindowEx 的参数

BOOL CTVWallAXCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.lpszClass = _T("STATIC");
	cs.style = SS_NOTIFY | WS_VISIBLE | WS_CHILD;
	m_hwndParent = cs.hwndParent;
	return COleControl::PreCreateWindow(cs);
}

// CTVWallAXCtrl::IsSubclassedControl - 这是一个子类控件

BOOL CTVWallAXCtrl::IsSubclassedControl()
{
	return TRUE;
}

// CTVWallAXCtrl::OnOcmCommand - 处理命令消息

LRESULT CTVWallAXCtrl::OnOcmCommand(WPARAM wParam, LPARAM lParam)
{
	WORD wNotifyCode = HIWORD(wParam);

	// TODO:  在此接通 wNotifyCode。

	return 0;
}


// CTVWallAXCtrl 消息处理程序


int CTVWallAXCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_playerGroup.Create(NULL, _T(""), WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_PLAYERGROUP);
	//
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON;

	CBitmapButton* OneScreen = new CBitmapButton();
	OneScreen->Create(_T("一"), dwStyle, CRect(0,0,0,0), this, IDC_ONESCREEN);

	CBitmapButton* FourScreen = new CBitmapButton();
	FourScreen->Create(_T("四"), dwStyle, CRect(0, 0, 0, 0), this, IDC_FOURSCREEN);

	CBitmapButton* SixScreen = new CBitmapButton();
	SixScreen->Create(_T("六"), dwStyle, CRect(0, 0, 0, 0), this, IDC_SIXSCREEN);

	CBitmapButton* EightScreen = new CBitmapButton();
	EightScreen->Create(_T("八"), dwStyle, CRect(0, 0, 0, 0), this, IDC_EIGHTSCREEN);

	CBitmapButton* NineScreen = new CBitmapButton();
	NineScreen->Create(_T("九"), dwStyle, CRect(0, 0, 0, 0), this, IDC_NINESCREEN);

	CBitmapButton* SixteenScreen = new CBitmapButton();
	SixteenScreen->Create(_T("十六"), dwStyle, CRect(0, 0, 0, 0), this, IDC_SIXTEENSCREEN);

	CBitmapButton* FullScreen = new CBitmapButton();
	FullScreen->Create(_T("全屏"), dwStyle, CRect(0, 0, 0, 0), this, IDC_FULLSCREEN);

	CBitmapButton* ScreenShot = new CBitmapButton();
	ScreenShot->Create(_T("截图"), dwStyle, CRect(0, 0, 0, 0), this, IDC_SCREENSHOT);
	return 0;
}


void CTVWallAXCtrl::SetScreenNum(LONG Num)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO:  在此添加调度处理程序代码]
	m_playerGroup.SetScreenCount(Num);
}


void CTVWallAXCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	//触发并调用客户端js代码
	Invoke(1);
	COleControl::OnLButtonDown(nFlags, point);
}


BOOL CTVWallAXCtrl::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_LBUTTONDOWN){
		/*CWnd*pWnd = FromHandle(pMsg->hwnd);
		::SendMessage(GetParent()->m_hWnd, WM_LBUTTONDOWN, 0, 0);*/
		//return 0;
	}
	return COleControl::PreTranslateMessage(pMsg);
}
void CTVWallAXCtrl::OnScreenBtnClicked(UINT uId){
	int Num = 16;
	switch (uId){
	case IDC_ONESCREEN:
		Num = 1;
		break;
	case IDC_FOURSCREEN:
		Num = 4;
		break;
	case IDC_SIXSCREEN:
		Num = 6;
		break;
	case IDC_EIGHTSCREEN:
		Num = 8;
		break;
	case IDC_NINESCREEN:
		Num = 9;

		break;
	case IDC_SIXTEENSCREEN:
		Num = 16;
		break;

	}
	m_playerGroup.SetScreenCount(Num);
}
void CTVWallAXCtrl::OnFullScreenBtnClicked(){
	
	m_bFullScreenFlag = !m_bFullScreenFlag;
	if (m_bFullScreenFlag)
	{
		MaxiumWindow();
	}
	else
	{
		ResetWindowSize();
	}
}

void CTVWallAXCtrl::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{

	if (::GetParent(m_hWnd) != m_hwndParent)
	{
		CRect rc;
		GetMaxMonitorRect(&rc);
		lpwndpos->cx = rc.Width();
		lpwndpos->cy = rc.Height();
		lpwndpos->x = rc.left;
		lpwndpos->y = rc.top;
	}
	COleControl::OnWindowPosChanging(lpwndpos);

	// TODO:  在此处添加消息处理程序代码

}
///< 取得显示器宽、高  
void CTVWallAXCtrl::GetMaxMonitorRect(LPRECT prc)
{
	HMONITOR hMonitor;
	MONITORINFOEX mi;
	RECT rc;
	hMonitor = MonitorFromWindow(m_hWnd, MONITOR_DEFAULTTONEAREST);
	mi.cbSize = sizeof(mi);
	GetMonitorInfo(hMonitor, &mi);
	rc = mi.rcMonitor;
	*prc = rc;
}
///< 最大化窗口  
int CTVWallAXCtrl::MaxiumWindow()
{
	HWND hwnd = GetSafeHwnd();
	RECT rc;
	// 取得显示器的宽、高  
	GetMaxMonitorRect(&rc);
	// 计算画面宽、高  
	int nWidth = rc.right - rc.left;
	int nHeight = rc.bottom - rc.top;
	// 取得原始位置并保存  
	m_wpPrev.length = sizeof(WINDOWPLACEMENT);
	::GetWindowPlacement(m_hWnd, &m_wpPrev);
	// 窗口全屏  
	SetParent(NULL);
	DWORD dwFlag = SWP_DRAWFRAME;
	BOOL bSucceed = ::SetWindowPos(m_hWnd, HWND_TOPMOST, rc.left, rc.top, nWidth, nHeight, dwFlag);
	return 1;
}
///< 恢复窗口  
int CTVWallAXCtrl::ResetWindowSize()
{
	if (NULL != m_hwndParent)
	{
		::SetParent(m_hWnd, m_hwndParent);
		m_wpPrev.flags = SW_SHOWMAXIMIZED;
		::SetWindowPlacement(m_hWnd, &m_wpPrev);
	}
	HWND hWnd = ::FindWindow(_T("Shell_TrayWnd"), NULL);
	HWND hStar = ::FindWindow(_T("Button"), NULL);
	::ShowWindow(hWnd, SW_SHOW);
	::ShowWindow(hStar, SW_SHOW);
	return 1;
}
void CTVWallAXCtrl::OnScreenShotBtnClicked(){
	m_playerGroup.SavePicture();
}
//
void f(void*r){

	CTVWallAXCtrl*p = (CTVWallAXCtrl*)r;
	Sleep(5000);
	p->m_a += 10;
	PostMessage(p->m_hWnd, WM_THREADFIREEVENT, (WPARAM)NULL, (LPARAM)NULL);
	return;
}
// 测试函数
void CTVWallAXCtrl::Invoke(short a)
{
	m_a = a;
	_beginthread(f, 0, (void*)this);
}
//测试事件处理函数
LRESULT CTVWallAXCtrl::OnFireEventForThread(WPARAM wParam, LPARAM lParam)
{
	this->calljs(m_a);
	return TRUE;
}