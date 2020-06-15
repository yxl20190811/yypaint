#pragma once
#include "ITool.h"
#include <set>
#include <list>
#include "TCell_SelectRect.h"

using namespace std;

enum
{
    UNKNOWN,
    DRAW_SELECT_RECT,
    DRAGING_SELCT,
    DRAGING_HOT
};

class TTool_Select: public ITool
{
public:
    TTool_Select(void);
    ~TTool_Select(void);
public:
    virtual const char* GetUuid(){return "{EEEAE43F-7229-4C76-AE48-72CFDF949F8E}";}
    virtual HICON GetIcon();
    virtual void cancelSelected(IGraph* graph);
    virtual LRESULT WindowProc(IGraph* graph, UINT message, WPARAM wParam, LPARAM lParam);
private:
    void KEY_DOWN_ESC(IGraph* graph);
    void OnLButtonDbClick(IGraph* graph, int x, int y);
    void OnLButtonDown(IGraph* graph, int x, int y);
    void OnLButtonUp(IGraph* graph, int x, int y);
    void OnMouseMove(IGraph* graph, int x, int y);
private:
    HCURSOR m_curCursor;
    HCURSOR m_arrowCuror;
    int m_hotType;
    int m_state;
    int m_StartMoveX, m_StartMoveY;
    TCell_SelectRect m_TmpCell;
    list<ICell*>  m_SelectSet;
    HCURSOR m_curorRatale;
};

