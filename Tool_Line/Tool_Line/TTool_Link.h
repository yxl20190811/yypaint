#pragma once
#include "ITool.h"
#include "TCell_Link.h"

class TTool_Link: public ITool
{
public:
    TTool_Link(void);
    ~TTool_Link(void);
public:
    virtual const char* GetUuid();
    virtual HICON GetIcon();
public:
    virtual LRESULT WindowProc(IGraph* graph, UINT message, WPARAM wParam, LPARAM lParam);
    virtual void cancelSelected(IGraph* graph);
    virtual ICell* CreateCell();
private:
    void OnLButtonDown(IGraph* graph, int x, int y);
    void OnLButtonUp(IGraph* graph, int x, int y);
    void OnMouseMove(IGraph* graph, int x, int y);
private:
    TCell_Link m_tmp;
    HCURSOR m_curCursor;
};

