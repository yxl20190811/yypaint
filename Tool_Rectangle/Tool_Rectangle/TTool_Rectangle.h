#pragma once
#include "ITool.h"
class TTool_Rectangle: public ITool
{
public:
    TTool_Rectangle(void);
    ~TTool_Rectangle(void);
public:
    virtual const char* GetUuid();
    virtual HICON GetIcon();
public:
    virtual LRESULT WindowProc(IGraph* graph, UINT message, WPARAM wParam, LPARAM lParam);
    virtual void cancelSelected(IGraph* graph);
};

