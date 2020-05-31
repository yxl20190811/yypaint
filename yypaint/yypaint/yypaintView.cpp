
// yypaintView.cpp : CyypaintView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CyypaintView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CyypaintView 构造/析构

CyypaintView::CyypaintView()
{
	// TODO: 在此处添加构造代码

}

CyypaintView::~CyypaintView()
{
}

BOOL CyypaintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CyypaintView 绘制

void CyypaintView::OnDraw(CDC* /*pDC*/)
{
	CyypaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CyypaintView 打印


void CyypaintView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CyypaintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CyypaintView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CyypaintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CyypaintView 诊断

#ifdef _DEBUG
void CyypaintView::AssertValid() const
{
	CView::AssertValid();
}

void CyypaintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CyypaintDoc* CyypaintView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CyypaintDoc)));
	return (CyypaintDoc*)m_pDocument;
}
#endif //_DEBUG


// CyypaintView 消息处理程序
