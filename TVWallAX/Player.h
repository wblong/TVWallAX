#pragma once
#include"PlayerItem.h"

// CPlayer

class CPlayer : public CWnd
{
	DECLARE_DYNAMIC(CPlayer)

public:
	CPlayer();
	virtual ~CPlayer();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//BOOL   RegisterWindowClass(HINSTANCE hInstance = NULL);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//!原有的大小
	CRect rcWnd;
protected:
	//! 选中状态
	bool m_bSelected;
	//! 绘制边框
	void DrawEdge(CDC* dc);
	
	//
	//!未选中边框颜色
	COLORREF m_edgeColor;
	//!选中边框颜色
	COLORREF m_edgeSelColor;
	//!播放控件
	CPlayerItem m_playerItem;
public:
	void SetSelected(bool Selected);
protected:
	// 是否是最大化状态
	bool m_bIsMaxsize;
public:
	// 获取最大化状态
	bool GetMaxSizeStatus();
	// 设置最大化状态
	void SetMaxSizeStatus(bool bMaxSize);
	void SavePicture();
	bool GetSelectedStatus();
	// 播放实时视屏
	long StartRealPlay(long connectionID, CString cameraId);
};


