
// yypaintView.h : CyypaintView 类的接口
//

#pragma once

#include "TMyView.h"

class CyypaintView : public CView
{
protected: // 仅从序列化创建
	CyypaintView();
	DECLARE_DYNCREATE(CyypaintView)

// 特性
public:
	CyypaintDoc* GetDocument() const;
    TMyView*  m_view;
// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CyypaintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnCommd(UINT  id);
    afx_msg void OnUpdateCommd(CCmdUI* p);
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    afx_msg void OnEditUndo();
    afx_msg void OnEditRedo();
};

#ifndef _DEBUG  // yypaintView.cpp 中的调试版本
inline CyypaintDoc* CyypaintView::GetDocument() const
   { return reinterpret_cast<CyypaintDoc*>(m_pDocument); }
#endif

