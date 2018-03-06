#pragma once
#include"PlayerGroup.h"
// TVWallAXCtrl.h : CTVWallAXCtrl ActiveX 控件类的声明。


// CTVWallAXCtrl : 有关实现的信息，请参阅 TVWallAXCtrl.cpp。

class CTVWallAXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CTVWallAXCtrl)

// 构造函数
public:
	CTVWallAXCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual DWORD GetControlFlags();

// 实现
protected:
	~CTVWallAXCtrl();

	DECLARE_OLECREATE_EX(CTVWallAXCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CTVWallAXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CTVWallAXCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CTVWallAXCtrl)		// 类型名称和杂项状态

	// 子类控件支持
	BOOL IsSubclassedControl();
	LRESULT OnOcmCommand(WPARAM wParam, LPARAM lParam);

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
		dispidStartLocalRecord = 16L,
		dispidStopRealPlay = 15L,
		dispidStartRealPlay = 14L,
		dispidGetCameraList = 13L,
		dispidGetSupportedPlatform = 12L,
		dispidLogout = 11L,
		dispidLogin = 10L,
		dispidPlatformID = 9,
		dispidSocketType = 8,
		dispidPort = 7,
		dispidPassWd = 6,
		dispidUserName = 5,
		dispidIP = 4,
		dispidUnInit = 3L,
		dispidInit = 2L,
		dispidSetScreenNum = 1L
	};
	//
	CPlayerGroup m_playerGroup;
	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);


protected:
	void SetScreenNum(LONG Num);
	//---- window fullscreen and normal
	BOOL m_bFullScreenFlag;
	WINDOWPLACEMENT m_wpPrev;
	HWND m_hwndParent;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//!分屏响应函数
	void OnScreenBtnClicked(UINT uId);
	//！full screen
	void OnFullScreenBtnClicked();
	//! shot
	void OnScreenShotBtnClicked();
	//!videoRecord
	void OnVideoRecordBtnClicked();
	//!
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	///< 取得显示器宽、高
	void GetMaxMonitorRect(LPRECT prc);
	///< 最大化窗口
	int MaxiumWindow();
	///< 恢复窗口
	int ResetWindowSize();
protected:
	LONG Init();
	LONG UnInit();
	void OnIPChanged();
	CString m_strIP;
	void OnUserNameChanged();
	CString m_strUserName;
	void OnPassWdChanged();
	CString m_strPassWd;
	void OnPortChanged();
	LONG m_nPort;
	void OnSocketTypeChanged();
	LONG m_nSocketType;
	void OnPlatformIDChanged();
	LONG m_nPlatformID;
	LONG Login();
	LONG Logout();
	LONG m_nConnectionID;
	BSTR GetSupportedPlatform();
	BSTR GetCameraList();
	LONG StartRealPlay(LPCTSTR cameraId);
	LONG StopRealPlay();
	LONG StartLocalRecord();
};

