#pragma once
#include <Windows.h>

class IGraph;
class ITool
{
public:
    virtual const char* GetUuid()=0;
    virtual HICON GetIcon()=0;
public:
    virtual LRESULT WindowProc(IGraph* graph, UINT message, WPARAM wParam, LPARAM lParam){return FALSE;};
    virtual void cancelSelected(IGraph* graph){};
public:
    int GetMsgId(){return m_MsgId;}
    void SetMsgId(int MsgId){m_MsgId = MsgId;}
public:
    ITool()
    {
        m_MsgId = -1;
    }
private:
    int m_MsgId;
};

