#include "StdAfx.h"
#include "TLoadDll.h"
#include <set>
#include <ITool.h>


map<int, ITool*> TLoadDll::m_MsgId2Tool;
map<string, ITool*> TLoadDll::m_Uuid2Tool;

static set<HMODULE> DllLst;
void FindFile(char* path, char* flitter, set<string>& ret)
{
    
    

    HANDLE hFile = INVALID_HANDLE_VALUE; 
	WIN32_FIND_DATA pNextInfo; 
    
    char tmp1[MAX_PATH];
    sprintf(tmp1, "%s\\%s",  path, flitter);
    hFile = FindFirstFile(tmp1,&pNextInfo); 
    
	if(INVALID_HANDLE_VALUE == hFile)  
	{  
		return;  
	}
    do 
	{  
		if(pNextInfo.cFileName[0] == '.')
		{
			continue;  
		}
        if(pNextInfo.cFileName[0] == '..')
		{
			continue;  
		}
        char tmp[MAX_PATH];
        sprintf(tmp, "%s\\%s",  path, pNextInfo.cFileName);

        if((pNextInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) !=0)
        {
            FindFile(tmp, flitter, ret);
            continue;
        }
        //if((pNextInfo.dwFileAttributes & FILE_ATTRIBUTE_NORMAL) !=0)
        {
            ret.insert(tmp);
        }
	}while(FindNextFile(hFile,&pNextInfo));
}


static class TLoad
{
public:
    ~TLoad()
    {
        for(set<HMODULE>::iterator it = DllLst.begin();
            DllLst.end() != it; ++it)
        {
            ::FreeLibrary(*it);
        }
        DllLst.clear();
    }
    TLoad()
    {
        char path[MAX_PATH];
        ::GetModuleFileName(0, path, sizeof(path));
        char* pos = strrchr(path, '\\');
        strcpy(pos, "\\tools");

        set<string> filenameSet;
        FindFile(path, "*.dll", filenameSet);

        int MsgId = WM_USER+1;
        for(set<string>::iterator it = filenameSet.begin();
            filenameSet.end() != it; ++it)
        {
            ITool* tool = load(it->c_str());
            if(NULL== tool)
            {
                continue;
            }
            tool->SetMsgId(MsgId);
            TLoadDll::m_Uuid2Tool[tool->GetUuid()] = tool;
            TLoadDll::m_MsgId2Tool[MsgId] = tool;
            MsgId++;
        }
    }
    ITool* load(const char* FileName)
    {
        if(NULL == FileName)
        {
            return NULL;
        }
        HMODULE h = ::LoadLibrary(FileName);
        if(NULL == h)
        {
            return NULL;
        }
        DllLst.insert(h);
        typedef ITool*  (*CreateToolType)();
        CreateToolType fun = (CreateToolType)::GetProcAddress(h, "CreateTool");
        if(fun == NULL)
        {
            return NULL;
        }
        ITool *tool = fun();

        return tool;
    }
}GlobLoad;

