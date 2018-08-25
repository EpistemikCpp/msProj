// scribbleView.cpp : implementation of the CScribbleView class
//

#include "stdafx.h"
#include "scribble.h"

#include "scribbleDoc.h"
#include "scribbleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__ ;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScribbleView

IMPLEMENT_DYNCREATE(CScribbleView, CScrollView)

BEGIN_MESSAGE_MAP(CScribbleView, CScrollView)
	//{{AFX_MSG_MAP(CScribbleView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScribbleView construction/destruction

CScribbleView::CScribbleView()
  {
	 // TODO: add construction code here
  }

CScribbleView::~CScribbleView()
  {}

BOOL CScribbleView::PreCreateWindow( CREATESTRUCT& cs )
  {
	 // TODO: Modify the Window class or styles here by modifying
	 //  the CREATESTRUCT cs
 	 return CView::PreCreateWindow( cs );
  }

/////////////////////////////////////////////////////////////////////////////
// CScribbleView drawing

void CScribbleView::OnDraw( CDC* pDC )
  {
	 CScribbleDoc* pDoc = GetDocument();
	 ASSERT_VALID( pDoc );

	 // Get the invalidated rectangle of the view, or in the case
	 // of printing, the clipping region of the printer DC.
	 CRect rectClip ;
	 CRect rectStroke ;
	 pDC->GetClipBox( &rectClip );

	 // changes to account for the MM_LOENGLISH mapping mode
	 pDC->LPtoDP( &rectClip );
	 rectClip.InflateRect( 1, 1 ); // avoid rounding to nothing

	 // Note: CScrollView::OnPaint() will have already adjusted 
    // the viewpoint origin before calling OnDraw(), to reflect
    // the currently scrolled position.

    // The view delegates the drawing of individual strokes to
    // CStroke::DrawStroke( ).
	 CTypedPtrList<CObList, CStroke*>& strokeList = pDoc->m_strokeList ;
	 POSITION pos = strokeList.GetHeadPosition( );
	 while( pos != NULL )
      {
	     CStroke* pStroke = strokeList.GetNext( pos );
	     rectStroke = pStroke->GetBoundingRect() ;

	     // changes to account for the MM_LOENGLISH mapping mode
	     pDC->LPtoDP( &rectStroke );
	     rectStroke.InflateRect( 1, 1 );

	     if( !rectStroke.IntersectRect(&rectStroke, &rectClip) )
	       continue;
	     pStroke->DrawStroke( pDC );
      }
  }

/////////////////////////////////////////////////////////////////////////////
// CScribbleView printing

BOOL CScribbleView::OnPreparePrinting( CPrintInfo* pInfo )
  {
	 pInfo->SetMaxPage( 1 );
	 // the document is one page long: the drawing 
	 BOOL bRet = DoPreparePrinting( pInfo ); // default preparation

	 pInfo->m_nNumPreviewPages = 1 ; //Preview 1 page at a time
	 // Set this value after calling DoPreparePrinting to override
	 // value read from registry
	 return bRet ;
  }

void CScribbleView::OnBeginPrinting( CDC* /*pDC*/, CPrintInfo* /*pInfo*/ )
  {
	 // TODO: add extra initialization before printing
  }

void CScribbleView::OnEndPrinting( CDC* /*pDC*/, CPrintInfo* /*pInfo*/ )
  {
	 // TODO: add cleanup after printing
  }

/////////////////////////////////////////////////////////////////////////////
// CScribbleView diagnostics

#ifdef _DEBUG
void CScribbleView::AssertValid() const
  { CScrollView::AssertValid(); }

void CScribbleView::Dump( CDumpContext& dc ) const
  { CScrollView::Dump( dc );	}

CScribbleDoc* CScribbleView::GetDocument() // non-debug version is inline
  {
	 ASSERT( m_pDocument->IsKindOf(RUNTIME_CLASS(CScribbleDoc)) );
	 return (CScribbleDoc*)m_pDocument ;
  }
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScribbleView message handlers

void CScribbleView::OnLButtonDown( UINT nFlags, CPoint point ) 
  {
	 // CScrollView changes the viewport origin and mapping mode.
    // It's necessary to convert the point from device coordinates
    // to logical coordinates, such as are stored in the document.
	 CClientDC dc( this );
	 OnPrepareDC( &dc ); // set up mapping mode and viewport origin
	 dc.DPtoLP( &point );

    // Pressing the mouse button in the view window starts a new stroke.
	 m_pStrokeCur = GetDocument( )->NewStroke( );
	 // Add first point to the new stroke
	 m_pStrokeCur->m_pointArray.Add( point );

	 SetCapture();  // Capture the mouse until button up
	 m_ptPrev = point ;
	 // Serves as the MoveTo( ) anchor point for the LineTo() the next point,
	 // as the user drags the mouse

	 return ;
  }

void CScribbleView::OnLButtonUp( UINT nFlags, CPoint point ) 
  {
	 // Mouse button up is interesting in the Scribble application 
    // only if the user is currently drawing a new stroke by 
    // dragging the captured mouse.
    if( GetCapture( ) != this )
		return ;   // If this window (view) didn't capture the 
		 			  // mouse, the user isn't drawing in this window.

    CScribbleDoc* pDoc = GetDocument();
	 CClientDC dc( this );

    // CScrollView changes the viewport origin and mapping mode.
    // It's necessary to convert the point from device coordinates
    // to logical coordinates, such as are stored in the document.
    OnPrepareDC( &dc ); // set up mapping mode and viewport origin
    dc.DPtoLP( &point );

	 CPen* pOldPen = dc.SelectObject( pDoc->GetCurrentPen() );
	 dc.MoveTo( m_ptPrev );
	 dc.LineTo( point );
	 dc.SelectObject( pOldPen );
	 m_pStrokeCur->m_pointArray.Add( point );

	 // Tell the stroke item that we're done adding points to it.
    // This is so it can finish computing its bounding rectangle.
    m_pStrokeCur->FinishStroke();

    // Tell the other views that this stroke has been added so
    // that they can invalidate this stroke's area in their client area.
	 pDoc->UpdateAllViews( this, 0L, m_pStrokeCur );

	 // Release the mouse capture established at the beginning of the mouse drag.
	 ReleaseCapture();

    return ;
  }

void CScribbleView::OnMouseMove( UINT nFlags, CPoint point ) 
  {
    // Mouse movement is interesting in the Scribble application only if the
    // user is currently drawing a new stroke by dragging the captured mouse.
    if( GetCapture( ) != this )
		return ;           // If this window (view) didn't capture the 
							    // mouse, the user isn't drawing in this window.

    CClientDC dc( this );
	 // CScrollView changes the viewport origin and mapping mode.
    // It's necessary to convert the point from device coordinates
    // to logical coordinates, such as are stored in the document.
    OnPrepareDC( &dc );  // set up mapping mode and viewport origin
    dc.DPtoLP( &point );

	 m_pStrokeCur->m_pointArray.Add( point );

    // Draw a line from the previous detected point in the mouse
    // drag to the current point.
    CPen* pOldPen = dc.SelectObject( GetDocument( )->GetCurrentPen( ) );
    dc.MoveTo( m_ptPrev );
    dc.LineTo( point );
    dc.SelectObject( pOldPen );
    m_ptPrev = point ;

    return ;
  }

void CScribbleView::OnUpdate( CView* pSender, LPARAM lHint, CObject* pHint ) 
  {
    // The document has informed this view that some data has changed.
	 if( pHint != NULL )
		{
		  if( pHint->IsKindOf(RUNTIME_CLASS(CStroke)) )
          {
				// The hint is that a stroke has been added (or changed).
				// So, invalidate its rectangle.
				CStroke* pStroke = (CStroke*)pHint ;

            CClientDC dc( this );
            OnPrepareDC( &dc ); 
				CRect rectInvalid = pStroke->GetBoundingRect();

            // need to change the logical coordinates of the document to 
				// device coordinates for the window
				dc.LPtoDP( &rectInvalid );
				InvalidateRect( &rectInvalid );

				return ;
          }
      }
	 // We can't interpret the hint, so assume that anything
	 // might have been updated.
	 Invalidate();

	 return ;
  }

void CScribbleView::OnInitialUpdate() 
  {
    CScrollView::OnInitialUpdate();
    SetScrollSizes( MM_LOENGLISH, GetDocument()->GetDocSize() );
  }

void CScribbleView::OnPrint( CDC* pDC, CPrintInfo* pInfo ) 
  {
	 /* if (pInfo->m_nCurPage == 1)     // page no. 1 is the title page
	 {
		PrintTitlePage(pDC, pInfo);
	 }
		else {
	 */
	 CString strHeader = GetDocument()->GetTitle();

	 PrintPageHeader( pDC, pInfo, strHeader );
	 // PrintPageHeader() subtracts out from the pInfo->m_rectDraw the
	 // amount of the page used for the header.
	 pDC->SetWindowOrg( pInfo->m_rectDraw.left, -(pInfo->m_rectDraw.top) );

	 // Now print the rest of the page
	 OnDraw( pDC );
	 // }
	 return ;

	 //CScrollView::OnPrint( pDC, pInfo );
  }

void CScribbleView::PrintPageHeader( CDC *pDC, CPrintInfo *pInfo,
                                     CString &strHeader           )
  {
	 // Specify left text alignment
	 pDC->SetTextAlign( TA_LEFT );

	 // Print a page header consisting of the name of
	 // the document and a horizontal line
	 pDC->TextOut( 0, -25, strHeader );  // 1/4 inch down

	 // Draw a line across the page, below the header
	 TEXTMETRIC textMetric ;
	 pDC->GetTextMetrics( &textMetric );
	 int y = -35 - textMetric.tmHeight ;  // line 1/10th in. 

	 // below text
	 pDC->MoveTo( 0, y );                       // from left margin
	 pDC->LineTo( pInfo->m_rectDraw.right, y ); // to right margin

	 // Subtract from the drawing rectangle the space used by header.
	 y -= 25 ;     // space 1/4 inch below (top of) line
	 pInfo->m_rectDraw.top += y ;
  }
