// comPort.h: interface for the comPort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPORT_H__3343C08E_8D85_11D1_9FD5_006008043EC4__INCLUDED_)
#define AFX_COMPORT_H__3343C08E_8D85_11D1_9FD5_006008043EC4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "definitions.h"

#include "mscommctrl.h"
#include "NSCommPortResource.h"



class DllExport CcomPort  
{
public:
	BOOL Terminate();
	CString WriteAndRead ( CString csTrigger, int nSecond );
	CString Read();
	BOOL Write ( CString csTrigger );
	BOOL Initialize ( int nPortType, 
							int nTriggerDelay,
							int nInputBufferSize,
							int nOutputBufferSize,
							int nPortID,
							CString csPortSettings,
						    BOOL blnDTREnable,
							BOOL blnRTSEnable,
							BOOL blnNULLDiscard);

	void SetTriggerDelay ( int nDelay );


	CcomPort();
	virtual ~CcomPort();


private:
	BOOL			m_bInitialized;				// Port initialized flag.
	CMSCommCtrl	m_oComControl;					// MSComm32 ocx interface.
	int			m_nPortType;					// Sub-system type.
	int			m_nTriggerDelay;				// Delay to wait after triggering.
	int			m_nPortID;						// Port ID.
	int			m_nInputBufferSize;			// Size of the port input buffer.
	int			m_nOutputBufferSize;			// Size of the port output buffer.
	CString		m_csPortSettings;				// Port settings. Baud rate, parity, ...

};

#endif // !defined(AFX_COMPORT_H__3343C08E_8D85_11D1_9FD5_006008043EC4__INCLUDED_)
