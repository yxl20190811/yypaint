// Tool_Rectangle.h : Tool_Rectangle DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTool_RectangleApp
// �йش���ʵ�ֵ���Ϣ������� Tool_Rectangle.cpp
//

class CTool_RectangleApp : public CWinApp
{
public:
	CTool_RectangleApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
