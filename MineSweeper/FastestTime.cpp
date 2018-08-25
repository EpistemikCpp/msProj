// FastestTime.cpp : implementation file
//

#include "stdafx.h"
#include "minesweeper.h"
#include "FastestTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FastestTime dialog


FastestTime::FastestTime(CWnd* pParent /*=NULL*/)
	: CDialog(FastestTime::IDD, pParent)
{
	//{{AFX_DATA_INIT(FastestTime)
	m_Name = _T("");
	m_Message1 = _T("");
	m_Message2 = _T("");
	m_Message3 = _T("");
	//}}AFX_DATA_INIT
}


void FastestTime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FastestTime)
	DDX_Text(pDX, IDC_EDIT_Name, m_Name);
	DDV_MaxChars(pDX, m_Name, 10);
	DDX_Text(pDX, IDC_EDIT_Message1, m_Message1);
	DDX_Text(pDX, IDC_EDIT_Message2, m_Message2);
	DDX_Text(pDX, IDC_EDIT_Message3, m_Message3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FastestTime, CDialog)
	//{{AFX_MSG_MAP(FastestTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FastestTime message handlers

BOOL FastestTime::OnInitDialog() 
{
	CDialog::OnInitDialog();

	FastestTime::GetDlgItem(IDC_EDIT_Name)->SetFocus();	

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
