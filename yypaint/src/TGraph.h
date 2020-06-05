#pragma once
#include "IGraph.h"
#include <list>
using namespace std;

class TGraph: public IGraph
{
public:
    TGraph();
    ~TGraph(void);
    void SetWnd(CWnd* wnd);
public:
    virtual void RePaint();
    virtual void OnPaint();
public:
    virtual ICell* OverTest(int x, int y);
    virtual void OverHotTest(int x, int y,
        int& type, ICell*& cell, HCURSOR* curor);
public:
    virtual void SelectByRect(int x1, int y1, int x2, int y2);
    virtual void PreDragingSelectCell(int type);
    virtual void CancelDragingSelectCell(int type);
    virtual void DragingSelectCell(int x, int y, int type);
public:
    virtual ICell* GetNewCell();
    virtual void SetNewCell(ICell* cell);
    virtual void AddNewCell2Graph(ICell* cell);
protected:
    typedef  list<ICell*> TCellLst;
    TCellLst m_CellList;
    TCellLst  m_SelectLst;
    
    ICell*  m_curDrawCell;
    CWnd*   m_wnd;
    bool  m_IsInvalide;
protected:
    CDC m_MemDC; //首先定义一个显示设备对象
    CBitmap m_MemBitmap;//定义一个位图对象
private:
    void RealonPaint(CDC& dc);
    void DrawGrid(CDC* pDC);
};

