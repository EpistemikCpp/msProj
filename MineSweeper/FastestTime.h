#if !defined(AFX_FASTESTTIME_H__35987727_A666_44D7_8E58_DFECBDAEDB8F__INCLUDED_)
#define AFX_FASTESTTIME_H__35987727_A666_44D7_8E58_DFECBDAEDB8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FastestTime.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FastestTime dialog

class FastestTime : public CDialog
{
// Construction
public:
	FastestTime(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(FastestTime)
	enum { IDD = IDD_DIALOG_FastestTime };
	CString	m_Name;
	CString	m_Message1;
	CString	m_Message2;
	CString	m_Message3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FastestTime)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(FastestTime)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FASTESTTIME_H__35987727_A666_44D7_8E58_DFECBDAEDB8F__INCLUDED_)
