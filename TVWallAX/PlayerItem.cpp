// PlayerItem.cpp : 实现文件
//

#include "stdafx.h"
#include "TVWallAX.h"
#include "PlayerItem.h"


// CPlayerItem

IMPLEMENT_DYNAMIC(CPlayerItem, CWnd)

CPlayerItem::CPlayerItem()
{
	saveFilePath = _T("C:\\Capture\\");
}

CPlayerItem::~CPlayerItem()
{
}


BEGIN_MESSAGE_MAP(CPlayerItem, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CPlayerItem 消息处理程序




BOOL CPlayerItem::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	rcWindow.OffsetRect(-rcWindow.TopLeft());
	pDC->FillSolidRect(&rcWindow,RGB(120,120,120));
	CString str;
	str.Format(_T("%d"),this->GetDlgCtrlID()-IDC_PLAYERITEM+1);
	pDC->DrawText(str, rcWindow, DT_SINGLELINE | DT_VCENTER|DT_CENTER);
	return true;
	//return CWnd::OnEraseBkgnd(pDC);
}


void CPlayerItem::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
}


void CPlayerItem::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	//::SendMessage(GetParent()->m_hWnd, WM_LBUTTONDOWN, 0, 0);
	CWnd::OnLButtonDown(nFlags, point);
}


BOOL CPlayerItem::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_LBUTTONDOWN){
		
		::SendMessage(GetParent()->m_hWnd, WM_LBUTTONDOWN, 0, 0);
	}
	if (pMsg->message == WM_LBUTTONDBLCLK){
		
		::SendMessage(GetParent()->m_hWnd,WM_LBUTTONDBLCLK,0,0);
	}
	return CWnd::PreTranslateMessage(pMsg);
}


// 截图保存
void CPlayerItem::SavePicture()
{
	CClientDC dc(this);
	CRect rect;
	//BOOL  showMsgTag;                  //是否要弹出”图像保存成功对话框"   
	GetClientRect(&rect);                  //获取画布大小  
	HBITMAP hbitmap = CreateCompatibleBitmap(dc, rect.right - rect.left, rect.bottom - rect.top);
	//创建兼容位图  
	HDC hdc = CreateCompatibleDC(dc);      //创建兼容DC，以便将图像保存为不同的格式  
	HBITMAP hOldMap = (HBITMAP)SelectObject(hdc, hbitmap);
	//将位图选入DC，并保存返回值   
	BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, dc, 0, 0, SRCCOPY);
	//将屏幕DC的图像复制到内存DC中  
	ATL::CImage image;
	image.Attach(hbitmap);                //将位图转化为一般图像  

	CString  strFilter = _T("位图文件(*.bmp)|*.bmp|JPEG 图像文件|*.jpg|GIF图像文件 | *.gif | PNG图像文件 | *.png |其他格式(*.*) | *.* || ");  
	CFileDialog dlg(FALSE, _T("bmp"), _T("unknown.bmp"), NULL, strFilter);
	if (dlg.DoModal() != IDOK)
		return;
	CString strFileName;          //如果用户没有指定文件扩展名，则为其添加一个  
	CString strExtension;
	strFileName = dlg.m_ofn.lpstrFile;

	if (dlg.m_ofn.nFileExtension = 0)               //扩展名项目为0  
	{
		switch (dlg.m_ofn.nFilterIndex)
		{
		case 1:
			strExtension = "bmp"; break;
		case 2:
			strExtension = "jpg"; break;
		case 3:
			strExtension = "gif"; break;
		case 4:
			strExtension = "png"; break;
		default:
			break;
		}
		strFileName = strFileName +_T( ".") + strExtension;

	}

	saveFilePath = strFileName;     //saveFilePath为视类中的全局变量,类型为CString  
	//AfxMessageBox(saveFilePath); //显示图像保存的全路径(包含文件名)  

	HRESULT hResult = image.Save(saveFilePath);     //保存图像  
	if (FAILED(hResult))
	{
		MessageBox(_T("保存图像文件失败！"),_T("提示"));

	}
	else
	{
		MessageBox(_T("文件保存成功！"),_T("提示"));

	}
	image.Detach();
	SelectObject(hdc, hOldMap);
}
