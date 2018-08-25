// PenWidthsDlg.h : header file
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PENWIDTHSDLG_H__C5A83B60_D068_11D4_BB12_99FF980C0351__INCLUDED_)
#define AFX_PENWIDTHSDLG_H__C5A83B60_D068_11D4_BB12_99FF980C0351__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPenWidthsDlg dialog

class CPenWidthsDlg : public CDialog
{
// Construction
public:
	CPenWidthsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPenWidthsDlg)
	enum { IDD = IDD_PEN_WIDTHS };
	int m_nThinWidth ;
	int m_nThickWidth ;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPenWidthsDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

// Generated message map functions
	//{{AFX_MSG(CPenWidthsDlg)
	afx_msg void OnDefaultPenWidths();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// VC++ will insert additional declarations immediately before the previous line.

#endif
// !defined(AFX_PENWIDTHSDLG_H__C5A83B60_D068_11D4_BB12_99FF980C0351__INCLUDED_)
