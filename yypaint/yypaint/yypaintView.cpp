
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
    ON_COMMAND_RANGE(0x0400, 0x0400+100,&CyypaintView::OnCommd)
    ON_UPDATE_COMMAND_UI_RANGE(0x0400, 0x0400+100,&CyypaintView::OnUpdateCommd)
END_MESSAGE_MAP()

// CyypaintView ����/����

CyypaintView::CyypaintView()
{
	// TODO: �ڴ˴���ӹ������
    m_view = NULL;
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




void CyypaintView::OnCommd(UINT  id)
{   
    m_view->WindowProc(WM_COMMAND, id, 0);
}
void CyypaintView::OnUpdateCommd(CCmdUI* p)
{
    m_view->WindowProc(WM_COMMAND, (DWORD)p, CN_UPDATE_COMMAND_UI);
}

LRESULT CyypaintView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    // TODO: �ڴ����ר�ô����/����û���
    if(NULL != m_view && TRUE == m_view->WindowProc(message, wParam, lParam))
    {
        return TRUE;
    }
    BOOL ret = CView::WindowProc(message, wParam, lParam);
    if(WM_CREATE == message)
    {
        m_view = &(GetDocument()->m_view);
        m_view->SetWnd(this);
        m_view->WindowProc(message, wParam, lParam);
    }
    return ret;
}
