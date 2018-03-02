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
	int m_nCount;
	CRect m_rcWnd[16];
	CRect m_rcWndMax;
	CPlayer m_player[16];
	
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


