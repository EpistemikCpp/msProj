// scribbleView.h : interface of the CScribbleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCRIBBLEVIEW_H__0BC7BCAE_CA2F_11D4_BB12_F46BEF55B851__INCLUDED_)
#define AFX_SCRIBBLEVIEW_H__0BC7BCAE_CA2F_11D4_BB12_F46BEF55B851__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CScribbleView : public CScrollView
{
protected: // create from serialization only
	CScribbleView();
	DECLARE_DYNCREATE(CScribbleView)

// Attributes
public:
	CScribbleDoc* GetDocument();

protected:
   CStroke*  m_pStrokeCur; // The stroke in progress
   CPoint    m_ptPrev;     // The last mouse pt in the stroke in progress

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScribbleView)
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation

public:
	void PrintPageHeader( CDC* pDC, CPrintInfo* pInfo, CString& strHeader );
	virtual ~CScribbleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions

protected:
	//{{AFX_MSG(CScribbleView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in scribbleView.cpp
inline CScribbleDoc* CScribbleView::GetDocument()
   { return (CScribbleDoc*)m_pDocument ; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCRIBBLEVIEW_H__0BC7BCAE_CA2F_11D4_BB12_F46BEF55B851__INCLUDED_)
