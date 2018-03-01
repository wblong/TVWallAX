// TVWallAXPropPage.cpp : CTVWallAXPropPage 属性页类的实现。

#include "stdafx.h"
#include "TVWallAX.h"
#include "TVWallAXPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CTVWallAXPropPage, COlePropertyPage)

// 消息映射

BEGIN_MESSAGE_MAP(CTVWallAXPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CTVWallAXPropPage, "TVWALLAX.TVWallAXPropPage.1",
	0x8a6d9234, 0x171a, 0x4b37, 0x95, 0x2e, 0x26, 0x59, 0x82, 0x95, 0x2e, 0xed)

// CTVWallAXPropPage::CTVWallAXPropPageFactory::UpdateRegistry -
// 添加或移除 CTVWallAXPropPage 的系统注册表项

BOOL CTVWallAXPropPage::CTVWallAXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_TVWALLAX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

// CTVWallAXPropPage::CTVWallAXPropPage - 构造函数

CTVWallAXPropPage::CTVWallAXPropPage() :
	COlePropertyPage(IDD, IDS_TVWALLAX_PPG_CAPTION)
{
}

// CTVWallAXPropPage::DoDataExchange - 在页和属性间移动数据

void CTVWallAXPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CTVWallAXPropPage 消息处理程序
