#pragma once
#include "ITool.h"
#include "TCell_Rectangle.h"
class TTool_Rectangle: public ITool
{
public:
    TTool_Rectangle(void);
    ~TTool_Rectangle(void);
public:
    virtual const char* GetUuid();
    virtual HICON GetIcon();
public:
    virtual LRESULT WindowProc(IGraph* graph, UINT message, WPARAM wParam, LPARAM lParam);
    virtual void cancelSelected(IGraph* graph);
private:
    void OnLButtonDown(IGraph* graph, int x, int y);
    void OnLButtonUp(IGraph* graph, int x, int y);
    void OnMouseMove(IGraph* graph, int x, int y);
private:
    TCell_Rectangle m_tmp;
    HCURSOR m_curCursor;
};

