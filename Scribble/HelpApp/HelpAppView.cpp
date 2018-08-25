// HelpAppView.cpp : implementation of the CHelpAppView class
//

#include "stdafx.h"
#include "HelpApp.h"

#include "HelpAppDoc.h"
#include "HelpAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelpAppView

IMPLEMENT_DYNCREATE(CHelpAppView, CView)

BEGIN_MESSAGE_MAP(CHelpAppView, CView)
	//{{AFX_MSG_MAP(CHelpAppView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelpAppView construction/destruction

CHelpAppView::CHelpAppView()
{
	// TODO: add construction code here

}

CHelpAppView::~CHelpAppView()
{
}

BOOL CHelpAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHelpAppView drawing

void CHelpAppView::OnDraw(CDC* pDC)
{
	CHelpAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CHelpAppView printing

BOOL CHelpAppView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHelpAppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHelpAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CHelpAppView diagnostics

#ifdef _DEBUG
void CHelpAppView::AssertValid() const
{
	CView::AssertValid();
}

void CHelpAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHelpAppDoc* CHelpAppView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHelpAppDoc)));
	return (CHelpAppDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHelpAppView message handlers
