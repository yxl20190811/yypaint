#include "StdAfx.h"
#include "TTool_Rectangle.h"
#include "resource.h"

TTool_Rectangle::TTool_Rectangle(void)
{
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
    return FALSE;
}
void TTool_Rectangle::cancelSelected(IGraph* graph)
{
};

extern "C" __declspec(dllexport) ITool* CreateTool()
{
    static TTool_Rectangle obj;
    return &obj;
}

