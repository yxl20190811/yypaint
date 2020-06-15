#include "StdAfx.h"
#include "TTool_Select.h"
#include "Resource.h"
#include "IGraph.h"
#include "ICell.h"
#include "TCell_SelectRect.h"


extern "C" __declspec(dllexport) ITool* CreateTool()
{
    static TTool_Select obj;
    return &obj;
}


TTool_Select::TTool_Select(void)
{
    m_curCursor = NULL;
    m_hotType = 0;
    m_state = UNKNOWN;
    m_arrowCuror = LoadCursor(NULL,IDC_ARROW);
    m_curorRatale = AfxGetApp()->LoadCursor(IDC_CURSOR_ROTALE);
}


TTool_Select::~TTool_Select(void)
{
}

HICON TTool_Select::GetIcon()
{
    return AfxGetApp()->LoadIcon(IDI_ICON_SELECT);
}
void TTool_Select::cancelSelected(IGraph* graph)
{
    m_state = UNKNOWN;
    m_hotType = 0;
    graph->ClearSelectSet();
    graph->SetNewCell(NULL);
    m_curCursor = m_arrowCuror;
    SetCursor(m_curCursor);
    graph->RePaint();
}

void TTool_Select::KEY_DOWN_ESC(IGraph* graph)
{
    m_state = UNKNOWN;
    m_hotType = 0;
    graph->SetNewCell(NULL);
    graph->ClearSelectSet();
    graph->RePaint();
    m_curCursor = m_arrowCuror;
    SetCursor(m_curCursor);
}

//单选一个图形
//画虚线框，选择被虚线框包含的多个图形
//拖动图形
//鼠标经过被选中的图形的热点
//拖动图形的热点
//取消一个图形的选择
//取消所有图形的选择

LRESULT TTool_Select::WindowProc(IGraph* graph, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
    case WM_LBUTTONDBLCLK:
        OnLButtonDbClick(graph, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;
    case WM_LBUTTONDOWN:
        OnLButtonDown(graph, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;
    case WM_LBUTTONUP:
        OnLButtonUp(graph, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;
    case WM_MOUSEMOVE:
        OnMouseMove(graph, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;
    case WM_SETCURSOR:
        if(NULL == m_curCursor)
        {
            m_curCursor = m_arrowCuror;
        }
        SetCursor(m_curCursor);
        break;
    case WM_KEYDOWN:
            if(27 == wParam)//ESC被按下
            {
               
               if(m_state == DRAGING_SELCT || m_state == DRAGING_HOT)
               {
                   graph->CancelDragingSelectCell(m_hotType);
               }
               m_curCursor = m_arrowCuror;
               SetCursor(m_curCursor);
               m_state = UNKNOWN;
               graph->SetNewCell(NULL);
               graph->RePaint();
               
            }
            break;
    default:
        return FALSE;
    }
    return TRUE;
}

void TTool_Select::OnLButtonDbClick(IGraph* graph, int x, int y)
{
    ICell* cell = graph->OverTest(x, y);
    if(NULL != cell)
    {
        graph->EraseSelectSet(cell);
    }
    else
    {
        graph->ClearSelectSet();
    }
    m_state = UNKNOWN;
    graph->RePaint();
}

void TTool_Select::OnLButtonDown(IGraph* graph, int x, int y)
{
    graph->RePaint();
    graph->SetNewCell(NULL);
    ICell* cell = graph->OverTest(x, y);
    if(NULL != cell)
    {
        graph->InsertSelectSet(cell);
       
    }

    int type = 0;
    HCURSOR curor;

    ICell* cell_tmp = graph->GetOnlySelectCell();
    if(NULL != cell_tmp)
    {
       type = cell_tmp->OverHotTest(x, y, &curor);
    }
    
    if(0 == type && NULL == cell)
    {
        m_state = DRAW_SELECT_RECT;
        m_TmpCell.m_x1 = x;
        m_TmpCell.m_y1 = y;
        m_TmpCell.m_x2 = x;
        m_TmpCell.m_y2 = y;
        graph->SetNewCell(&m_TmpCell);
        //m_SelectSet = lst;
        m_curCursor = m_arrowCuror;
        SetCursor(m_curCursor);
        return;
        
    }

    graph->PreDragingSelectCell(type);
    m_StartMoveX = x;
    m_StartMoveY = y;
    m_hotType = type;

    if(type > 0)
    {
        m_state = DRAGING_HOT;
        //设置鼠标形状为
        if(HOT_ROTALE == m_hotType)
        {
            m_curCursor = m_curorRatale;
        }
        else
        {
            m_curCursor = LoadCursor(NULL, IDC_CROSS);
        }
        SetCursor(m_curCursor);
    }
    else
    {
        m_state = DRAGING_SELCT;
        //设置鼠标形状为“手”
        m_curCursor = LoadCursor(NULL, IDC_SIZEALL);
        SetCursor(m_curCursor);
    }
    
}

void TTool_Select::OnLButtonUp(IGraph* graph, int x, int y)
{
    if(m_state == DRAW_SELECT_RECT)
    {
        graph->SelectByRect(m_TmpCell.m_x1, m_TmpCell.m_y1, m_TmpCell.m_x2, m_TmpCell.m_y2);
    }
    if(m_state == DRAGING_HOT)
    {
        //graph->DragingSelectCell(m_StartMoveX, m_StartMoveY, x, y, m_hotType);
    }
    m_curCursor = m_arrowCuror;
    SetCursor(m_curCursor);
    m_state = UNKNOWN;
    graph->SetNewCell(NULL);
    graph->RePaint();
}

void TTool_Select::OnMouseMove(IGraph* graph, int x, int y)
{
    switch(m_state)
    {
    case DRAW_SELECT_RECT:
        m_TmpCell.m_x2 = x;
        m_TmpCell.m_y2 = y;
        graph->RePaint();
        break;
    case DRAGING_SELCT:
    case DRAGING_HOT:
        graph->DragingSelectCell(m_StartMoveX, m_StartMoveY, x, y, m_hotType);
        graph->RePaint();
        break;
    default: //判断鼠标是否在热点上， 设置相应的形状
        {
            ICell* cell = NULL;
            int type = 0;
            HCURSOR curor;
            graph->OverHotTest(x, y, type, cell, &curor);
            if(NULL != cell)
            {
                m_curCursor = curor;
                SetCursor(m_curCursor);
            }
            else
            {
                if(m_arrowCuror != m_curCursor)
                {
                    m_curCursor = m_arrowCuror;
                    SetCursor(m_curCursor);
                }
            }
        }
        break;
    }
}


