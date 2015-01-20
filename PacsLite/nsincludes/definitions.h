#if !defined __DEFINITIONS_
#define __DEFINITIONS_

#define DllExport   __declspec( dllexport )

#define AFX_MFC_EXT_TYPE __declspec( dllexport )


#define	PW_OFFSET			45


#include "simulationconstants.h"

//#define SIMULATION	SIMULATEPRINTER|SIMULATELABELSCANNER|SIMULATEDIOCONTROLLER|SIMULATEPCBASEDCONTROLLER

//#define SIMULATION	SIMULATELABELSCANNER|SIMULATEDIOCONTROLLER

//#define SIMULATION	SIMULATEPRINTER|SIMULATEDIOCONTROLLER|SIMULATEPCBASEDCONTROLLER

//#define SIMULATION	SIMULATEPRINTER|SIMULATELABELSCANNER|SIMULATEDIOCONTROLLER

//#define SIMULATION	SIMULATEPRINTER|SIMULATELABELSCANNER

//#define SIMULATION	SIMULATELABELSCANNER

#define SIMULATION 0


struct	threadCom {
	BOOL		bThreadLives;
	unsigned	long ulInputArray;
	CString	csPosition;
	CString  csReturnScan;
};



enum point_key
{
	ORIGIN_KEY,
	PARK_KEY,
	NP1_SCAN_OFFSET0_KEY,
	NP1_SCAN_OFFSET90_KEY,
	NP1_OFFSET0_KEY,
	NP1_OFFSET90_KEY,
	NP2_SCAN_OFFSET0_KEY,
	NP2_SCAN_OFFSET90_KEY,
	NP2_OFFSET0_KEY,
	NP2_OFFSET90_KEY,
	REST_POSITION_KEY
};


enum systems
{
	PRINTER,
	SCANNER,
	PLACEMENT_SCANNER,
	SYSTEM_SCANNER,
	FRONT_DOWNSTREAM_PRINTER,
	BACK_UPSTREAM_PRINTER,
	BACK_DOWNSTREAM_PRINTER,
};


enum printer_type
{
	ZEBRA,
	INTERMEC,
	DATAMAX,
	THARO,
	GENERIC,
	APOLLO,
	SATO
};


enum scanner_type
{
	MICROSCAN_VS310,
	MICROSCAN_VS710,
	METANETICS_IR2000HD,
	WELCHALLYN_4700,
	WELCHALLYN_3900

};


enum controller_type
{
	MULTI_SEL,
	SUPER_SEL,
	GALIL
};


enum ser_base
{
	BASE10,
	BASE16,
	BASE29,
	BASE31,
	BASE36,
	OTHER
};

enum date_code
{
	YYMM,
	YYWW,
	WWYY
};

// Database key words.
const CString c_csOriginPos					= "Origin";
const CString c_csPrePickPos					= "PrePickupPos";
const CString c_csPickPos						= "PickupPos";
const CString c_csParkPos						= "Park";
const CString c_csNosePiece1ScanOffset0	= "NP1ScanOffset0";
const CString c_csNosePiece1ScanOffset90	= "NP1ScanOffset90";
const CString c_csNosePiece1Offset0			= "NP1Offset0";
const CString c_csNosePiece1Offset90		= "NP1Offset90";
const CString c_csNosePiece2ScanOffset0	= "NP2ScanOffset0";
const CString c_csNosePiece2ScanOffset90	= "NP2ScanOffset90";
const CString c_csNosePiece2Offset0			= "NP2Offset0";
const CString c_csNosePiece2Offset90		= "NP2Offset90";
const CString c_csRestPosition				= "RestPosition";
const CString c_csFixedScanner				= "FixedScanner";
const CString c_csNosePiece1Info			= "NP1Info";
const CString c_csNosePiece2Info			= "NP2Info";
const CString c_csScannerInfo				= "ScannerInfo";
const CString c_csThetaRotationDir			= "ThetaRotation";


// Y axis actuator limit
const	CString	c_csYAxisMax					= "055500";



enum printer_loc
{
	FRONT_DOWNSTREAM,
	FRONT_UPSTREAM,
	BACK_UPSTREAM,
	BACK_DOWNSTREAM,
	OFFLINE
};



#endif
