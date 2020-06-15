#include "StdAfx.h"
#include "TCell_SelectRect.h"


TCell_SelectRect::TCell_SelectRect(void)
{
    m_x1 = 0;
    m_y1 = 0;
    m_x2 = 0;
    m_y2 = 0;
}


TCell_SelectRect::~TCell_SelectRect(void)
{
}

void TCell_SelectRect::OnPaint(CDC& dc)
{
    CRect rect(m_x1, m_y1, m_x2, m_y2);
	rect.NormalizeRect();
	dc.DrawFocusRect(rect);
}