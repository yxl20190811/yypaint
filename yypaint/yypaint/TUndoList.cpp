#include "StdAfx.h"
#include "TUndoList.h"
#include "TGraph.h"
#include "IUndo.h"
TUndoList::TUndoList(void)
{
}


TUndoList::~TUndoList(void)
{
}

void TUndoList::AddUndo(IUndo* undo)
{
    for(list<IUndo*>::iterator it =   m_RedoLst.begin();
        m_RedoLst.end() != it; ++it)
    {
        IUndo* undo = *it;
        delete undo;
    }
    m_RedoLst.clear();

    m_UndoLst.push_back(undo);
        
};
void TUndoList::undo(TGraph* graph)
{
    if(m_UndoLst.empty())
    {
        return;
    }
    IUndo* undo = m_UndoLst.back(); 
    m_UndoLst.pop_back(); 
    undo->undo(graph);
    m_RedoLst.push_back(undo);

    graph->RePaint();
}
void TUndoList::redo(TGraph* graph)
{
    if(m_RedoLst.empty())
    {
        return;
    }
    IUndo* undo = m_RedoLst.back(); 
    m_RedoLst.pop_back(); 
    undo->redo(graph);
    m_UndoLst.push_back(undo);

    graph->RePaint();
}