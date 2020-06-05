#include "StdAfx.h"
#include "TTool_Rectangle.h"
#include "resource.h"
#include "IGraph.h"


extern "C" __declspec(dllexport) ITool* CreateTool()
{
    static TTool_Rectangle obj;
    return &obj;
}

TTool_Rectangle::TTool_Rectangle(void)
{
    m_curCursor = NULL;
}


TTool_Rectangle::~TTool_Rectangle(void)
{
}

const char* TTool_Rectangle::GetUuid()
{
    return "{D61F7D36-B72D-4161-B3D8-1E2596CFACFA}";
}
HICON TTool_Rectangle::GetIcon()
{
    return AfxGetApp()->LoadIcon(IDI_ICON_RECTANFGLE);
}

LRESULT TTool_Rectangle::WindowProc(IGraph* graph, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
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
            m_curCursor = LoadCursor(NULL,IDC_ARROW);
        }
        SetCursor(m_curCursor);
        break;
    case WM_KEYDOWN:
            if(27 == wParam)//ESC被按下
            {
               cancelSelected(graph);
            }
            break;
    default:
        return FALSE;
    }
    return FALSE;
}


void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

void TTool_Rectangle::OnMouseMove(IGraph* graph, int x, int y)
{
    if(graph->GetNewCell() != &m_tmp)
    {
        return;
    }
    m_tmp.MoveCell(x, y);
    graph->RePaint();
}

void TTool_Rectangle::cancelSelected(IGraph* graph)
{
    if(graph->GetNewCell() != &m_tmp)
    {
        return;
    }
    m_curCursor = LoadCursor(NULL, IDC_ARROW);
    SetCursor(m_curCursor);
    ReleaseCapture();
    graph->SetNewCell(NULL);
    graph->RePaint();
}

void TTool_Rectangle::OnLButtonUp(IGraph* graph, int x, int y)
{
    if(graph->GetNewCell() != &m_tmp)
    {
        return;
    }
    cancelSelected(graph);

    if(m_tmp.GetWidth() < 10 || m_tmp.GetHeight() < 10)
    {
        return;
    }
    TCell_Rectangle* obj = new TCell_Rectangle();
    *obj = m_tmp;
    graph->AddNewCell2Graph(obj);
    graph->RePaint();
}

void TTool_Rectangle::OnLButtonDown(IGraph* graph, int x, int y)
{
    graph->ClearSelectSet();
    //设置鼠标形状为十字
    m_curCursor = LoadCursor(NULL, IDC_CROSS);
    SetCursor(m_curCursor);
    //主抓鼠标，是的鼠标移动到窗口外还可以得到消息
    //view->m_wnd->SetCapture();
    //添加临时的矩形
    m_tmp.InitRect(x,y,x,y);
    graph->SetNewCell(&m_tmp);
    graph->RePaint();
}
