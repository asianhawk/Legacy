// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__AD710750_9E4A_11D2_A2AB_006008043EC4__INCLUDED_)
#define AFX_STDAFX_H__AD710750_9E4A_11D2_A2AB_006008043EC4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxtempl.h>

#include <afxcoll.h>
#include "simulationconstants.h"



#pragma warning(disable: 4275)
#pragma warning(disable: 4251) 


//#define SIMULATION	SIMULATEPRINTER|SIMULATELABELSCANNER|SIMULATEDIOCONTROLLER|SIMULATEPCBASEDCONTROLLER

//#define SIMULATION	SIMULATEPRINTER|SIMULATELABELSCANNER|SIMULATEDIOCONTROLLER

//#define SIMULATION	SIMULATEPRINTER|SIMULATELABELSCANNER

//#define SIMULATION	SIMULATELABELSCANNER

//#define SIMULATION 0


#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC OLE automation classes
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC socket extensions

// This macro is the same as IMPLEMENT_OLECREATE, except it passes TRUE
//  for the bMultiInstance parameter to the COleObjectFactory constructor.
//  We want a separate instance of this application to be launched for
//  each OLE automation proxy object requested by automation controllers.
#ifndef IMPLEMENT_OLECREATE2
#define IMPLEMENT_OLECREATE2(class_name, external_name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
	AFX_DATADEF COleObjectFactory class_name::factory(class_name::guid, \
		RUNTIME_CLASS(class_name), TRUE, _T(external_name)); \
	const AFX_DATADEF GUID class_name::guid = \
		{ l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } };
#endif // IMPLEMENT_OLECREATE2

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__AD710750_9E4A_11D2_A2AB_006008043EC4__INCLUDED_)
