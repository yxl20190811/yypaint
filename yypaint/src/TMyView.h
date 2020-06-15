#pragma once
#include "TGraph.h"
#include "TLoadDll.h"

class ITool;
class TMyView: public TGraph
{
public:
    TMyView(void);
    ~TMyView(void);
public:
    LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
private:
    void OnToolSelected(int MsgId);
private:
    ITool*  m_curTool;
};

