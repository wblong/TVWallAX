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
	// ªÊ÷∆±ﬂ
	void DrawEdge(CDC* dc);
	//
	CRect rcWnd;
	//
	CPlayerItem m_playerItem;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
};


