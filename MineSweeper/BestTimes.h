#if !defined(AFX_BESTTIMES_H__519C86D9_D9BC_4343_928B_299E2F7B2F23__INCLUDED_)
#define AFX_BESTTIMES_H__519C86D9_D9BC_4343_928B_299E2F7B2F23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BestTimes.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// BestTimes dialog

class BestTimes : public CDialog
{
// Construction
public:
	BestTimes(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(BestTimes)
	enum { IDD = IDD_DIALOG_BestScores };
	CString	m_NameBeginner;
	CString	m_NameExpert;
	CString	m_NameIntermediate;
	UINT	m_TimeBeginner;
	UINT	m_TimeExpert;
	UINT	m_TimeIntermediate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BestTimes)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(BestTimes)
	afx_msg void OnResetScores();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BESTTIMES_H__519C86D9_D9BC_4343_928B_299E2F7B2F23__INCLUDED_)
