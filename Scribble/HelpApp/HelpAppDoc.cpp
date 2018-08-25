// HelpAppDoc.cpp : implementation of the CHelpAppDoc class
//

#include "stdafx.h"
#include "HelpApp.h"

#include "HelpAppDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelpAppDoc

IMPLEMENT_DYNCREATE(CHelpAppDoc, CDocument)

BEGIN_MESSAGE_MAP(CHelpAppDoc, CDocument)
	//{{AFX_MSG_MAP(CHelpAppDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelpAppDoc construction/destruction

CHelpAppDoc::CHelpAppDoc()
{
	// TODO: add one-time construction code here

}

CHelpAppDoc::~CHelpAppDoc()
{
}

BOOL CHelpAppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHelpAppDoc serialization

void CHelpAppDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CHelpAppDoc diagnostics

#ifdef _DEBUG
void CHelpAppDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHelpAppDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHelpAppDoc commands
