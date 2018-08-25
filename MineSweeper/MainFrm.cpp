// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MineSweeper.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_MOVE()
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_CONTENT, OnHelpContent)
	ON_COMMAND(ID_HELP_INDEX, OnHelpIndex)
	ON_COMMAND(ID_HELP_SEARCH, OnHelpSearch)
	ON_COMMAND(ID_HELP_USING, OnHelpUsing)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame(CMineSweeperApp* pParentWnd)
{
	this->m_pCWinApp = pParentWnd;	
}
CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// create a view to occupy the client area of the frame
//	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW&,
	if (!m_wndView.Create(NULL, NULL, WS_CHILD|WS_VISIBLE,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.dwExStyle &= ~WS_BORDER;
	cs.style &= ~WS_THICKFRAME;
	cs.style &= ~WS_BORDER;

HICON	hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	cs.lpszClass = AfxRegisterWndClass(0, 0, 0, hIcon);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	// forward focus to the view window
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnHelpContent() 
{
	HWND hwndMain = CMainFrame::m_hWnd;
	HWND hwnd = HtmlHelp(hwndMain,
            "MineSweeper.chm::/mine_object.htm",
            HH_DISPLAY_TOC, NULL) ;
}
void CMainFrame::OnHelpIndex() 
{
	HWND hwndMain = CMainFrame::m_hWnd;
	HWND hwnd = HtmlHelp(hwndMain,
            "MineSweeper.chm",
            HH_DISPLAY_INDEX, NULL) ;
}
void CMainFrame::OnHelpSearch() 
{
//	HH_FTS_QUERY q;
	HWND hwndMain = CMainFrame::m_hWnd;
	HWND hwnd = HtmlHelp(hwndMain,
            "MineSweeper.chm",
			HH_HELP_FINDER, NULL);
//            HH_DISPLAY_SEARCH, (DWORD)&q) ;
}

void CMainFrame::OnHelpUsing() 
{
	HWND hwndMain = CMainFrame::m_hWnd;
	::WinHelp(hwndMain, "winhlp32.hlp", HELP_HELPONHELP, 0);
}


void CMainFrame::OnMove(int x, int y) 
{
	CFrameWnd::OnMove(x, y);
	RECT Rect;
	GetWindowRect( &Rect );
	if (!IsIconic())
	{
		m_wndView.m_WindowLeft = Rect.left;
		m_wndView.m_WindowTop = Rect.top;
		m_wndView.SetProfileParams();
	}
}
