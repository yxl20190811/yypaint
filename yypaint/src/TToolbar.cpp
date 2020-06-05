#include "StdAfx.h"
#include "TToolbar.h"
#include "Resource.h"
#include "TLoadDll.h"
#include "ITool.h"

void TToolbar::SetColumns(UINT nColumns)
{
       m_nColumns = nColumns;
       int nCount = GetToolBarCtrl().GetButtonCount();
       for (int i = 0; i < nCount; i++)
       {
              UINT nStyle = GetButtonStyle(i);
              BOOL bWrap = (((i + 1) % nColumns) == 0);
              if (bWrap)
                     nStyle |= TBBS_WRAPPED;
              else
                     nStyle &= ~TBBS_WRAPPED;
              SetButtonStyle(i, nStyle);
       }
       Invalidate();
       GetParentFrame()->RecalcLayout();
}


BOOL TToolbar::Create(CWnd* pwnd)
{
    if(!CToolBar:: CreateEx(pwnd,
		TBSTYLE_FLAT, 
        WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_FLYBY|CBRS_SIZE_FIXED,
        CRect(0,0,0,0),
		AFX_IDW_TOOLBAR+2))
    {
       return -1;
    }
    
    if(!LoadToolBar(IDR_MAINFRAME))
    {
	    return -1;      // Î´ÄÜ´´½¨
    }
    int size = TLoadDll::m_Uuid2Tool.size();
    if(size <= 0)
    {
        return -1;
    }
    
    m_imgs.Create(32, 32, ILC_MASK | ILC_COLOR32, 2, 0);
   
    for(map<string, ITool*>::iterator it = TLoadDll::m_Uuid2Tool.begin();
            TLoadDll::m_Uuid2Tool.end() != it; ++it)
    {
        m_imgs.Add(it->second->GetIcon());
    }
    GetToolBarCtrl().SetImageList(&m_imgs);


    
    UINT* MsgId = new UINT[size+1];
    int pos = 0;
     for(map<string, ITool*>::iterator it = TLoadDll::m_Uuid2Tool.begin();
            TLoadDll::m_Uuid2Tool.end() != it; ++it)
    {
        MsgId[pos] = it->second->GetMsgId();
    }
    this->SetButtons(MsgId, size);
    
    pos = 0;
    for(map<string, ITool*>::iterator it = TLoadDll::m_Uuid2Tool.begin();
            TLoadDll::m_Uuid2Tool.end() != it; ++it)
    {
        this->SetButtonInfo(pos, MsgId[pos], TBBS_BUTTON, pos);
    }
    delete MsgId;
    
    //SetSizes(CSize(53, 53), CSize(46, 46));

    return TRUE;
}



