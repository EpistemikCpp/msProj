// HelpAppView.h : interface of the CHelpAppView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HELPAPPVIEW_H__35EF3D38_B8DF_4032_9788_77575D98E724__INCLUDED_)
#define AFX_HELPAPPVIEW_H__35EF3D38_B8DF_4032_9788_77575D98E724__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHelpAppView : public CView
{
protected: // create from serialization only
	CHelpAppView();
	DECLARE_DYNCREATE(CHelpAppView)

// Attributes
public:
	CHelpAppDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHelpAppView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHelpAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHelpAppView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in HelpAppView.cpp
inline CHelpAppDoc* CHelpAppView::GetDocument()
   { return (CHelpAppDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELPAPPVIEW_H__35EF3D38_B8DF_4032_9788_77575D98E724__INCLUDED_)
