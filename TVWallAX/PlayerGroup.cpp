// PlayerGroup.cpp : 实现文件
//

#include "stdafx.h"
#include "TVWallAX.h"
#include "PlayerGroup.h"


// CPlayerGroup

IMPLEMENT_DYNAMIC(CPlayerGroup, CWnd)

CPlayerGroup::CPlayerGroup()
{

}

CPlayerGroup::~CPlayerGroup()
{
}


BEGIN_MESSAGE_MAP(CPlayerGroup, CWnd)
END_MESSAGE_MAP()



// CPlayerGroup 消息处理程序



//子控件的布局
void CPlayerGroup::RecalWndPos()
{
	CRect rcWindow;
	GetClientRect(rcWindow);

	int nWidth;
	int nHeight;
	int nPos;
	//清空所有CRect
	for (nPos = 0; nPos < m_nplayWindowCount; nPos++){

		m_rcWnd[nPos] = CRect(0, 0, 0, 0);
		m_player[nPos].rcWnd = CRect(0, 0, 0, 0);
	}
	//
	//得到最大化CRect
	m_rcWndMax = rcWindow;
	//计算各个显示数量时的CRect

	if (m_nCount == 1)
	{
		rcWindow.InflateRect(0, 0, 0, 0);
		m_rcWnd[0] = rcWindow;
	}

	else if (m_nCount == 4)
	{

		nWidth = rcWindow.Width() / 2;
		nHeight = rcWindow.Height() / 2;
		m_rcWnd[0] = CRect(0, 0, nWidth, nHeight);
		m_rcWnd[1] = CRect(nWidth, 0, rcWindow.Width(), nHeight);
		m_rcWnd[2] = CRect(0, nHeight, nWidth, rcWindow.Height());
		m_rcWnd[3] = CRect(nWidth, nHeight, rcWindow.Width(), rcWindow.Height());

	}
	else if (m_nCount == 6)

	{

		nWidth = rcWindow.Width() / 3;
		nHeight = rcWindow.Height() / 3;

		m_rcWnd[0] = CRect(0, 0, nWidth * 2, nHeight * 2);

		m_rcWnd[1] = CRect(nWidth * 2, 0, rcWindow.Width(), nHeight);

		m_rcWnd[2] = CRect(nWidth * 2, nHeight, rcWindow.Width(), nHeight * 2);

		m_rcWnd[3] = CRect(nWidth * 2, nHeight * 2, rcWindow.Width(), rcWindow.Height());

		m_rcWnd[4] = CRect(0, nHeight * 2, nWidth, rcWindow.Height());

		m_rcWnd[5] = CRect(nWidth, nHeight * 2, nWidth * 2, rcWindow.Height());

	}

	else if (m_nCount == 8)

	{

		nWidth = rcWindow.Width() / 4;

		nHeight = rcWindow.Height() / 4;

		m_rcWnd[0] = CRect(0, 0, nWidth * 3, nHeight * 3);

		m_rcWnd[1] = CRect(nWidth * 3, 0, rcWindow.Width(), nHeight);

		m_rcWnd[2] = CRect(nWidth * 3, nHeight, rcWindow.Width(), nHeight * 2);

		m_rcWnd[3] = CRect(nWidth * 3, nHeight * 2, rcWindow.Width(), nHeight * 3);

		m_rcWnd[4] = CRect(nWidth * 3, nHeight * 3, rcWindow.Width(), rcWindow.Height());

		m_rcWnd[5] = CRect(0, nHeight * 3, nWidth, rcWindow.Height());

		m_rcWnd[6] = CRect(nWidth, nHeight * 3, nWidth * 2, rcWindow.Height());

		m_rcWnd[7] = CRect(nWidth * 2, nHeight * 3, nWidth * 3, rcWindow.Height());

	}

	else if (m_nCount == 9)

	{

		nWidth = rcWindow.Width() / 3;

		nHeight = rcWindow.Height() / 3;

		int x, y;

		for (y = 0; y < 3; y++)

		{

			for (x = 0; x < 3; x++)

			{

				if (y == 2)

				{

					if (x == 2)

					{

						m_rcWnd[x + 3 * y] = CRect(x*nWidth, y*nHeight,

							rcWindow.Width(), rcWindow.Height());

					}

					else

					{

						m_rcWnd[x + 3 * y] = CRect(x*nWidth,

							y*nHeight, (x + 1)*nWidth, rcWindow.Height());

					}

				}

				else

				{

					if (x == 2)

					{

						m_rcWnd[x + 3 * y] = CRect(x*nWidth, y*nHeight,

							rcWindow.Width(), (y + 1)*nHeight);

					}

					else

					{

						m_rcWnd[x + 3 * y] = CRect(x*nWidth,

							y*nHeight, (x + 1)*nWidth, (y + 1)*nHeight);

					}

				}

			}

		}

	}

	else if (m_nCount == 16)

	{

		nWidth = rcWindow.Width() / 4;

		nHeight = rcWindow.Height() / 4;

		int x, y;

		for (y = 0; y < 4; y++)

		{

			for (x = 0; x < 4; x++)

			{

				if (y == 3)

				{

					if (x == 3)

					{

						m_rcWnd[x + 4 * y] = CRect(x*nWidth, y*nHeight,

							rcWindow.Width(), rcWindow.Height());

					}

					else

					{

						m_rcWnd[x + 4 * y] = CRect(x*nWidth,

							y*nHeight, (x + 1)*nWidth, rcWindow.Height());

					}

				}

				else

				{

					if (x == 3)

					{

						m_rcWnd[x + 4 * y] = CRect(x*nWidth, y*nHeight,

							rcWindow.Width(), (y + 1)*nHeight);

					}

					else

					{

						m_rcWnd[x + 4 * y] = CRect(x*nWidth,

							y*nHeight, (x + 1)*nWidth, (y + 1)*nHeight);

					}

				}

			}

		}
	}
}