// Tool_Line.h : Tool_Line DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTool_LineApp
// �йش���ʵ�ֵ���Ϣ������� Tool_Line.cpp
//

class CTool_LineApp : public CWinApp
{
public:
	CTool_LineApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
