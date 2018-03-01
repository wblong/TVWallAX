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
	
};


