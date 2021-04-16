#pragma once
#include "ICell.h"
#include <math.h>
class IGraph;

class TCell_Link: public ICell
{
public:
    TCell_Link(void);
    ~TCell_Link(void);
private:
    int m_x1, m_y1, m_x2, m_y2;
    int m_OldX1, m_OldY1, m_OldX2, m_OldY2;
public:
    virtual void DragingCell(IGraph* graph, int oldX, int oldY, int x, int y, int type);
    void MoveCell(IGraph* graph, int x, int y){m_x2 = x;m_y2 = y;m_IsMove=true;}
    void InitRect(int x1, int y1, int x2, int y2){m_x1 = x1;m_y1 = y1;m_x2 = x2;m_y2 = y2; m_aEnd = NULL; m_zEnd = NULL;}
    int GetLong(){return (m_x1-m_x2)*(m_x1-m_x2)+(m_y1-m_y2)*(m_y1-m_y2);}
public:
    virtual void Serialize(CArchive& ar);
    virtual void OnPaint(CDC& dc);
    virtual void OnPaintSelect(CDC& dc);
public:
    virtual bool OverTest(int x, int y);
    virtual int OverHotTest(int x, int y, HCURSOR* curor);
    virtual bool InnerTest(int x1, int y1, int x2, int y2);
public:
    virtual void PreDragingCell(int type);
    virtual void CancelDragingCell(int type);
public:
    int m_OffsetX1, m_OffsetY1, m_OffsetX2, m_OffsetY2;
    ICell  *m_aEnd, *m_zEnd;
    bool m_IsMove;
public:
    void AdjustPos();
    void adjustEndA(IGraph* graph);
    void adjustEndZ(IGraph* graph);
};

