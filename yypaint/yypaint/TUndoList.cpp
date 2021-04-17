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

void TUndoList::AddUndo(list<IUndo*>& undo)
{
    for(list<list<IUndo*>>::iterator it1 =   m_RedoLst.begin();
        m_RedoLst.end() != it1; ++it1)
    {
        for(list<IUndo*>::iterator it =   it1->begin();
            it1->end() != it; ++it)
        {
            IUndo* undo = *it;
            delete undo;
        }
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
    list<IUndo*> undoLst = m_UndoLst.back(); 
    m_UndoLst.pop_back(); 

    for(list<IUndo*>::iterator it = undoLst.begin(); undoLst.end() != it; ++it)
    {
        (*it)->undo(graph);
    }
    m_RedoLst.push_back(undoLst);

    graph->RePaint();
}
void TUndoList::redo(TGraph* graph)
{
    if(m_RedoLst.empty())
    {
        return;
    }
    list<IUndo*> undoLst = m_RedoLst.back(); 
    m_RedoLst.pop_back(); 

    for(list<IUndo*>::iterator it = undoLst.begin(); undoLst.end() != it; ++it)
    {
        (*it)->redo(graph);
    }
    m_UndoLst.push_back(undoLst);

    graph->RePaint();
}