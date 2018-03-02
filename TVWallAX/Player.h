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
protected:
	//! 选中状态
	bool m_bSelected;
	//! 绘制边框
	void DrawEdge(CDC* dc);
	//
	CRect rcWnd;
	//
	//!未选中边框颜色
	COLORREF m_edgeColor;
	//!选中边框颜色
	COLORREF m_edgeSelColor;
	//!播放控件
	CPlayerItem m_playerItem;
public:
	void SetSelected(bool Selected);
};


