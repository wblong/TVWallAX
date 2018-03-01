#pragma once


// CPlayerItem

class CPlayerItem : public CWnd
{
	DECLARE_DYNAMIC(CPlayerItem)

public:
	CPlayerItem();
	virtual ~CPlayerItem();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


