/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998,'99 by J�rg K�nig
// All rights reserved
//
// This file is part of the completely free tetris clone "CGTetris".
//
// This is free software.
// You may redistribute it by any means providing it is not sold for profit
// without the authors written consent.
//
// No warrantee of any kind, expressed or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Send bug reports, bug fixes, enhancements, requests, flames, etc., and
// I'll try to keep a version up to date.  I can be reached as follows:
//    J.Koenig@adg.de                 (company site)
//    Joerg.Koenig@rhein-neckar.de    (private site)
//
// Revision 2, 04/27/99
/////////////////////////////////////////////////////////////////////////////


// OptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tetris.h"
#include "OptionsDlg.h"
#include "GameBoard.h"
#include "SplashWnd.h"

//#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// music box indices:
#define CHAIKOVSKY 0
#define SCORPIONS	 1
#define KALINKA	 2

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg property page

IMPLEMENT_DYNCREATE(COptionsDlg, CBitmapPropPage)

COptionsDlg::COptionsDlg() : CBitmapPropPage(COptionsDlg::IDD, IDS_TitleOptionsPage)
{
	//{{AFX_DATA_INIT(COptionsDlg)
	m_bGrid = FALSE;
	m_nSquareHeight = 0;
	m_nSquareWidth = 0;
	m_bWantSound = FALSE;
	m_bWantMusic = FALSE;
	m_nMusicType = -1;
	m_bExFigures = FALSE;
	m_strSoundCard = _T("");
	m_strSquareHeight = _T("");
	m_strSquareWidth = _T("");
	m_bSequence = FALSE;
	//}}AFX_DATA_INIT
	m_psp.dwFlags &= ~PSP_HASHELP;
}

COptionsDlg::~COptionsDlg()
  { }

void COptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CBitmapPropPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsDlg)
	DDX_Control(pDX, IDC_ChkSequence, m_ctrlSequence);
	DDX_Control(pDX, IDC_MusicBox, m_ctrlMusicBox);
	DDX_Control(pDX, IDC_ChkMusic, m_ctrlWantMusic);
	DDX_Control(pDX, IDC_ChkSound, m_ctrlWantSound);
	DDX_Control(pDX, IDC_SpinWidth, m_spinWidth);
	DDX_Control(pDX, IDC_SpinHeight, m_spinHeight);
	DDX_Check(pDX, IDC_CheckGrid, m_bGrid);
	DDX_Text(pDX, IDC_EditHeight, m_nSquareHeight);
	DDX_Text(pDX, IDC_EditWidth, m_nSquareWidth);
	DDX_Check(pDX, IDC_ChkSound, m_bWantSound);
	DDX_Check(pDX, IDC_ChkMusic, m_bWantMusic);
	DDX_CBIndex(pDX, IDC_MusicBox, m_nMusicType);
	DDX_Check(pDX, IDC_ExtendedFigureSet, m_bExFigures);
	DDX_Text(pDX, IDC_TxtSoundCard, m_strSoundCard);
	DDX_Text(pDX, IDC_TxtSquareHeight, m_strSquareHeight);
	DDX_Text(pDX, IDC_TxtSquareWidth, m_strSquareWidth);
	DDX_Check(pDX, IDC_ChkSequence, m_bSequence);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_Splash, m_btnSplash);

	if( ! pDX->m_bSaveAndValidate ) 
     {
		// set language dependend strings
		GetDlgItem(IDC_GroupBoard)->SetWindowText(m_strBoard);
		GetDlgItem(IDC_GroupSound)->SetWindowText(m_strSound);
		GetDlgItem(IDC_ExtendedFigureSet)->SetWindowText(m_strExFigureSet);
		GetDlgItem(IDC_Splash)->SetWindowText(m_strSplashAgain);
		GetDlgItem(IDC_ChkSound)->SetWindowText(m_strEnableSound);
		GetDlgItem(IDC_ChkMusic)->SetWindowText(m_strEnableMusic);
		GetDlgItem(IDC_CheckGrid)->SetWindowText(m_strGrid);
		GetDlgItem(IDC_ChkSequence)->SetWindowText(m_strSequence);
     }
}


void COptionsDlg::LoadAllStrings() {
	VERIFY(CLanguage::LoadString(m_strSquareWidth, IDS_TxtSquareWidth));
	VERIFY(CLanguage::LoadString(m_strSquareHeight, IDS_TxtSquareHeight));
	VERIFY(CLanguage::LoadString(m_strSoundCard, IDS_TxtSoundCardRequired));
	VERIFY(CLanguage::LoadString(m_strGrid, IDS_TxtGrid));
	VERIFY(CLanguage::LoadString(m_strSplashAgain, IDS_TxtSplashAgain));
	VERIFY(CLanguage::LoadString(m_strEnableSound, IDS_TxtEnableSound));
	VERIFY(CLanguage::LoadString(m_strEnableMusic, IDS_TxtEnableMusic));
	VERIFY(CLanguage::LoadString(m_strBoard, IDS_TxtBoard));
	VERIFY(CLanguage::LoadString(m_strSound, IDS_TxtSound));
	VERIFY(CLanguage::LoadString(m_strExFigureSet, IDS_TxtExFigureSet));
	VERIFY(CLanguage::LoadString(m_strChaikovsky, IDS_TxtChaikovsky));
	VERIFY(CLanguage::LoadString(m_strScorpions, IDS_TxtScorpions));
	VERIFY(CLanguage::LoadString(m_strKalinka, IDS_TxtKalinka));
	VERIFY(CLanguage::LoadString(m_strSequence, IDS_TxtSequence));

	UpdateData(FALSE);
}

BEGIN_MESSAGE_MAP(COptionsDlg, CBitmapPropPage)
	//{{AFX_MSG_MAP(COptionsDlg)
	ON_BN_CLICKED(IDC_Splash, OnSplash)
	ON_BN_CLICKED(IDC_ChkMusic, OnChkMusic)
	ON_BN_CLICKED(IDC_ChkSequence, OnChkSequence)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg message handlers

/* this method is called when DoModal() is called on the associated
   property sheet (CMainDlg) in CTetrisApp::InitInstance(),
   or when the page is first accessed ?? */ 
BOOL COptionsDlg::OnInitDialog() 
  {
	CBitmapPropPage::OnInitDialog();

	LoadAllStrings();

	CGameBoard *pBoard = TetrisGetGameBoard();
	ASSERT( pBoard != 0 );
	pBoard->GetDimension( m_nSquareWidth, m_nSquareHeight );
	m_bGrid = pBoard->IsGridEnabled();
	m_bExFigures = pBoard->UseExFigureSet();

	m_spinHeight.SetRange( 4, 32 );
	m_spinHeight.SetPos( m_nSquareHeight );
	m_spinWidth.SetRange( 4, 32 );
	m_spinWidth.SetPos( m_nSquareWidth );

	m_bWantMusic = theApp.GetWantMusic();
	m_bWantSound = theApp.GetWantSound();
	m_bSequence  = theApp.GetWantSequence();

	m_ctrlMusicBox.EnableWindow( m_bWantMusic && !m_bSequence );

	m_ctrlMusicBox.AddString( m_strChaikovsky );
	m_ctrlMusicBox.AddString( m_strScorpions );
	m_ctrlMusicBox.AddString( m_strKalinka );
	AddMusicFiles( m_ctrlMusicBox );

	switch( theApp.GetMusicType() ) 
     {
		case IDM_Fairy:			m_nMusicType = CHAIKOVSKY; break;
		case IDM_WindOfChange:	m_nMusicType = SCORPIONS; break;
		case IDM_Kalinka:		   m_nMusicType = KALINKA; break;
		default:
			m_nMusicType 
            = m_ctrlMusicBox.FindStringExact( 0, theApp.GetMusicFileName() );
			if(m_nMusicType < 0)
				m_nMusicType = SCORPIONS;
			break;
     }

	UpdateData(FALSE);

	return TRUE;
 }

BOOL COptionsDlg::OnKillActive() 
  {
	SaveSettings();
	return CBitmapPropPage::OnKillActive();
  }

void COptionsDlg::OnOK() 
  {
	SaveSettings();
	CBitmapPropPage::OnOK();
  }

void COptionsDlg::OnCancel() 
  {
	SaveSettings();
	CBitmapPropPage::OnCancel();
  }

void COptionsDlg::SaveSettings()
  {
	UpdateData();

	CGameBoard * pBoard = TetrisGetGameBoard();
	ASSERT( pBoard != 0 );
	pBoard->EnableSound(m_bWantSound);
	pBoard->EnableMusic(m_bWantMusic);
	pBoard->SetDimension(m_nSquareWidth, m_nSquareHeight);
	pBoard->ShowGrid(m_bGrid);
	pBoard->UseExFigureSet(m_bExFigures);

	UINT uResource;
	switch(m_nMusicType)
     {
		case CHAIKOVSKY:	uResource = IDM_Fairy; break;
		case SCORPIONS:	uResource = IDM_WindOfChange; break;
		case KALINKA:		uResource = IDM_Kalinka; break;
		default:			uResource = IDM_FromFile; break;
     }
	pBoard->SetMusicType(uResource);
	pBoard->SetMusicSequence(m_bSequence);
	
	if( uResource == IDM_FromFile )
     {
		CString strFileName;
		m_ctrlMusicBox.GetLBText( m_nMusicType, strFileName );
		if( !strFileName.IsEmpty() )
        {
			pBoard->SetMusicFile(strFileName);
			theApp.WriteMusicFileName(strFileName);
        }
     }

	theApp.WriteMusicType(uResource);
	theApp.WriteWantSound(m_bWantSound);
	theApp.WriteWantMusic(m_bWantMusic);
	theApp.WriteSquareSize( m_nSquareWidth, m_nSquareHeight );
	theApp.WriteWantGrid(m_bGrid);
	theApp.WriteWantExFigures(m_bExFigures);
	theApp.WriteWantSequence(m_bSequence);
}

void COptionsDlg::OnSplash() 
  {
	CSplashWnd * pSplash = new CSplashWnd( IDB_Splash );
	pSplash->Create();
  }

void COptionsDlg::OnChkMusic() 
  {
	UpdateData();
	m_ctrlSequence.EnableWindow( m_bWantMusic );
	m_ctrlMusicBox.EnableWindow( m_bWantMusic && !m_bSequence );
  }

void COptionsDlg::OnChkSequence() 
  {
	UpdateData();
	m_ctrlMusicBox.EnableWindow( !m_bSequence );
  }


void COptionsDlg::AddMusicFiles(CComboBox & box) 
  {
	TCHAR chName[_MAX_PATH];
	::GetModuleFileName( 0, chName, _MAX_PATH );
	TCHAR chDrive[_MAX_DRIVE];
	TCHAR chPath[_MAX_PATH];
	TCHAR chFullPath[_MAX_PATH];
	_tsplitpath( chName, chDrive, chPath, 0, 0 );
	_tcscpy( chFullPath, chDrive );
	_tcscat( chFullPath, chPath );
	_tcscat( chFullPath, TEXT("*.mid") );

	CFileFind finder;
	BOOL bFound = finder.FindFile( chFullPath );
	while( bFound )
     {
		bFound = finder.FindNextFile();
		box.AddString( finder.GetFileTitle() );
     }
  }
