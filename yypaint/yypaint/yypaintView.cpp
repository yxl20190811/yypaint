
// yypaintView.cpp : CyypaintView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "yypaint.h"
#endif

#include "yypaintDoc.h"
#include "yypaintView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CyypaintView

IMPLEMENT_DYNCREATE(CyypaintView, CView)

BEGIN_MESSAGE_MAP(CyypaintView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CyypaintView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CyypaintView ����/����

CyypaintView::CyypaintView()
{
	// TODO: �ڴ˴���ӹ������

}

CyypaintView::~CyypaintView()
{
}

BOOL CyypaintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CyypaintView ����

void CyypaintView::OnDraw(CDC* /*pDC*/)
{
	CyypaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CyypaintView ��ӡ


void CyypaintView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CyypaintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CyypaintView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CyypaintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CyypaintView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CyypaintView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CyypaintView ���

#ifdef _DEBUG
void CyypaintView::AssertValid() const
{
	CView::AssertValid();
}

void CyypaintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CyypaintDoc* CyypaintView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CyypaintDoc)));
	return (CyypaintDoc*)m_pDocument;
}
#endif //_DEBUG


// CyypaintView ��Ϣ�������
