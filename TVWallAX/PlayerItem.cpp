// PlayerItem.cpp : 实现文件
//

#include "stdafx.h"
#include "TVWallAX.h"
#include "PlayerItem.h"
#include "TCS_CommonData.h"
#include "TCS_Functions.h"

///外部函数
//!视频播放回调函数
void CallBackMediaFunc(int sessionId, MediaData* data, void* pUserData);
//!YUV 转换为RGB
bool CONVERT_YUV420PtoRGB24(unsigned char* yuv_y, unsigned char* yuv_u, unsigned char* yuv_v, 
	unsigned char* rgb_dst, int nWidth, int nHeight);

void CallBackMediaFunc(int sessionId, MediaData* data, void* pUserData){
	if (data->errorcode == 0){

		char*pBGR24 = (char *)malloc(data->imageWidth*data->imageHeight * 3);
		//为图像数据申请空间  
		//str.Format("%s",data->yStride);
		//YV12ToBGR24_Native((char*)data->yData,(char*)data->vData,(char*)data->uData,pBGR24,data->imageWidth,data->imageHeight)
		if (CONVERT_YUV420PtoRGB24((unsigned char*)data->yData, (unsigned char*)data->vData, (unsigned char*)data->uData, (unsigned char*)pBGR24, data->imageWidth, data->imageHeight)){
			//显示图像  
			//BMP Header  
			BITMAPINFO m_bmphdr = { 0 };
			DWORD dwBmpHdr = sizeof(BITMAPINFO);
			m_bmphdr.bmiHeader.biBitCount = 24;
			m_bmphdr.bmiHeader.biClrImportant = 0;
			m_bmphdr.bmiHeader.biSize = dwBmpHdr;
			m_bmphdr.bmiHeader.biSizeImage = 0;
			m_bmphdr.bmiHeader.biWidth = data->imageWidth;
			//注意BMP在y方向是反着存储的，一次必须设置一个负值，才能使图像正着显示出来  
			m_bmphdr.bmiHeader.biHeight = -data->imageHeight;
			m_bmphdr.bmiHeader.biXPelsPerMeter = 0;
			m_bmphdr.bmiHeader.biYPelsPerMeter = 0;
			m_bmphdr.bmiHeader.biClrUsed = 0;
			m_bmphdr.bmiHeader.biPlanes = 1;
			m_bmphdr.bmiHeader.biCompression = BI_RGB;
			//数据传递
			
			CWnd* pWnd;
			pWnd = CWnd::FromHandle((HWND)pUserData);
			
			if (pWnd){
				CRect rect;
				pWnd->GetClientRect(&rect);
				if (rect.Width()>0 && rect.Height()>0){
					//异常中断
					CDC *pDC = pWnd->GetDC();
					
					//pDC->Ellipse(rect);
					pDC->SetStretchBltMode(COLORONCOLOR);
					StretchDIBits(pDC->GetSafeHdc(), rect.left, rect.top, rect.Width(), rect.Height(), 0, 0,
						data->imageWidth, data->imageHeight, pBGR24, &m_bmphdr, DIB_RGB_COLORS, SRCCOPY);
					ReleaseDC(pWnd->m_hWnd, pDC->m_hDC);
				}
			}
		}
		//
		delete[] pBGR24;
		pBGR24 = NULL;
	}

}

inline unsigned char CONVERT_ADJUST(double tmp)
{
	return (unsigned char)((tmp >= 0 && tmp <= 255) ? tmp : (tmp < 0 ? 0 : 255));
}

bool CONVERT_YUV420PtoRGB24(unsigned char* yuv_y, unsigned char* yuv_u, unsigned char* yuv_v, unsigned char* rgb_dst, int nWidth, int nHeight)
{
	if (nWidth < 1 || nHeight < 1 || yuv_y == NULL || yuv_u == NULL || yuv_v == NULL || rgb_dst == NULL)
		return false;
	unsigned char *tmpbuf = (unsigned char *)malloc(nWidth*nHeight * 3);
	unsigned char Y, U, V, R, G, B;
	unsigned char* y_planar, *u_planar, *v_planar;
	int rgb_width, u_width;
	rgb_width = nWidth * 3;
	u_width = (nWidth >> 1);
	int ypSize = nWidth * nHeight;
	int upSize = (ypSize >> 2);
	int offSet = 0;

	y_planar = yuv_y;
	u_planar = yuv_u;
	v_planar = yuv_v;


	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
		{
			// Get the Y value from the y planar
			// Get the Y value from the y planar
			Y = *(y_planar + nWidth * i + j);
			// Get the V value from the u planar
			offSet = (i >> 1) * (u_width)+(j >> 1);
			V = *(u_planar + offSet);
			// Get the U value from the v planar
			U = *(v_planar + offSet);

			// Cacular the R,G,B values
			// Method 1
			R = CONVERT_ADJUST((Y + (1.4075 * (V - 128))));
			G = CONVERT_ADJUST((Y - (0.3455 * (U - 128) + 0.7169 * (V - 128))));
			B = CONVERT_ADJUST((Y + (1.7790 * (U - 128))));
			/*
			// The following formulas are from MicroSoft' MSDN
			int C,D,E;
			// Method 2
			C = Y - 16;
			D = U - 128;
			E = V - 128;
			R = CONVERT_ADJUST(( 298 * C + 409 * E + 128) >> 8);
			G = CONVERT_ADJUST(( 298 * C - 100 * D - 208 * E + 128) >> 8);
			B = CONVERT_ADJUST(( 298 * C + 516 * D + 128) >> 8);
			R = ((R - 128) * .6 + 128 )>255?255:(R - 128) * .6 + 128;
			G = ((G - 128) * .6 + 128 )>255?255:(G - 128) * .6 + 128;
			B = ((B - 128) * .6 + 128 )>255?255:(B - 128) * .6 + 128;
			*/

			offSet = rgb_width * i + j * 3;

			rgb_dst[offSet] = B;
			rgb_dst[offSet + 1] = G;
			rgb_dst[offSet + 2] = R;
		}
	}
	free(tmpbuf);
	return true;
}

// CPlayerItem

IMPLEMENT_DYNAMIC(CPlayerItem, CWnd)

CPlayerItem::CPlayerItem()
: m_nSessionID(-1)
, m_strCameraID(_T(""))
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


// 播放实时视频
long CPlayerItem::StartRealPlay(long connectionId, CString cameraId)
{
	if (m_nSessionID <0)
	{
		//记录相机ID
		m_strCameraID = cameraId;
		//播放视屏
		m_nSessionID = TCS_StartRealPlay(connectionId, cameraId,
			MainStream, CallBackMediaFunc, this->GetSafeHwnd());
	}
	else{
		//关闭先前的
		TCS_StopRealPlay(m_nSessionID);
	}
	return m_nSessionID;
}
