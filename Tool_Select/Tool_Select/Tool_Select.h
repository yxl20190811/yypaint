// Tool_Select.h : Tool_Select DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTool_SelectApp
// �йش���ʵ�ֵ���Ϣ������� Tool_Select.cpp
//

class CTool_SelectApp : public CWinApp
{
public:
	CTool_SelectApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
