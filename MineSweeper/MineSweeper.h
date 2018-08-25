// MineSweeper.h : main header file for the MINESWEEPER application
//

#if !defined(AFX_MINESWEEPER_H__B5B932F2_5AE9_4B08_8202_A3B4749EBBF8__INCLUDED_)
#define AFX_MINESWEEPER_H__B5B932F2_5AE9_4B08_8202_A3B4749EBBF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMineSweeperApp:
// See MineSweeper.cpp for the implementation of this class
//

class CMineSweeperApp : public CWinApp
{
public:
	CMineSweeperApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMineSweeperApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CMineSweeperApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MINESWEEPER_H__B5B932F2_5AE9_4B08_8202_A3B4749EBBF8__INCLUDED_)
