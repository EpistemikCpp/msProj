// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__2E4457FD_0FEB_4C24_AFFD_0CB99CF37D7C__INCLUDED_)
#define AFX_MAINFRM_H__2E4457FD_0FEB_4C24_AFFD_0CB99CF37D7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChildView.h"

class CMineSweeperApp;

class CMainFrame : public CFrameWnd
{
	
public:
//	CMainFrame();
	CMainFrame(CMineSweeperApp* pParentWnd);

protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CMineSweeperApp* m_pCWinApp;
	CChildView    m_wndView;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnHelpContent();
	afx_msg void OnHelpIndex();
	afx_msg void OnHelpSearch();
	afx_msg void OnHelpUsing();
	afx_msg void OnMove(int x, int y);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__2E4457FD_0FEB_4C24_AFFD_0CB99CF37D7C__INCLUDED_)
