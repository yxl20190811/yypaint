#include "StdAfx.h"
#include "TUndo_EndDrag.h"
#include "ICell.h"

TUndo_EndDrag::TUndo_EndDrag(std::set<ICell*>& lst, int oldX, int oldY, int x, int y, int type)
{
    m_lst = lst;
    m_OldX = oldX;
    m_OldY = oldY;
    m_x = x;
    m_y = y;
    m_type = type;
}


TUndo_EndDrag::~TUndo_EndDrag(void)
{
}

void TUndo_EndDrag::undo(TGraph* graph)
{
    for(std::set<ICell*>::iterator it = m_lst.begin(); 
        m_lst.end() != it; ++it)
    {
        ICell* cell =  *it;
        cell->PreDragingCell(m_type);
        cell->DragingCell(m_x, m_y, m_OldX, m_OldY, m_type);
    }
}


void TUndo_EndDrag::redo(TGraph* graph)
{
    for(std::set<ICell*>::iterator it = m_lst.begin(); 
        m_lst.end() != it; ++it)
    {
        ICell* cell =  *it;
        cell->PreDragingCell(m_type);
        cell->DragingCell(m_OldX, m_OldY, m_x, m_y, m_type);
    }
}