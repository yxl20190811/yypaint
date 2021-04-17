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
    void AddUndo(list<IUndo*>& undo);
    void undo(TGraph* graph);
    void redo(TGraph* graph);
private:
    list<list<IUndo*>>  m_UndoLst;
    list<list<IUndo*>>  m_RedoLst;
};

