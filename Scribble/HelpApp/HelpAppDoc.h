// HelpAppDoc.h : interface of the CHelpAppDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HELPAPPDOC_H__C5CE31B5_A673_4B92_AB6A_3AB0863343F6__INCLUDED_)
#define AFX_HELPAPPDOC_H__C5CE31B5_A673_4B92_AB6A_3AB0863343F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHelpAppDoc : public CDocument
{
protected: // create from serialization only
	CHelpAppDoc();
	DECLARE_DYNCREATE(CHelpAppDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHelpAppDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHelpAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHelpAppDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELPAPPDOC_H__C5CE31B5_A673_4B92_AB6A_3AB0863343F6__INCLUDED_)
