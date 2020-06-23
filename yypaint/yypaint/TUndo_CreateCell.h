#pragma once
#include "IUndo.h"
#include "IGraph.h"
#include "TGraph.h"
class ICell;

class TUndo_CreateCell: public IUndo
{
public:
    TUndo_CreateCell(ICell* cell, bool IsCreateOrDel)
    {
        m_cell = cell;
        m_IsCreateOrDel = IsCreateOrDel;
    }
    
public:
    ICell*  m_cell;
    bool    m_IsCreateOrDel;
public:
    void undo(TGraph* graph)
    {
        if(m_IsCreateOrDel)
        {
            graph->EraseCell(m_cell);
        }
        else
        {
            graph->AddNewCell(m_cell); 
        }
    };
    void redo(TGraph* graph)
    {
        if(m_IsCreateOrDel)
        
        {
            graph->AddNewCell(m_cell); 
        }
        else
        {
            graph->EraseCell(m_cell);
        }
    };
};

