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
	// 截图保存
	void SavePicture();
	CString saveFilePath;
	// 播放实时视频
	long StartRealPlay(long connectionId, CString cameraId);
	// 当前会话
	long m_nSessionID;
	// 相机ID
	CString m_strCameraID;
	// 停止实时播放
	long StopRealPlay();
	// 开始本地录像
	long StartLocalRecord();
	// 录像状态
	bool m_bVideoStart;
};


