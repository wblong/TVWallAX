#pragma once
#include"Player.h"

// CPlayerGroup

class CPlayerGroup : public CWnd
{
	DECLARE_DYNAMIC(CPlayerGroup)

public:
	CPlayerGroup();
	virtual ~CPlayerGroup();

protected:
	DECLARE_MESSAGE_MAP()
public:
	void RecalWndPos();
private:
	int m_nplayWindowCount;
	//!分屏数目
	int m_nCount;
	CRect m_rcWnd[16];
	CRect m_rcWndMax;
	CPlayer m_player[16];
	int m_nActivePlayer;
	//!连接ID
	int m_nConnectionID;
	
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	// 设置分屏
	void SetScreenCount(int nCount);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	
	// 截图
	void SavePicture();
	// 播放实时视频
	long StartRealPlay(long connectionID, CString cameraId);
	// 停止实时监控
	long StopRealPlay();
	// 录像
	long StartLocalRecord();
	// 获取分屏数目
	long GetScreenCount();
	//字符串分割
	void StringSplit(CString source, CStringArray& dest, char division);
	//相机列表
	CStringArray m_strArrCameras;
	//轮播间隔
	int m_nPlayBatchTime;
	// 设置轮播时间
	void SetInterval(long  millisecond);
	//
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// 开始轮播
	void StartBatchPlay(int connectionID);
	// 设置相机列表
	void SetCamerasIDS(CString camerasIds);
	// 停止轮播
	void StopPlayBatch();
	// 轮播
	void BatchPlay(int connectionID);
	// 设置连接ID
	void SetConnectionID(int connectionID);
	// 标记下一次轮播的索引
	int m_nCurrentIndex;
};


