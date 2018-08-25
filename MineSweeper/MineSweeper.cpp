// MineSweeper.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MineSweeper.h"
#include "AboutDlg.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMineSweeperApp

BEGIN_MESSAGE_MAP(CMineSweeperApp, CWinApp)
	//{{AFX_MSG_MAP(CMineSweeperApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMineSweeperApp construction

CMineSweeperApp::CMineSweeperApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMineSweeperApp object

CMineSweeperApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMineSweeperApp initialization

BOOL CMineSweeperApp::InitInstance()
{
	AfxEnableControlContainer();

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("AlWhin2K"));


	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object.

	CMainFrame* pFrame = new CMainFrame(this);
	m_pMainWnd = pFrame;
	// create and load the frame with its resources

	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_SYSMENU|WS_MINIMIZEBOX, NULL,
		NULL);

	// The one and only window has been initialized, so show and update it.
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMineSweeperApp message handlers


// App command to run the dialog
void CMineSweeperApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}




