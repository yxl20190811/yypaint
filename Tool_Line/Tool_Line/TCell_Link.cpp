#include "StdAfx.h"
#include "TCell_Link.h"


TCell_Link::TCell_Link(void)
{
    m_x1 = 0;
    m_y1 = 0;
    m_x2 = 0;
    m_y2 = 0;
    m_OldX1 = 0;
    m_OldY1 = 0;
    m_OldX2 = 0;
    m_OldY2 = 0;
}


TCell_Link::~TCell_Link(void)
{
}

void TCell_Link::OnPaint(CDC& dc)
{
    dc.MoveTo(m_x1, m_y1);
    dc.LineTo(m_x2, m_y2);
}

void TCell_Link::OnPaintSelect(CDC& dc)
{
    dc.MoveTo(m_x1, m_y1);
    dc.LineTo(m_x2, m_y2);

    int d = 3;
    dc.Ellipse(m_x1-d, m_y1-d, m_x1+d, m_y1+d);
    dc.Ellipse(m_x2-d, m_y2-d, m_x2+d, m_y2+d);
}



bool TCell_Link::OverTest(int x, int y)
{
    if(x > m_x1)
    {
        if( x > m_x2)
        {
            return false;
        }
    }
    else
    {
        if( x < m_x2)
        {
            return false;
        }
    }

    if(y > m_y1)
    {
        if( y > m_y2)
        {
            return false;
        }
    }
    else
    {
        if( y < m_y2)
        {
            return false;
        }
    }
    return true;
}

inline bool InnerOverTest(int x1, int y1, int d, int x2, int y2)
{
    if(x1-d < x2 && x1+d > x2 
    && y1-d < y2 && y1+d > y2)
    {
        return true;
    }
    return false;
}


int TCell_Link::OverHotTest(int x, int y, HCURSOR* curor)
{
    int d = 5;
    int type = 0;
    if(InnerOverTest(m_x1, m_y1, d, x, y))
    {
        type =  HOT_LEFT_TOP;
        *curor = LoadCursor(NULL,IDC_SIZENESW);
    }
    if(InnerOverTest(m_x2, m_y2, d, x, y))
    {
        type =  HOT_RIGHT_TOP;
        *curor = LoadCursor(NULL,IDC_SIZENESW);
    }
    return type;
}


bool TCell_Link::InnerTest(int x1, int y1, int x2, int y2)
{
    if(x1 > x2)
    {
        int tmp = x1;
        x1 = x2;
        x2 = tmp;
    }
    if(y1 > y2)
    {
        int tmp = y1;
        y1 = y2;
        y2 = tmp;
    }

    if(x1 > m_x1 || x1 > m_x2  
     || y1 >m_y1 || y1 > m_y2
     || x2 < m_x1 || x2 < m_x2
     || y2 <m_y1 || y2 < m_y2
     )
    {
        return false;
    }
    return TRUE;
}

void TCell_Link::PreDragingCell(int type)
{
    m_OldX1 = m_x1;
    m_OldX2 = m_x2;
    m_OldY1 = m_y1;
    m_OldY2 = m_y2;
}
void TCell_Link::CancelDragingCell(int type)
{
    m_x1 = m_OldX1;
    m_y1 = m_OldY1;
    m_x2 = m_OldX2;
    m_y2 = m_OldY2;
}

void TCell_Link::DragingCell(int oldX, int oldY, int x, int y, int type)
{
    switch(type)
    {
    case 0:
        {
            m_x1 = m_OldX1 + x - oldX;
            m_y1 = m_OldY1 + y - oldY;
            m_x2 = m_OldX2 + x - oldX;
            m_y2 = m_OldY2 + y - oldY;
            break;
        }
    case HOT_LEFT_TOP:
        {
            m_x1 = x;
            m_y1 = y;
            break;
        }
    case HOT_RIGHT_TOP:
        {
            m_x2 = x;
            m_y2 = y;
            break;            
        }
    }
}