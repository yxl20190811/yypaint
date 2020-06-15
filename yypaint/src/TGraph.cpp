#include "StdAfx.h"
#include "TGraph.h"
#include "ICell.h"

TGraph::TGraph()
{
    m_wnd = NULL;
    m_curDrawCell = NULL;
    m_IsInvalide = true;
}
void TGraph::SetWnd(CWnd* wnd)
{
    m_wnd = wnd;
}

TGraph::~TGraph(void)
{
}

void TGraph::RePaint()
{
    m_wnd->Invalidate();
    m_IsInvalide = true;

}

void TGraph::DrawGrid(CDC* pDC)
{
	CRect rect(0, 0, 3000,3000);
	COLORREF backColor = RGB(255, 255, 255);
	CBrush brush(backColor);
	pDC->FillRect(rect, &brush);
	
	CPen* pOldPen;
	CPen penDot;
	penDot.CreatePen(PS_DOT, 1, RGB(128, 128, 128));
	pOldPen = pDC->SelectObject(&penDot);
	
	for (int x = 50; x < rect.right; x += 50)
	{
		pDC->MoveTo(x, rect.top);
		pDC->LineTo(x, rect.bottom);
	}
	
	for (int y = 50; y < rect.bottom; y += 50)
	{
		pDC->MoveTo(rect.left, y);
		pDC->LineTo(rect.right, y);
	}
	
	pDC->SelectObject(pOldPen);
}

void TGraph::RealonPaint(CDC& dc)
{
    DrawGrid(&dc);
    for(TCellLst::iterator it =  m_CellList.begin();
        m_CellList.end() != it; ++it)
    {
        (*it)->OnPaint(dc);
    }
    for(TCellSet::iterator it =  m_SelectLst.begin();
        m_SelectLst.end() != it; ++it)
    {
        (*it)->OnPaintSelect(dc);
    }
    if(NULL != m_curDrawCell)
    {
        m_curDrawCell->OnPaint(dc);
        m_curDrawCell->OnPaintSelect(dc);
    }
}
void TGraph::OnPaint()
{
    if(m_IsInvalide)
    {
        m_IsInvalide = false;
        RealonPaint(m_MemDC);
    }
    CPaintDC dc(m_wnd);
    CRect rect;
    ::GetWindowRect(m_wnd->GetSafeHwnd(), rect);
    dc.BitBlt(0,0,rect.right-rect.left,rect.bottom-rect.top,&m_MemDC,0,0,SRCCOPY);
}

void TGraph::InsertSelectSet(ICell* cell)
{
    m_SelectLst.insert(cell);
}
void TGraph::ClearSelectSet()
{
    m_SelectLst.clear();
}
void TGraph::EraseSelectSet(ICell* cell)
{
    m_SelectLst.erase(cell);
}
ICell* TGraph::GetOnlySelectCell()
{
    if(1 != m_SelectLst.size())
    {
        return NULL;
    }
    return *(m_SelectLst.begin());
}


ICell* TGraph::OverTest(int x, int y)
{
    for(TCellLst::iterator it = m_CellList.begin();
        m_CellList.end() != it; ++it)
    {
        if((*it)->OverTest(x, y))
        {
            return *it;
        }
    }
    return NULL;
}
void TGraph::OverHotTest(int x, int y,
        int& type, ICell*& cell, HCURSOR* curor)
{
    for(TCellSet::iterator it = m_SelectLst.begin();
        m_SelectLst.end() != it; ++it)
    {
        cell = *it;
        type = cell->OverHotTest(x, y, curor);
        if( 0 != type)
        {
            return;
        }
    }
    type = 0;
    cell = 0;
    curor = 0;
}
void TGraph::SelectByRect(int x1, int y1, int x2, int y2)
{
    for(TCellLst::iterator it = m_CellList.begin();
        m_CellList.end() != it; ++it)
    {
        if((*it)->InnerTest(x1, y1, x2, y2))
        {
            m_SelectLst.insert(*it);
        }
    }
}
void TGraph::PreDragingSelectCell(int type)
{
     for(TCellSet::iterator it = m_SelectLst.begin();
        m_SelectLst.end() != it; ++it)
    {
        (*it)->PreDragingCell(type);
     }
}
void TGraph::CancelDragingSelectCell(int type)
{
     for(TCellSet::iterator it = m_SelectLst.begin();
        m_SelectLst.end() != it; ++it)
    {
        (*it)->CancelDragingCell(type);
     }
}

void TGraph::DragingSelectCell(int oldX, int oldY, int x, int y, int type)
{
    for(TCellSet::iterator it = m_SelectLst.begin();
        m_SelectLst.end() != it; ++it)
    {
        (*it)->DragingCell(oldX, oldY, x, y, type);
     }
}

void TGraph::SetNewCell(ICell* cell)
{
    m_curDrawCell = cell;
}
void TGraph::AddNewCell2Graph(ICell* cell)
{
    m_CellList.push_back(cell);
    m_curDrawCell = NULL;
}

ICell* TGraph::GetNewCell()
{
    return m_curDrawCell;
}