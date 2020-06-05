#pragma once
#include "afxtoolbar.h"
#include "TLoadDll.h"

class TToolbar:public CToolBar
{
private:
    int m_nColumns;
    CImageList m_imgs;
public:
    void SetColumns(UINT nColumns);
    BOOL Create(CWnd* pwnd);
};

