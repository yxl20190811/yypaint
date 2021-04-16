#include "StdAfx.h"
#include "TCell_Rectangle.h"
#include "resource.h"
#include <math.h>
#include "GdiPlus.h"
using namespace Gdiplus;
#pragma comment( lib, "gdiplus.lib" )

#define PI 3.1415926535897f
template<typename T>
inline float GetAngle(const T& o, const T& s, const T& e) 
{ 
	float cosfi, norm; 
	float dsx = s.x - o.x; 
	float dsy = s.y - o.y; 
	float dex = e.x - o.x; 
	float dey = e.y - o.y; 
	
	cosfi = dsx * dex + dsy * dey; 
	norm = (dsx * dsx + dsy * dsy) * (dex * dex + dey * dey); 
	cosfi /= sqrt(norm); 
	
	if (cosfi >=  1.0 ) return 0; 
	if (cosfi <= -1.0 ) return PI; 
	
	return acos(cosfi); 
}


const TCell_Rectangle& TCell_Rectangle::operator=(const TCell_Rectangle& obj)
{
    m_x1 = obj.m_x1;
    m_x2 = obj.m_x2;
    m_y1 = obj.m_y1;
    m_y2 = obj.m_y2;
    m_rotAngle = 0;
    return obj;
}

void TCell_Rectangle::OnPaint(CDC& dc)
{
    Graphics gp(dc.m_hDC);
    CRect rect(m_x1, m_y1, m_x2, m_y2);
    
    gp.SetSmoothingMode(SmoothingModeAntiAlias);
    gp.TranslateTransform(m_centerPoint.x,m_centerPoint.y); //源点移动到旋转中心
    gp.RotateTransform(m_rotAngle); //旋转
    gp.TranslateTransform(-m_centerPoint.x, -m_centerPoint.y);//还原源点
    Gdiplus::Color c(Gdiplus::Color::Blue);
    Gdiplus::Pen pen(c, 3);
    gp.DrawRectangle(&pen, m_x1, m_y1, rect.Width(), rect.Height());

    /*
    CBrush brush;
    brush.CreateSolidBrush(RGB(184, 224, 230));
    dc.SelectObject(brush);

    CPen bluePen;
    bluePen.CreatePen(PS_SOLID, 1, RGB(10, 10, 10));
    dc.SelectObject(bluePen);
    dc.Rectangle(m_x1, m_y1, m_x2, m_y2);
    */
}

void TCell_Rectangle::OnPaintSelect(CDC& dc)
{
     Graphics gp(dc.m_hDC);
    CRect rect(m_x1, m_y1, m_x2, m_y2);
    gp.SetSmoothingMode(SmoothingModeAntiAlias);
    gp.TranslateTransform(m_centerPoint.x,m_centerPoint.y); //源点移动到旋转中心
    gp.RotateTransform(m_rotAngle); //旋转
    gp.TranslateTransform(-m_centerPoint.x, -m_centerPoint.y);//还原源点
    Gdiplus::Color c(Gdiplus::Color::Black);
    Gdiplus::Pen pen(c, 1);

    int d = 3;
    
    gp.DrawEllipse(&pen,m_x1-d, m_y1-d, d, d);
    gp.DrawEllipse(&pen,m_x1-d, m_y2-d, d, d);
    gp.DrawEllipse(&pen,m_x2-d, m_y1-d, d, d);
    gp.DrawEllipse(&pen,m_x2-d, m_y2-d, d, d);

    int x = (m_x1 + m_x2)/2;
    gp.DrawEllipse(&pen,x-d, m_y1-d, d, d);
    gp.DrawEllipse(&pen,x-d, m_y2-d, d, d);

    

    int y = (m_y1 + m_y2)/2;
    gp.DrawEllipse(&pen,m_x1-d, y-d, d, d);
    gp.DrawEllipse(&pen,m_x2-d, y-d, d, d);

    y = m_y1;
    if(m_y1 > m_y2)
    {
        y = m_y2;
    }
    gp.DrawLine(&pen, x,y, x, y - 20);
    gp.DrawEllipse(&pen, x-d, y-20-d, d, d);
    
}

inline bool InnerOverTest(int x1, int y1, int d, int x2, int y2)
{
    if(x1-d < x2 && x1+d > x2 
    && y1-d < y2 && y1+d > y2)
    {
        return true;
    }
    return false;
}

HCURSOR curorRatale = NULL;
#define ZERO 1E-5
#define FABS(v) ((v)>0?(v):(-v))

void TCell_Rectangle::RotatePoint(int &x, int &y, float angle)
{
    CPoint point(x,y);
	if (FABS(angle)<=ZERO)
		return;
	CPoint _point;
	CPoint delta = point - m_centerPoint;
	float theta = angle/180*PI;
	_point.x = delta.x*cos(theta)-delta.y*sin(theta)+0.5f;
	_point.y = delta.x*sin(theta)+delta.y*cos(theta)+0.5f;
	_point += m_centerPoint;
	
    x = _point.x;
    y = _point.y;
}

int TCell_Rectangle::OverHotTest(int x, int y, HCURSOR* curor)
{
    RotatePoint(x ,y, m_rotAngle*-1.0);

    int d = 5;
    int type = 0;
    if(InnerOverTest(m_x1, m_y1, d, x, y))
    {
        type =  HOT_LEFT_TOP;
        
    }
    else if(InnerOverTest(m_x1, m_y2, d, x, y))
    {
        type =  HOT_LEFT_BOTTOM;
    }
    else if(InnerOverTest(m_x2, m_y1, d, x, y))
    {
        *curor = LoadCursor(NULL,IDC_SIZENESW);
        type =  HOT_RIGHT_TOP;
    }
    else if(InnerOverTest(m_x2, m_y2, d, x, y))
    {
        type =  HOT_RIGHT_BOTTOM;
    }

    
    else if(InnerOverTest(m_x1, (m_y1+m_y2)/2, d, x, y))
    {
        type =  HOT_LEFT_CENTER;
    }
    else if(InnerOverTest(m_x2, (m_y1+m_y2)/2, d, x, y))
    {
        type =  HOT_RIGHT_CENTER;
    }
    else if(InnerOverTest((m_x1+m_x2)/2, m_y1, d, x, y))
    {
        type =  HOT_TOP_CENTER;
    }
    else if(InnerOverTest((m_x1+m_x2)/2, m_y2, d, x, y))
    {
        type =  HOT_BOTTOM_CENTER;
    }
    else if(InnerOverTest((m_x1+m_x2)/2, m_y1<m_y2?m_y1-20:m_y2-20, d, x, y))
    {
        type =  HOT_ROTALE;
    }

    int type1 = type;
    if(type1 >=1 && type1 <= 8)
    {
        float theta = m_rotAngle;	//保证鼠标形状是合理的
	    if (m_rotAngle < 0)
		    theta += 360;
	    type1 += (theta+22.5f)/45.0f;
	    type1 %= 8;
	    if (type1==0)
		    type1 = 8;
    }

    switch(type1)
    {
    case HOT_ROTALE:
        if(NULL == curorRatale)
        {
            curorRatale = AfxGetApp()->LoadCursor(IDC_CURSOR_ROTALE);
        }
        *curor = curorRatale;
        break;

    case HOT_LEFT_TOP:
    case HOT_RIGHT_BOTTOM:
        *curor = LoadCursor(NULL,IDC_SIZENWSE);
        break;
    case HOT_LEFT_BOTTOM:
    case HOT_RIGHT_TOP:
        *curor = LoadCursor(NULL,IDC_SIZENESW);
        break;
    case HOT_LEFT_CENTER:
    case HOT_RIGHT_CENTER:
        *curor = LoadCursor(NULL,IDC_SIZEWE);
        break;
    case HOT_TOP_CENTER:
    case HOT_BOTTOM_CENTER:
        *curor = LoadCursor(NULL,IDC_SIZENS);
        break;

    }
    return type;
}

bool TCell_Rectangle::InnerTest(int x1, int y1, int x2, int y2)
{
    if(x1 > x2)
    {
        int tmp = x1;
        x1 = x2;
        x2 = tmp;
    }
    if(y1 > y2)
    {
        int tmp = y1;
        y1 = y2;
        y2 = tmp;
    }

    if(x1 > m_x1 || x1 > m_x2  
     || y1 >m_y1 || y1 > m_y2
     || x2 < m_x1 || x2 < m_x2
     || y2 <m_y1 || y2 < m_y2
     )
    {
        return false;
    }
    return TRUE;
}

bool TCell_Rectangle::OverTest(int x, int y)
{
    RotatePoint(x ,y, m_rotAngle*-1.0);

    if(x > m_x1)
    {
        if( x > m_x2)
        {
            return false;
        }
    }
    else
    {
        if( x < m_x2)
        {
            return false;
        }
    }

    if(y > m_y1)
    {
        if( y > m_y2)
        {
            return false;
        }
    }
    else
    {
        if( y < m_y2)
        {
            return false;
        }
    }
    return true;
}

void TCell_Rectangle::PreDragingCell(int type)
{
    m_OldX1 = m_x1;
    m_OldX2 = m_x2;
    m_OldY1 = m_y1;
    m_OldY2 = m_y2;
}

void TCell_Rectangle::CancelDragingCell(int type)
{
    m_x1 = m_OldX1;
    m_y1 = m_OldY1;
    m_x2 = m_OldX2;
    m_y2 = m_OldY2;
}

void TCell_Rectangle::ResetCenterPoint()
{
    int x = (m_x1+m_x2)/2;
    int y = (m_y1+m_y2)/2;
    RotatePoint(x, y, m_rotAngle);
    int offsetX = x - (m_x1+m_x2)/2;
    int offsetY = y - (m_y1+m_y2)/2;

    m_x1 += offsetX;
    m_y1 += offsetY;

    m_x2 += offsetX;
    m_y2 += offsetY;

    
    m_centerPoint.x = x;
    m_centerPoint.y = y;
}

void TCell_Rectangle::Serialize(CArchive& ar)
{
    if(ar.IsStoring())
    {
        ar << CString("{D61F7D36-B72D-4161-B3D8-1E2596CFACFA}");
        int size = sizeof(TCell_Rectangle);
        ar << size-sizeof(int);
        ar.Write((char*)this+sizeof(int), size-sizeof(int));
        //ar << m_rotAngle << m_x1 << m_y1 << m_x1 << m_y2 << m_centerPoint;
    }
    else
    {
        int size = 0;
        ar >> size;
        if(size+sizeof(int) != sizeof(TCell_Rectangle))
        {
            abort();
        }
        ar.Read((char*)this+sizeof(int), size);
        //ar >> size >> m_rotAngle >> m_x1 >> m_y1 << m_x1 >> m_y2 >> m_centerPoint;
    }
}


void TCell_Rectangle::DragingCell(IGraph*, int oldX, int oldY, int x, int y, int type)
{
    
    switch(type)
    {
    case 0:
        {
            RotatePoint(x ,y, m_rotAngle*-1.0);
            RotatePoint(oldX ,oldY, m_rotAngle*-1.0);
            m_x1 = m_OldX1 + x - oldX;
            m_y1 = m_OldY1 + y - oldY;
            m_x2 = m_OldX2 + x - oldX;
            m_y2 = m_OldY2 + y - oldY;
            
        }
        break;

    case HOT_LEFT_TOP:
        {
            RotatePoint(x ,y, m_rotAngle*-1.0);
            m_x1 = x;
            m_y1 = y;
        }
        break;

    case HOT_LEFT_BOTTOM:
        {
            RotatePoint(x ,y, m_rotAngle*-1.0);
            m_x1 = x;
            m_y2 = y;
            
        }
        break;
    case HOT_RIGHT_TOP:
        {
            RotatePoint(x ,y, m_rotAngle*-1.0);
            m_x2 = x;
            m_y1 = y;
            
        }
        break;
    case HOT_RIGHT_BOTTOM:
        {
            RotatePoint(x ,y, m_rotAngle*-1.0);
            m_x2 = x;
            m_y2 = y;
            
        }
        break;
    

    case HOT_LEFT_CENTER:
        {
            RotatePoint(x ,y, m_rotAngle*-1.0);
            m_x1 = x;
            
        }
        break;
    
    case HOT_RIGHT_CENTER:
        {
            RotatePoint(x ,y, m_rotAngle*-1.0);
            m_x2 = x;
            
        }
        break;
    

    case HOT_TOP_CENTER:
        {
            RotatePoint(x ,y, m_rotAngle*-1.0);
            m_y1 = y;
            
        }
        break;
    
    case HOT_BOTTOM_CENTER:
        {
            RotatePoint(x ,y, m_rotAngle*-1.0);
            m_y2 = y;
            
        }
        break;
    
    case HOT_ROTALE:
        {
            if(0 == m_centerPoint.x && 0 == m_centerPoint.y)
            {
                m_centerPoint.x = (m_x1 + m_x2)/2;
                m_centerPoint.y = (m_y1 + m_y2)/2;
            }
            else
            {
                ResetCenterPoint();
            }
            CPoint handle(m_centerPoint.x, m_centerPoint.y-20);
            CPoint point(x, y);
	        float theta = GetAngle(m_centerPoint, handle, point)/PI*180;
	        if (point.x < m_centerPoint.x)
		        theta = -theta;
            m_rotAngle = theta;
        }
        break;
    }
}

