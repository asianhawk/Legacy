// 3Dpoint.h: interface for the C3Dpoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_3DPOINT_H__1B3DFC63_6847_11D4_9026_00105A170700__INCLUDED_)
#define AFX_3DPOINT_H__1B3DFC63_6847_11D4_9026_00105A170700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class C3Dpoint  
{
public:
	int GetScreenY();
	int GetScreenX();
	void RotateAboutX(double nRadians);
	void RotateAboutY(double nRadians);
	int m_nZval;
	int m_nYval;
	int m_nXval;
	C3Dpoint();
	virtual ~C3Dpoint();

};

#endif // !defined(AFX_3DPOINT_H__1B3DFC63_6847_11D4_9026_00105A170700__INCLUDED_)
