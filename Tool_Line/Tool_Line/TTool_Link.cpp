#include "StdAfx.h"
#include "TTool_Link.h"
#include "resource.h"
#include "TCell_Link.h"
#include "IGraph.h"

extern "C" __declspec(dllexport) ITool* CreateTool()
{
    static TTool_Link obj;
    return &obj;
}

TTool_Link::TTool_Link(void)
{
}


TTool_Link::~TTool_Link(void)
{
}
const char* TTool_Link::GetUuid()
{
    return "{348E6D46-9E63-4C27-8242-9AEB88818566}";
}

HICON TTool_Link::GetIcon()
{
    return AfxGetApp()->LoadIcon(IDI_ICON_LINK);
}

ICell* TTool_Link::CreateCell()
{
    return new TCell_Link();
}
void TTool_Link::cancelSelected(IGraph* graph)
{
}
LRESULT TTool_Link::WindowProc(IGraph* graph, UINT message, WPARAM wParam, LPARAM lParam)
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
            m_curCursor = LoadCursor(NULL,IDC_CROSS);
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

void TTool_Link::OnLButtonDown(IGraph* graph, int x, int y)
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
void TTool_Link::OnLButtonUp(IGraph* graph, int x, int y)
{
    if(graph->GetNewCell() != &m_tmp)
    {
        return;
    }
    cancelSelected(graph);

    if(m_tmp.GetLong() < 10)
    {
        return;
    }
    TCell_Link* obj = new TCell_Link();
    *obj = m_tmp;
    graph->AddNewCell2Graph(obj);
    graph->RePaint();
}

void TTool_Link::OnMouseMove(IGraph* graph, int x, int y)
{
    if(graph->GetNewCell() != &m_tmp)
    {
        return;
    }
    m_tmp.MoveCell(x, y);
    graph->RePaint();
}