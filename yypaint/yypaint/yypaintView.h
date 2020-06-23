
// yypaintView.h : CyypaintView ��Ľӿ�
//

#pragma once

#include "TMyView.h"

class CyypaintView : public CView
{
protected: // �������л�����
	CyypaintView();
	DECLARE_DYNCREATE(CyypaintView)

// ����
public:
	CyypaintDoc* GetDocument() const;
    TMyView*  m_view;
// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CyypaintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // yypaintView.cpp �еĵ��԰汾
inline CyypaintDoc* CyypaintView::GetDocument() const
   { return reinterpret_cast<CyypaintDoc*>(m_pDocument); }
#endif

