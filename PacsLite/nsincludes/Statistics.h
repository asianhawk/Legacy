// Statistics.h: interface for the CStatistics class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATISTICS_H__43A44D42_2B68_11D2_A68A_641A11C1FB5F__INCLUDED_)
#define AFX_STATISTICS_H__43A44D42_2B68_11D2_A68A_641A11C1FB5F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxdao.h>


#include "definitions.h"
#include "NSStatisticsDBResource.h"


enum refreshrate
{
	REFRESH_ONCE_A_DAY,
	REFRESH_ONCE_A_WEEK,
	REFRESH_ONCE_A_MONTH,
	REFRESH_ONCE_A_YEAR,
	REFRESH_NEVER
};


// Computype log file updated every update rate.

const CString	c_csComputypeLog = "ComputypeStats.log";


class AFX_MFC_EXT_TYPE CStatistics  
{
public:
	CStatistics();
	virtual ~CStatistics();

	void	StartPanelCycleTime ( void );
	void	EndPanelCycleTime ( void );
	long	GetPanelCycleTime ( void );

	void	StartRunModeTime ( void );
	void	EndRunModeTime( void );
	float	GetRunModeTime ( void );
	void	StartIdleModeTime ( void );
	void	EndIdleModeTime ( void );
	float GetIdleModeTime ( void );
	void	StartSetupModeTime ( void );
	void	EndSetupModeTime ( void );
	float GetSetupModeTime ( void );
	void	IncrementLabelCount ( void );
	long	GetLabelCount ( void );
	void	IncrementRescanCount ( void );
	long	GetRescanCount ( void );
	void	IncrementRepickCount ( void );
	long	GetRepickCount ( void );
	void	IncrementPanelCount ( void );
	long	GetPanelCount ( void );
	BOOL	UpdateStatistics ( BOOL bForceLog );
	BOOL	StartNewProduct ( CString csProductName );
	BOOL	Initialize ( void );
	CString GetLogFile ( void );
	void	SetLogFile ( CString csLogFile );
	int	GetRefreshRate ( void );
	void	SetRefreshRate ( int nRefreshRate );
	BOOL	IsStatisticsEnabled ( void );
	void	SetEnableStatistics ( BOOL bEnable );
	int	GetUpdateRate ( void );
	void	SetUpdateRate ( int nUpdateRate );
	void  SetTimeToUpdate ( BOOL bTimeToUpdate );
	BOOL	IsTimeToUpdate ( void );

private:
	BOOL		m_bDisplayNoDB;			// Display no database msg flag.

	BOOL		m_bTimeToUpdate;			// Flag indicating that it is time to log.

	CString	m_csLogFile;				// User log file.
	CString	m_csProductName;			// Product name.

	// For file.
	float		m_fTimeInRunMode;			// Accumulative hours in run mode only.
	float		m_fTimeInIdleMode;		// Accumulative hours in hold or error.
	float		m_fTimeInSetupMode;		// Accumulative hours in setup mode.
	long		m_lLabelsApplied;			// The number of valid labels applied.
	long		m_lLabelsRescanned;		// The number of re-scanned.
	long		m_lLabelsRepicked;		// The number of re-picks.
	long		m_lPanelsCompleted;		// Then number of boards populated.

	long		m_lPanelCycleTime;		// Overall board cycle time ( real-time ) in seconds.

	int		m_nRefreshRate;			// The frequency in which the log file is cleared.
	int		m_nUpdateRate;				// The frequency in which the log file is updated.

	CTime		m_ctStartPanelTime;		// Used for timing board cycle rate.
	CTime		m_ctStartRunModeTime;	// Used for run mode timing.
	CTime		m_ctStartIdleModeTime;	// Used for idle mode timing.
	CTime		m_ctStartSetupModeTime;	// Used for setup mode timing.

	int		m_nDayOfLastLog;			// Keep track of the day it was logged to user
												// specified file.
	BOOL		m_bUseStatistics;			// Enable/disable flag.

	BOOL		m_bInRunModeTime;			// In timing mode flags.
	BOOL		m_bInIdleModeTime;
	BOOL		m_bInSetupModeTime;

	BOOL IsRefreshTime ( void );
	BOOL ParseLine ( CString csLine,
										long *lPanelCycleTime,
										long *lLabelsApplied,
										long *lLabelsRescanned,
										long *lLabelsRepicked,
										long *lPanelsCompleted,
										float *fTimeInRunMode,
										float *fTimeInIdleMode,
										float *fTimeInSetupMode );
	BOOL TimeToUpdate ( void );
	BOOL CheckLogForTimeChange ( int nUpdateRate );
	BOOL UpdateProductTotalTable ( CDaoDatabase *StatDB );
	BOOL UpdateTotalTable ( CDaoDatabase *StatDB );
	BOOL UpdateStatisticsDB ( void );
	BOOL RefreshStatistics ( void );
	CTime GetFileTime ( void );
	BOOL UpdateStatisticsFile ( void );
	void UpdateTimers ( void );

};
#endif // !defined(AFX_STATISTICS_H__43A44D42_2B68_11D2_A68A_641A11C1FB5F__INCLUDED_)
