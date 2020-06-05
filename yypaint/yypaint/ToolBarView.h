
#pragma once

#include "ViewTree.h"
#include "TToolbar.h"


class CToolBarView : public CDockablePane
{
// 构造
public:
	CToolBarView();

// 特性
protected:
	TToolbar m_wndToolBar;

protected:
	void AdjustLayout();

// 实现
public:
	virtual ~CToolBarView();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
};

