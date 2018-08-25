// scribbleDoc.h : interface of the CScribbleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCRIBBLEDOC_H__0BC7BCAC_CA2F_11D4_BB12_F46BEF55B851__INCLUDED_)
#define AFX_SCRIBBLEDOC_H__0BC7BCAC_CA2F_11D4_BB12_F46BEF55B851__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////
// class CStroke
// A stroke is a series of connected points in the Scribble drawing.
// A Scribble document may have multiple strokes.
class CStroke : public CObject
{
public:
   CStroke( UINT nPenWidth );

protected:
   CStroke();
   DECLARE_SERIAL( CStroke )

// Attributes
   // One width applies to entire stroke
   UINT m_nPenWidth;   
   // smallest rect that surrounds all of the points in the stroke
   CRect m_rectBounding;  

public:
   CArray<CPoint, CPoint> m_pointArray;  // Series of connected points                                                    // points
   CRect& GetBoundingRect() { return m_rectBounding; }

// Operations
   void FinishStroke();
   BOOL DrawStroke( CDC* pDC );
   virtual void Serialize( CArchive& ar );
};


class CScribbleDoc : public CDocument
{
protected: // create from serialization only
   CScribbleDoc();
   DECLARE_DYNCREATE(CScribbleDoc)

// Attributes
	CPen m_penCur;
	UINT m_nPenWidth;
	BOOL m_bThickPen;   // Thick currently selected or not 
   UINT m_nThinWidth;  // Current definition of thin
   UINT m_nThickWidth; // Current definition of thick 
   CSize m_sizeDoc;

public:
	CTypedPtrList<CObList, CStroke*> m_strokeList ;

// Operations
	CPen* GetCurrentPen( ) { return &m_penCur; }
   CSize GetDocSize() { return m_sizeDoc; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScribbleDoc)
	virtual BOOL OnNewDocument();
	virtual void Serialize( CArchive& ar );
	virtual BOOL OnOpenDocument( LPCTSTR lpszPathName );
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
	CStroke* NewStroke();
	virtual ~CScribbleDoc();

protected:
	void ReplacePen();
	void InitDocument();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump( CDumpContext& dc ) const;
#endif

// Generated message map functions
	//{{AFX_MSG(CScribbleDoc)
	afx_msg void OnEditClearAll();
	afx_msg void OnPenThickOrThin();
	afx_msg void OnUpdateEditClearAll( CCmdUI* pCmdUI );
	afx_msg void OnUpdatePenThickOrThin( CCmdUI* pCmdUI );
	afx_msg void OnPenWidths();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCRIBBLEDOC_H__0BC7BCAC_CA2F_11D4_BB12_F46BEF55B851__INCLUDED_)
