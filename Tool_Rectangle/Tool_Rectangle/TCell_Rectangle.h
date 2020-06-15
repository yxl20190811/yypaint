#pragma once
#include "ICell.h"


extern HCURSOR curorRatale;

class TCell_Rectangle: public ICell
{
private:
    float m_rotAngle;
    int m_x1, m_y1, m_x2, m_y2;
    int m_OldX1, m_OldY1, m_OldX2, m_OldY2;

    CPoint m_centerPoint;
public:
    void MoveCell(int x, int y){m_x2 = x;m_y2 = y;}
    virtual void DragingCell(int oldX, int oldY, int x, int y, int type);
public:
    const TCell_Rectangle& operator=(const TCell_Rectangle& obj);
    void InitRect(int x1, int y1, int x2, int y2){m_x1 = x1;m_y1 = y1;m_x2 = x2;m_y2 = y2;}
    int GetWidth(){return abs(m_x2 - m_x1);}
    int GetHeight(){return abs(m_y2 - m_y1);}
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
private:
    void DrawShape(CDC* pDC);
    void TranseAngle2Back(int& x, int& y);
    void RotatePoint(int &x, int &y, float angle);
    void ResetCenterPoint();
};

