#pragma once
#include <map>
#include <string>
using namespace std;
class ITool;

class TLoadDll
{
    friend class TLoad;
    friend class TToolbar;
    friend class TMyView;
    friend class TGraph;
protected:
    static map<int, ITool*> m_MsgId2Tool;
    static map<string, ITool*> m_Uuid2Tool;
};

