#if !defined(AFX_CUSTOMMINES_H__6760ECB8_E189_42EA_AA4C_93DFB08C96E2__INCLUDED_)
#define AFX_CUSTOMMINES_H__6760ECB8_E189_42EA_AA4C_93DFB08C96E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomMines.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CustomMines dialog

class CustomMines : public CDialog
{
// Construction
public:
	CustomMines(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CustomMines)
	enum { IDD = IDD_DIALOG_Custom_Mines };
	UINT	m_Height;
	UINT	m_Mines;
	UINT	m_Width;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CustomMines)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CustomMines)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMMINES_H__6760ECB8_E189_42EA_AA4C_93DFB08C96E2__INCLUDED_)
