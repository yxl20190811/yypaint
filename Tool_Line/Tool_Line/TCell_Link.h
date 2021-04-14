#pragma once
#include "ICell.h"
#include <math.h>

class TCell_Link: public ICell
{
public:
    TCell_Link(void);
    ~TCell_Link(void);
private:
    int m_x1, m_y1, m_x2, m_y2;
    int m_OldX1, m_OldY1, m_OldX2, m_OldY2;
public:
    virtual void DragingCell(int oldX, int oldY, int x, int y, int type);
    void MoveCell(int x, int y){m_x2 = x;m_y2 = y;}
    void InitRect(int x1, int y1, int x2, int y2){m_x1 = x1;m_y1 = y1;m_x2 = x2;m_y2 = y2;}
    int GetLong(){return (m_x1-m_x2)*(m_x1-m_x2)+(m_y1-m_y2)*(m_y1-m_y2);}
public:
    virtual void OnPaint(CDC& dc);
    virtual void OnPaintSelect(CDC& dc);
public:
    virtual bool OverTest(int x, int y);
    virtual int OverHotTest(int x, int y, HCURSOR* curor);
    virtual bool InnerTest(int x1, int y1, int x2, int y2);
public:
    virtual void PreDragingCell(int type);
    virtual void CancelDragingCell(int type);
};

