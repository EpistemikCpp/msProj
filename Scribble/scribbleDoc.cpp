// scribbleDoc.cpp : implementation of the CScribbleDoc class
//

#include "stdafx.h"
#include "scribble.h"
#include "scribbleDoc.h"
#include "PenWidthsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScribbleDoc

IMPLEMENT_DYNCREATE(CScribbleDoc, CDocument)

BEGIN_MESSAGE_MAP(CScribbleDoc, CDocument)
	//{{AFX_MSG_MAP(CScribbleDoc)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
	ON_COMMAND(ID_PEN_THICK_OR_THIN, OnPenThickOrThin)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, OnUpdateEditClearAll)
	ON_UPDATE_COMMAND_UI(ID_PEN_THICK_OR_THIN, OnUpdatePenThickOrThin)
	ON_COMMAND(ID_PEN_WIDTHS, OnPenWidths)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScribbleDoc construction/destruction

CScribbleDoc::CScribbleDoc()
{
	// TODO: add one-time construction code here
}

CScribbleDoc::~CScribbleDoc()
	{}

/////////////////////////////////////////////////////////////////////
// CScribbleDoc - New Document initialization
BOOL CScribbleDoc::OnNewDocument()
  {
	 if( !CDocument::OnNewDocument() ) 
	   return FALSE ;

    InitDocument();
    return TRUE ;
  }

/////////////////////////////////////////////////////////////////////////////
// CScribbleDoc serialization
void CScribbleDoc::Serialize( CArchive& ar )
  {
	 if( ar.IsStoring() )
		ar << m_sizeDoc ;
	 else
		  ar >> m_sizeDoc ;

	 m_strokeList.Serialize( ar );
  }

/////////////////////////////////////////////////////////////////////////////
// CScribbleDoc - drawing strokes
BOOL CStroke::DrawStroke( CDC* pDC )
  {
    CPen penStroke;
	 if( !penStroke.CreatePen(PS_SOLID, m_nPenWidth, RGB(0,0,0)) ) 
		return FALSE;

	 CPen* pOldPen = pDC->SelectObject( &penStroke );
	 pDC->MoveTo( m_pointArray[0] );
	 for( int i=1; i < m_pointArray.GetSize(); i++ )
		 pDC->LineTo( m_pointArray[i] );

	 pDC->SelectObject( pOldPen );
	 return TRUE;
  }

/////////////////////////////////////////////////////////////////////////////
// CScribbleDoc diagnostics

#ifdef _DEBUG
void CScribbleDoc::AssertValid() const
  { CDocument::AssertValid(); }

void CScribbleDoc::Dump( CDumpContext& dc ) const
  { CDocument::Dump(dc); }
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScribbleDoc commands

CStroke* CScribbleDoc::NewStroke()
  {
    CStroke* pStrokeItem = new CStroke( m_nPenWidth );
    m_strokeList.AddTail( pStrokeItem );

    // Mark document as modified to confirm File Close.
    SetModifiedFlag();    
    return pStrokeItem;
  }

void CScribbleDoc::InitDocument()
  {
    m_bThickPen = FALSE ;
    m_nThinWidth = 2 ;   // Default thin pen is 2 pixels wide
    m_nThickWidth = 5 ;  // Default thick pen is 5 pixels wide
    ReplacePen();        // Initialize pen according to current width

    // Default document size is 800 x 900 screen pixels.
    m_sizeDoc = CSize( 800, 900 );
  }

BOOL CScribbleDoc::OnOpenDocument( LPCTSTR lpszPathName ) 
  {
 	 if( !CDocument::OnOpenDocument(lpszPathName) )
	   return FALSE ;

	 InitDocument( );
	 return TRUE;
  }

void CScribbleDoc::DeleteContents() 
  {
    while( !m_strokeList.IsEmpty() )
	   delete m_strokeList.RemoveHead( ) ;

	 CDocument::DeleteContents();
  }

/////////////////////////////////////////////////////////////
// CStroke

//MHS: Set the version of the App
IMPLEMENT_SERIAL( CStroke, CObject, 3 )

CStroke::CStroke()
  {
    // This empty constructor should be used by
    // the application framework for serialization only
  }

CStroke::CStroke( UINT nPenWidth )
  {
	 m_nPenWidth = nPenWidth ;
	 m_rectBounding.SetRectEmpty();
  }

void CStroke::Serialize( CArchive& ar )
  {
    if( ar.IsStoring() )
      {
	    ar << m_rectBounding;
	    ar << (WORD)m_nPenWidth;
       m_pointArray.Serialize(ar);
      }
    else
      {
        ar >> m_rectBounding ;
	     WORD w ;
	     ar >> w ;
	     m_nPenWidth = w ;
		  m_pointArray.Serialize( ar );
      }
  }

void CScribbleDoc::OnEditClearAll() 
  {
    DeleteContents();
    SetModifiedFlag();
    UpdateAllViews( NULL );
  }

void CScribbleDoc::OnPenThickOrThin() 
  {
    // Toggle the state of the pen between thin and thick.
    m_bThickPen = !m_bThickPen;
    // Change the current pen to reflect the new width.
    ReplacePen();
  }

void CScribbleDoc::ReplacePen()
  {
    m_nPenWidth = m_bThickPen ? m_nThickWidth : m_nThinWidth ;
    // Change the current pen to reflect the new width.
    m_penCur.DeleteObject();
    m_penCur.CreatePen( PS_SOLID, m_nPenWidth, RGB(0,0,0) );
  }

void CScribbleDoc::OnUpdateEditClearAll( CCmdUI* pCmdUI ) 
  {
    // Enable the user-interface object (menu item or tool-bar button)
    // if the document is non-empty, i.e., has at least one stroke.
    pCmdUI->Enable( !m_strokeList.IsEmpty() );
  }

void CScribbleDoc::OnUpdatePenThickOrThin( CCmdUI* pCmdUI ) 
  {
    // Add check mark to Pen Thick Line menu item if the current width is "thick"
    pCmdUI->SetCheck( m_bThickPen );
  }

void CScribbleDoc::OnPenWidths() 
  {
   CPenWidthsDlg dlg ;

   // Initialize dialog data
   dlg.m_nThinWidth = m_nThinWidth;
   dlg.m_nThickWidth = m_nThickWidth;
   
   // Invoke the dialog box
   if( dlg.DoModal() == IDOK )
	 {
     // retrieve the dialog data
     m_nThinWidth = dlg.m_nThinWidth;
     m_nThickWidth = dlg.m_nThickWidth;
     
     // Update the pen used by views when drawing new strokes
     // to reflect the new pen widths for "thick" and "thin".
     ReplacePen();
	 }
  }

void CStroke::FinishStroke()
  {
    if( m_pointArray.GetSize() == 0 )
      {
	     m_rectBounding.SetRectEmpty();
        return;
      }

    CPoint pt = m_pointArray[0] ;
    m_rectBounding = CRect( pt.x, pt.y, pt.x, pt.y );

    for( int i=1; i < m_pointArray.GetSize(); i++ )
      {
	     // If the point lies outside of the accumulated bounding
	     // rectangle, then inflate the bounding rect to include it.
	     pt = m_pointArray[i] ;
        m_rectBounding.left   = min( m_rectBounding.left,   pt.x );
	     m_rectBounding.right  = max( m_rectBounding.right,  pt.x );
	     m_rectBounding.top    = max( m_rectBounding.top,    pt.y );
	     m_rectBounding.bottom = min( m_rectBounding.bottom, pt.y );
      }

	 // Add the pen width to the bounding rectangle.  This is needed to
	 // account for the width of the stroke when invalidating the screen.
	 m_rectBounding.InflateRect( CSize(m_nPenWidth, -(int)m_nPenWidth) );

	 return ;
  }
