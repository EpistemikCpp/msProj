// BestTimes.cpp : implementation file
//

#include "stdafx.h"
#include "minesweeper.h"
#include "BestTimes.h"
#include "FastestTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// BestTimes dialog


BestTimes::BestTimes(CWnd* pParent /*=NULL*/)
	: CDialog(BestTimes::IDD, pParent)
{
	//{{AFX_DATA_INIT(BestTimes)
	m_NameBeginner = _T("");
	m_NameExpert = _T("");
	m_NameIntermediate = _T("");
	m_TimeBeginner = 0;
	m_TimeExpert = 0;
	m_TimeIntermediate = 0;
	//}}AFX_DATA_INIT
}


void BestTimes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BestTimes)
	DDX_Text(pDX, IDC_EDIT_NameBeginner, m_NameBeginner);
	DDX_Text(pDX, IDC_EDIT_NameExpert, m_NameExpert);
	DDX_Text(pDX, IDC_EDIT_NameIntermediate, m_NameIntermediate);
	DDX_Text(pDX, IDC_EDIT_TimeBeginner, m_TimeBeginner);
	DDX_Text(pDX, IDC_EDIT_TimeExpert, m_TimeExpert);
	DDX_Text(pDX, IDC_EDIT_TimeIntermediate, m_TimeIntermediate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BestTimes, CDialog)
	//{{AFX_MSG_MAP(BestTimes)
	ON_BN_CLICKED(ID_ResetScores, OnResetScores)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BestTimes message handlers

void BestTimes::OnResetScores() 
{
	m_NameBeginner		= _T("Anonymous");
	m_NameExpert		= _T("Anonymous");
	m_NameIntermediate	= _T("Anonymous");
	m_TimeBeginner		= 999;
	m_TimeExpert		= 999;
	m_TimeIntermediate	= 999;
	UpdateData(false);
}
