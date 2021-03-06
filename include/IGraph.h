#pragma once
class ICell;
#include <list>
using namespace std;

class IGraph
{
public:
    virtual void RePaint(){};
public:
    virtual ICell* OverTest(int x, int y){return NULL;};
    virtual void OverHotTest(int x, int y,int& type, ICell*& cell, HCURSOR* curor){};
public:
    virtual void SelectByRect(int x1, int y1, int x2, int y2){};
    virtual void PreDragingSelectCell(int type){};
    virtual void CancelDragingSelectCell(int type){};
    virtual void DragingSelectCell(int oldX, int oldY, int x, int y, int type){};
    virtual void EndDragingSelectCell(int oldX, int oldY, int x, int y, int type){}
public:
    virtual void InsertSelectSet(ICell* cell){}
    virtual void ClearSelectSet(){}
    virtual void EraseSelectSet(ICell* cell){}
    virtual ICell* GetOnlySelectCell(){return NULL;}
public:
    virtual ICell* GetNewCell(){return NULL;}
    virtual void SetNewCell(ICell* cell){};
    virtual void AddNewCell2Graph(ICell* cell){};
    virtual void EraseCellFromGraph(ICell* cell){};
};