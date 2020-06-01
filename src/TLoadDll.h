#pragma once
#include <map>
#include <string>
using namespace std;
class ITool;

class TLoadDll
{
public:
    static map<int, ITool*> m_MsgId2Tool;
    static map<string, ITool*> m_Uuid2Tool;
};

