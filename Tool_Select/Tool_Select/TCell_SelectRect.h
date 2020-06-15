#pragma once
#include "ICell.h"

class TCell_SelectRect: public ICell
{
    friend class TTool_Select;
public:
    TCell_SelectRect(void);
    ~TCell_SelectRect(void);
    virtual void OnPaint(CDC& dc);
private:
    int m_x1, m_y1, m_x2, m_y2;
};

