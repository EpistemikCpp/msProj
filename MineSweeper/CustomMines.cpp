// CustomMines.cpp : implementation file
//

#include "stdafx.h"
#include "minesweeper.h"
#include "CustomMines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CustomMines dialog


CustomMines::CustomMines(CWnd* pParent /*=NULL*/)
	: CDialog(CustomMines::IDD, pParent)
{
	//{{AFX_DATA_INIT(CustomMines)
	m_Height = 0;
	m_Mines = 0;
	m_Width = 0;
	//}}AFX_DATA_INIT
}


void CustomMines::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CustomMines)
	DDX_Text(pDX, IDC_EDIT_Height, m_Height);
	DDV_MinMaxUInt(pDX, m_Height, 6, 30);
	DDX_Text(pDX, IDC_EDIT_Mines, m_Mines);
	DDV_MinMaxUInt(pDX, m_Mines, 10, 99);
	DDX_Text(pDX, IDC_EDIT_Width, m_Width);
	DDV_MinMaxUInt(pDX, m_Width, 9, 40);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CustomMines, CDialog)
	//{{AFX_MSG_MAP(CustomMines)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

