#include "StdAfx.h"
#include "TMyView.h"
#include "ITool.h"


TMyView::TMyView(void)
{
    m_curTool = NULL;
}


TMyView::~TMyView(void)
{
}

LRESULT TMyView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
     switch(message){
        case WM_CREATE:
            {
                CPaintDC dc(m_wnd);
                CRect rect(0,0,3000,3000);
                m_MemDC.CreateCompatibleDC(NULL);
                m_MemBitmap.CreateCompatibleBitmap(&dc,rect.right-rect.left,rect.bottom-rect.top);
                CBitmap *pOldBit=m_MemDC.SelectObject(&m_MemBitmap);
            }
            break;
        case WM_COMMAND:
            if(CN_UPDATE_COMMAND_UI == lParam)
            {
                CCmdUI* pCmdUI = (CCmdUI*)wParam;
                BOOL isRadio = FALSE;
                if(NULL != m_curTool && pCmdUI->m_nID == m_curTool->GetMsgId())
                {
                    isRadio = TRUE;
                }
                pCmdUI->SetRadio(isRadio);
            }
            else if(ID_EDIT_UNDO == lParam)
            {
                ClearSelectSet();
                undo(this);
            }
            else if(ID_EDIT_REDO == lParam)
            {
                ClearSelectSet();
                redo(this);
            }
            else
            {
                OnToolSelected(LOWORD(wParam));
            }
            break;
        case WM_ERASEBKGND:
            break;
        case WM_PAINT:
            TGraph::OnPaint();
            break;
        default:
            if(NULL != m_curTool)
            {
                return m_curTool->WindowProc(this, message, wParam, lParam);
            }
            else
            {
                return FALSE;
            }
     }
    return TRUE;
}


void TMyView::OnToolSelected(int MsgId)
{
    map<int, ITool*>::iterator it = TLoadDll::m_MsgId2Tool.find(MsgId);
    if(TLoadDll::m_MsgId2Tool.end() == it)
    {
        return;
    }
    if(NULL != m_curTool)
    {
        m_curTool->cancelSelected(this);
    }
    m_curTool = it->second;
    m_curTool->cancelSelected(this);
}
