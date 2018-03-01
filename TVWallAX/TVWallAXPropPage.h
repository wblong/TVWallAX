#pragma once

// TVWallAXPropPage.h : CTVWallAXPropPage 属性页类的声明。


// CTVWallAXPropPage : 有关实现的信息，请参阅 TVWallAXPropPage.cpp。

class CTVWallAXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CTVWallAXPropPage)
	DECLARE_OLECREATE_EX(CTVWallAXPropPage)

// 构造函数
public:
	CTVWallAXPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_TVWALLAX };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

