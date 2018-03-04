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
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	// ½ØÍ¼±£´æ
	void SavePicture();
	CString saveFilePath;
};


