// 3Dpoint.cpp: implementation of the C3Dpoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "pacs.h"
#include "3Dpoint.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C3Dpoint::C3Dpoint()
{

}

C3Dpoint::~C3Dpoint()
{

}

void C3Dpoint::RotateAboutY(double nRadians)
{
	long nHypothenuse = (long)sqrt(pow(m_nXval,2) + pow(m_nYval,2));

	m_nXval = (int)acos(nRadians)*nHypothenuse;
	m_nZval = (int)asin(nRadians)*nHypothenuse;
}


void C3Dpoint::RotateAboutX(double nRadians)
{
	long nHypothenuse = (long)sqrt(pow(m_nYval,2) + pow(m_nZval,2));

	m_nZval = (int)asin(nRadians)/nHypothenuse;
	m_nYval = (int)acos(nRadians)/nHypothenuse;
}


int C3Dpoint::GetScreenX()
{
	return(m_nXval-m_nZval);
}

int C3Dpoint::GetScreenY()
{
//	return(m_nYval +( (asin(0.785398)*m_nXval) + (asin(0.785398)*m_nZval) ) );
	return (int)(m_nYval +( (asin(0.5)*m_nXval) + (asin(0.5)*m_nZval) ) );

}
