#pragma once
#include <list>
class IUndo;
class TGraph;
using namespace std;


class TUndoList
{
public:
    TUndoList(void);
    ~TUndoList(void);
public:
    void AddUndo(IUndo* undo);
    void undo(TGraph* graph);
    void redo(TGraph* graph);
private:
    list<IUndo*>  m_UndoLst;
    list<IUndo*>  m_RedoLst;
};

