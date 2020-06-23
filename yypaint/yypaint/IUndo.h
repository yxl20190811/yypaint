#pragma once;
class TGraph;
class IUndo
{
public:
    IUndo(void){};
    virtual ~IUndo(void){};
    virtual void undo(TGraph* graph){};
    virtual void redo(TGraph* graph){};
};

