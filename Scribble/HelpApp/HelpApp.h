// HelpApp.h : main header file for the HELPAPP application
//

#if !defined(AFX_HELPAPP_H__431F5BD8_5449_41ED_9ED0_ABCBC6FB5923__INCLUDED_)
#define AFX_HELPAPP_H__431F5BD8_5449_41ED_9ED0_ABCBC6FB5923__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHelpAppApp:
// See HelpApp.cpp for the implementation of this class
//

class CHelpAppApp : public CWinApp
{
public:
	CHelpAppApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHelpAppApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CHelpAppApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELPAPP_H__431F5BD8_5449_41ED_9ED0_ABCBC6FB5923__INCLUDED_)
