// Tool_Rectangle.h : Tool_Rectangle DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CTool_RectangleApp
// 有关此类实现的信息，请参阅 Tool_Rectangle.cpp
//

class CTool_RectangleApp : public CWinApp
{
public:
	CTool_RectangleApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
