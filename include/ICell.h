#pragma once
enum
{
    HOT_LEFT_TOP = 1,
    HOT_TOP_CENTER,
    HOT_RIGHT_TOP,
    HOT_RIGHT_CENTER,
    HOT_RIGHT_BOTTOM,
    HOT_BOTTOM_CENTER,
    HOT_LEFT_BOTTOM,
    HOT_LEFT_CENTER,
    
    HOT_ROTALE
};

class ICell
{
public:
    ICell()
    {
        static int MsgId = 1;
        ++MsgId;
        m_order = MsgId;
    }
    virtual ~ICell(void){}
public:
    virtual void OnPaint(CDC& dc){};
    virtual void OnPaintSelect(CDC& dc){};
public:
    virtual bool OverTest(int x, int y){return false;};
    virtual int OverHotTest(int x, int y, HCURSOR* curor){return 0;};
    virtual bool InnerTest(int x1, int y1, int x2, int y2){return false;};
public:
    virtual void PreDragingCell(int type){};
    virtual void DragingCell(int oldX, int oldY, int x, int y, int type){};
    virtual void CancelDragingCell(int type){};
private:
    int m_order;

    friend class ICellOderLess;
};

class ICellOderLess
{
public:
    bool operator()(ICell* obj1, ICell* obj2)const
    {
        return obj1->m_order < obj2->m_order;
    }
};
