// Database.h: interface for the CDatabase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABASE_H__BCB778C3_9EE5_11D2_A2AB_006008043EC4__INCLUDED_)
#define AFX_DATABASE_H__BCB778C3_9EE5_11D2_A2AB_006008043EC4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include <afxdao.h>


#include "Job.h"
#include "Utilities.h"
#include "definitions.h"


class AFX_MFC_EXT_TYPE CSysDBase  
{
public:
	BOOL				m_bInitialized;						// Object initialized flag.
	CSysDBase();
	virtual ~CSysDBase();

	BOOL Initialize ( void );
	CString GetLastErrorMsg();
	void SetLastErrorMsg(CString csMessage);
	BOOL Open();												// Open the database.
	void Close();												// Close the database.
	CDaoDatabase	m_dbJobDatabase;						// DAO Database object.

private:

	CString m_csErrorMsg;
};






class AFX_MFC_EXT_TYPE CDatabase : public CSysDBase 
{
public:
	BOOL TemplateInUse(CString csTemplateName);
	BOOL RemoveTemplate(CString csTemplate);
	CDatabase();
	virtual ~CDatabase();

	BOOL GetJobNames ( CStringArray * csJobArray );
	BOOL GetJobAttributes ( CString csJobName, CJob * oJobInfo );
	BOOL SetJobAttributes ( CJob * oJobInfo );
	BOOL GetScannerAttributes ( CString csName, 
								BOOL *pbUse, 
								BOOL *pbEnable, 
								int *pnType, 
								CString *pcsTrigger,
								CString *pcsTriggerOff,
								CString *pcsReset );
	BOOL SetScannerAttributes ( CString csName, 
								BOOL bUse, 
								BOOL bEnable, 
								int nType, 
								CString csTrigger,
								CString csTriggerOff,
								CString csReset );

	BOOL GetConveyorDIOAddress ( CString * csInput, CString * csOutput );
	BOOL GetDIOAddress ( CString * csInput, CString * csOutput );
	BOOL SetPassword ( CString csPassword );
	BOOL GetPassword ( CString *csPassword );

	BOOL GetDBApplicatorPoints ( void );
	BOOL GetActivePrinterAttributes ( CString *csName, 
										 BOOL *bUse,
										 BOOL *bEnable,
										 int *nType);

	BOOL GetPrinterAttributes ( CString csName, 
										 BOOL *bUse,
										 BOOL *bEnable,
										 int *nType);
	
	
	
	BOOL GetComPortAttributes ( CString csName,
										 int *nTriggerDelay,
										 int *nInputBufferSize,
										 int *nOutputBufferSize,
										 int *nPortID,
										 CString *csPortSettings,
										 BOOL *blnDTREnable,
										 BOOL *blnRTSEnable,
										 BOOL *blnNULLDiscard);



	BOOL GetConveyorAttributes ( BOOL *bPCControlled, BOOL *bLToRDirection );
	BOOL GetMotionAttributes ( CString *csName, CString *csSpeed, CString *csAcceleration );
	BOOL GetUsablePrinterList ( CString *csPrinterList );
	void GetApplicatorPoint ( int nPoint,
									  CString *csXPos, 
									  CString *csYPos,
									  CString *csRot );
	BOOL SetPrinterAttributes ( CString csName, 
										 BOOL bUse,
										 BOOL bEnable,
										 int nType);
	BOOL SetApplicatorPoint ( int nPoint,
									  CString csXPos, 
									  CString csYPos,
									  CString csRot );
	BOOL GetStartingSN ( CString csJobName, CString *csSerialNumber );
	BOOL SetStartingSN ( CString csJobName, CString csSerialNumber );
	BOOL SetAutoRetries ( int nRescans, int nRepicks );
	BOOL SetConveyorAttributes ( BOOL bPCControlled, BOOL bLToRDirection );
	BOOL GetTemplate ( CString csTemplateName, CString *csTemplate );
	BOOL SetTemplate ( CString csTemplateName, CString csTemplate );
	BOOL RemoveJob ( CString csJobName );
	BOOL GetFeederAttributes ( CString csName, 
													BOOL *bUse,
													BOOL *bEnable,
													int *nTimer);
	BOOL SetFeederAttributes ( CString csName, 
													BOOL bUse,
													BOOL bEnable,
													int nTimer);
	BOOL GetTemplateList ( CString *csTemplateList );
	BOOL GetGeneralAttributes ( int *nRescans, int *nRepicks, BOOL *b2up, int *nNumberOfNosepieces );
	BOOL SetGeneralAttributes ( int nRescans, int nRepicks, BOOL b2up, int nNumberOfNosepieces );
	BOOL SetMotionAttributes ( CString csName, CString csSpeed, CString csAccel );
	BOOL GetDeviceNames ( CString *csDevices );
	BOOL SetDIOAddress ( CString csInput, CString csOutput );
	BOOL SetConveyorDIOAddress ( CString csInput, CString csOutput );
	BOOL SetComPortAttributes ( CString csName,
										 int nTriggerDelay,
										 int nInputBufferSize,
										 int nOutputBufferSize,
										 int nPortID,
										 CString csPortSettings,
										 BOOL blnDTREnable,
										 BOOL blnRTSEnable,
										 BOOL blnNULLDiscard);
	BOOL GetSNAttributes ( CString csJobName, 
											 BOOL *bUseSerialization,
											 int *nBase,
											 int *nLength,
											 CString *csSerialNumber );

	BOOL GetSNAttributes ( CString csJobName, 
											 BOOL *bUseSerialization,
											 int *nBase,
											 int *nLength,
											 CString *csSerialNumber,
											 BOOL *blnJulianDateReset);
	

	GetSNAttributes ( CString csJobName, 
											 BOOL *bUseSerialization,
											 int *nBase,
											 int *nLength,
											 CString *csSerialNumber,
											 BOOL *blnJulianDateReset,
											 CString *csLastJulianDate);
	

//	For Check Digit Handling


	BOOL GetSNAttributes ( CString csJobName, 
										  BOOL *bUseSerialization,
										  int *nBase,
										  int *nLength,
										  CString *csSerialNumber,
										  BOOL *blnUseChkDigit,
										  CString *csCheckDigitSource,
										  CString *csCheckDigitType);






	BOOL SetSNAttributes ( CString csJobName, 
												 BOOL bUseSerialization,
												 int nBase,
												 int nLength,
												 CString csSerialNumber );

	BOOL SetSNAttributes ( CString csJobName, 
												 BOOL bUseSerialization,
												 int nBase,
												 int nLength,
												 CString csSerialNumber,
												 BOOL blnJulianDateReset);


	BOOL SetSNAttributes ( CString csJobName, 
						   BOOL bUseSerialization,
						   int nBase,
						   int nLength,
						   CString csSerialNumber,
						   BOOL blnUseCheckDigit,
						   CString csCheckDigitType,
						   CString csCheckDigitSource);


	
	unsigned long GetFGBackGroundColor();
	unsigned long GetFGHighlightColor();
	BOOL CheckForReservedWord(CString csBuffer, CString *csFormat);
	BOOL IsReservedWord(CString csBuffer);
	BOOL IsReservedWordFormatValid(CString csBuffer, CString csFormat);
	BOOL VerifyDynamicData(CString csName, CString csValue);
	BOOL VerifyData(CString csName, CString csValue);

	BOOL VerifyJobAttributes( CJob * oJobInfo);

	BOOL GetInputBits(CStringArray *csInputBits);
	BOOL GetOutputBits(CStringArray *csOutputBits);
	BOOL GetPointTypes(CStringArray *csPointTypes);
	BOOL GetPointAttributes(CString csPointName, CString *csXPos, CString *csYPos, CString *csRot);
	CString GetLastErrorMsg();
	void SetLastErrorMsg(CString csMessage);
	BOOL IsTemplateActive(CString csTemplateName);
	BOOL ChkForShiftChanges(CString csJobName);

	void SetLastShiftID(CString csJobName, CString csShiftID);
	int GetLastShiftID(CString csJobName);
	BOOL SetLastJulianDate ( CString csJobName, CString csSerialNumber, CString csLastJulianDate );

	BOOL CheckPositionFormat ( CString csPosition );

	CString GetPrintedValue(CString csType, CString csDefault);
	CString GetDisplayedValue(CString csType, CString csDefault);
	
	BOOL VerifyReservedWordValue(CString csType, CString csUserValue);
	CString GetShiftID();


private:

	// X, Y, and rotation applicator points that are stored here for use.

	CString	m_csOriginX;				
	CString	m_csOriginY;
	CString	m_csOriginRot;
	CString	m_csParkX;
	CString	m_csParkY;
	CString	m_csParkRot;
	CString	m_csNP1ScanOffset0X;
	CString	m_csNP1ScanOffset0Y;
	CString	m_csNP1ScanOffset0Rot;
	CString	m_csNP1ScanOffset90X;
	CString	m_csNP1ScanOffset90Y;
	CString	m_csNP1ScanOffset90Rot;
	CString	m_csNP1Offset0X;
	CString	m_csNP1Offset0Y;
	CString	m_csNP1Offset0Rot;
	CString	m_csNP1Offset90X;
	CString	m_csNP1Offset90Y;
	CString	m_csNP1Offset90Rot;
	CString	m_csNP2ScanOffset0X;
	CString	m_csNP2ScanOffset0Y;
	CString	m_csNP2ScanOffset0Rot;
	CString	m_csNP2ScanOffset90X;
	CString	m_csNP2ScanOffset90Y;
	CString	m_csNP2ScanOffset90Rot;
	CString	m_csNP2Offset0X;
	CString	m_csNP2Offset0Y;
	CString	m_csNP2Offset0Rot;
	CString	m_csNP2Offset90X;
	CString	m_csNP2Offset90Y;
	CString	m_csNP2Offset90Rot;
	CString m_csRestPositionRot;
	CString m_csRestPositionY;
	CString m_csRestPositionX;
	CString	m_csErrorMsg;

};

#endif // !defined(AFX_DATABASE_H__BCB778C3_9EE5_11D2_A2AB_006008043EC4__INCLUDED_)
