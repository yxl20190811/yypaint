#pragma once
class TGraph;
class ICell;
#include "IUndo.h"
#include <set>

class TUndo_EndDrag: public IUndo
{
public:
    TUndo_EndDrag(std::set<ICell*>& lst, int oldX, int oldY, int x, int y, int type);
    ~TUndo_EndDrag(void);
    void undo(TGraph* graph);
    void redo(TGraph* graph);
private:
    std::set<ICell*> m_lst;
private:
    int m_OldX, m_OldY, m_x, m_y, m_type;
};

