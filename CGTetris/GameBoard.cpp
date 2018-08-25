/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998,'99 by Jörg König
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


// GameBoard.cpp : implementation file
//

#include "stdafx.h"
#include "Tetris.h"
#include "GameBoard.h"
#include "Piece.h"
#include "MemDC.h"
#include "VolumeCtrl.h"

#include <stdlib.h>
#include <time.h>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static CGameBoard *gpGameBoard;

CGameBoard *TetrisGetGameBoard() { return gpGameBoard; }

static UINT guBoomArray[] =
				{
					IDI_Boom_1,
					IDI_Boom_2,
					IDI_Boom_3,
					IDI_Boom_4,
					IDI_Boom_5,
					IDI_Boom_6,
					IDI_Boom_7,
					IDI_Boom_8,
					IDI_Boom_9,
					IDI_Boom_10,
				};

#define ENDVEC( vector ) ( vector-1 + sizeof(vector) / sizeof(vector[0]) )

/////////////////////////////////////////////////////////////////////////////
// CGameBoard

BOOL CGameBoard::m_bRegistered = Register();
CMusicPlayer *CGameBoard::m_pMusicPlayer;

IMPLEMENT_DYNAMIC(CGameBoard, CWnd);

CGameBoard::CGameBoard()
  {
	m_pCurPiece = m_pNextPiece = 0;
	m_usLevel = 0;
	m_clrCurPiece = RGB(0,0,0);
	m_bShowGrid = TRUE;
	m_nSquareWidth = 14;
	m_nSquareHeight = 14;
	m_clrBackground = RGB(255, 255, 255);
	m_bExFigures = FALSE;
	m_uTimer = 0;
	m_dwVolume = 50;	// 50% music volume by default
	m_bLevelSelected = FALSE;
	m_clrTopLeft = ::GetSysColor(COLOR_BTNHILIGHT);
	m_clrBottomRight = ::GetSysColor(COLOR_BTNSHADOW);

	if(!m_pMusicPlayer) 
		{
		 m_pMusicPlayer = new CMusicPlayer();
		 VERIFY( m_pMusicPlayer->Create() );
		}

	gpGameBoard = this;
  }

CGameBoard::~CGameBoard()
{
	if( m_pCurPiece )
		delete m_pCurPiece;
	if( m_pNextPiece )
		delete m_pNextPiece;

	if( m_pMusicPlayer )
		delete m_pMusicPlayer;

	gpGameBoard = 0;
}

BOOL CGameBoard :: Register()
{
	WNDCLASS wc;
	wc.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = GameBoardWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = 0;
	wc.hIcon = 0;
	wc.hCursor = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName = 0;
	wc.lpszClassName = TEXT("TetrisGameBoard");
	VERIFY(RegisterClass(&wc));
	return TRUE;
}

BEGIN_MESSAGE_MAP(CGameBoard, CWnd)
	//{{AFX_MSG_MAP(CGameBoard)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_NCDESTROY()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SYSCOLORCHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGameBoard message handlers

void CGameBoard::ShowGrid(BOOL bShow)
	{	m_bShowGrid = bShow; }

void CGameBoard :: Paint()
{
	Invalidate();
	OnPaint();	// force an immediately paint
}

void CGameBoard :: OnPaint()
{
	CPaintDC pdc(this); // device context for painting

	CMemDC dc(&pdc);

	CRect rect;
	GetClientRect(rect);
	
	dc.FillSolidRect(rect, m_clrBackground);

	register const UINT uWidth = Width(rect);
	register const UINT uHeight = Height(rect);

	// paint the board itself
	for( register UINT i=0; i<uHeight; ++i )
		for( register UINT j=0; j<uWidth; ++j )
			if( m_Board[i][j] != m_clrBackground ) 
				{
				 dc.FillSolidRect(j*m_nSquareWidth, i*m_nSquareHeight, 
					                m_nSquareWidth, m_nSquareHeight, m_Board[i][j]);
				 dc.Draw3dRect(j*m_nSquareWidth, i*m_nSquareHeight, m_nSquareWidth, 
					             m_nSquareHeight, m_clrTopLeft, m_clrBottomRight);
				}

	// now paint the current piece...
	if( m_pCurPiece != 0 )
     {
		register const int nLines = m_pCurPiece->GetLines();
		register const int nCols  = m_pCurPiece->GetColumns();

		for( register int l = nLines-1 ; l >= 0 ; --l )
			for( register int c = 0 ; c < nCols ; ++c ) 
           {
				int nL = m_nCurLine - ((nLines-1) & l);
				int nC = m_nCurCol + c;
				if( nL >= 0 && nL < Height() &&
					nC >= 0 && nC < Width() )
					if( m_pCurPiece->IsSquare(l, c) )
                 {
						dc.FillSolidRect(nC*m_nSquareWidth, nL*m_nSquareHeight,
							               m_nSquareWidth, m_nSquareHeight, m_clrCurPiece);
						dc.Draw3dRect(nC*m_nSquareWidth, nL*m_nSquareHeight, m_nSquareWidth,
							            m_nSquareHeight, m_clrTopLeft, m_clrBottomRight);
                 }
           }
     }

	// draw the grid
	if( m_bShowGrid )
     {
		// draw vertical lines
		for( register h = m_nSquareWidth; h < rect.Width(); h += m_nSquareWidth )
			{
			 dc.MoveTo(h, 0);
			 dc.LineTo(h, rect.bottom);
			}

		// draw horizontal lines
		for( register v = m_nSquareHeight; v < rect.Height(); v += m_nSquareHeight)
			{
			 dc.MoveTo(0, v);
			 dc.LineTo(rect.right, v);
			}
		}
}// OnPaint()

void CGameBoard::SetDimension(int nWidth, int nHeight)
  {
	m_nSquareWidth = nWidth;
	m_nSquareHeight = nHeight;
  }

void CGameBoard::GetDimension(int & nWidth, int & nHeight)
  {
	nWidth = m_nSquareWidth;
	nHeight = m_nSquareHeight;
  }

int CGameBoard::Width(LPCRECT pRect) const
{
	CRect rect(pRect ? pRect : CRect(0,0,0,0));
	if( ! pRect )
		GetClientRect(rect);
	return rect.Width() / m_nSquareWidth;
}

int CGameBoard::Height(LPCRECT pRect) const
{
	CRect rect(pRect ? pRect : CRect(0,0,0,0));
	if( ! pRect )
		GetClientRect(rect);
	return rect.Height() / m_nSquareHeight;
}

void CGameBoard::InitBoard()
{
	CRect rect;
	GetClientRect(rect);
	register const int nHeight = Height(rect);
	register const int nWidth = Width(rect);
	m_Board.resize(nHeight, vector<COLORREF>());
	for( register int i=0; i<nHeight; ++i ) 
		{
		 m_Board[i].resize(nWidth, m_clrBackground);
		 for( register int j=0; j<nWidth; ++j )
			  m_Board[i][j] = m_clrBackground;
		}

	m_ulCompleteLines = 0;
	if(!m_bLevelSelected)
		m_usLevel = 0;
	m_bLevelSelected = FALSE;
	m_ulPieces = 0;
	m_uPoints = 0;

	if( m_uTimer )
		KillTimer(m_uTimer);
	m_uTimer = 0;

	if( m_pCurPiece )
		delete m_pCurPiece;
	m_pCurPiece = 0;
	if( m_pNextPiece )
		delete m_pNextPiece;
	m_pNextPiece = SelectPiece();

	NotifyParent();

	Paint();
}

void CGameBoard::MoveLeft()
  {
	ASSERT(m_pCurPiece);	// make sure we're inside a game

	if( CanPlace(m_nCurLine, m_nCurCol-1) )
		{
		 --m_nCurCol;
		 m_SndKey.Play();
		}
  }

void CGameBoard::MoveRight()
  {
	ASSERT(m_pCurPiece);	// make sure we're inside a game

	if( CanPlace(m_nCurLine, m_nCurCol+1) ) 
		{
		 ++m_nCurCol;
		 m_SndKey.Play();
		}
  }

void CGameBoard::Rotate() 
  {
	ASSERT(m_pCurPiece);	// make sure we're inside a game

	m_pCurPiece->Rotate();
	if( !CanPlace(m_nCurLine, m_nCurCol) )
		m_pCurPiece->BackRotate();
	else
		m_SndKey.Play();
  }

void CGameBoard::BackRotate() 
  {
	ASSERT(m_pCurPiece);	// make sure we're inside a game

	m_pCurPiece->BackRotate();
	if( !CanPlace(m_nCurLine, m_nCurCol) )
		m_pCurPiece->Rotate();
	else
		m_SndKey.Play();
  }

void CGameBoard::StartFall() 
	{
	if( m_uTimer ) 
		{
		 m_SndKey.Play();
		 ResetTimer(TRUE);	// increase speed to maximum
		}
	}

void CGameBoard::StopFall() 
	{	if( m_uTimer ) ResetTimer(); } // restore speed

void CGameBoard::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( m_pCurPiece ) 
		{
		switch(nChar) 
			{
			case VK_LEFT:
			case VK_NUMPAD4:
				MoveLeft();
				break;

			case VK_RIGHT:
			case VK_NUMPAD6:
				MoveRight();
				break;

			case VK_SPACE:
			case VK_NUMPAD5:
				Rotate();
				break;

			case VK_NUMPAD0:
				BackRotate();
				break;

			case VK_DOWN:
			case VK_NUMPAD2:
				if( !(nFlags & (1<<14)) ) 
					{
					 // the key was not down before
					 StartFall();
					}
				break;

			case VK_ADD:
			case VK_SUBTRACT:
			case TCHAR('+'):
			case TCHAR('-'):
				if(m_pMusicPlayer) 
					{
					 CVolumeCtrl dlg(m_pMusicPlayer);
					 dlg.DoModal();
					 m_dwVolume = dlg.GetVolume();
					}
				break;
			}
		}
	Paint();
	CWnd::OnChar(nChar, nRepCnt, nFlags);
}


void CGameBoard::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
  {
	if( nChar == VK_DOWN || nChar == VK_NUMPAD2 ) 
		{
		 if( (nFlags & (1<<14)) ) 
			 {
			  // the key was down before
			  StopFall();
			 }
		}
	else CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
  }


bool CGameBoard::CanPlace(int nLine, int nCol)
  {
	ASSERT( m_pCurPiece != 0 );

	register const int nCols = m_pCurPiece->GetColumns();
	register const int nLines = m_pCurPiece->GetLines();

	for( register int l = nLines - 1 ; l >= 0 ; l-- ) 
		{
		for( register int c = 0 ; c < nCols ; c++ ) 
			{
			register const int nL = nLine - ((nLines-1) & l) ;
			register const int nC = nCol + c;

			if( m_pCurPiece->IsSquare(l, c) ) 
				{
				if( nL >= Height() || nC < 0 || nC >= Width() )
					return false;
				else if( nL >= 0 && m_Board[nL][nC] != m_clrBackground )
					return false;
				}
			}
		}
	return true;
  }


void CGameBoard::CheckBoard()
{
 for( register int l = Height() - 1 ; l > 0 ; --l ) 
   {
	 bool bLineComplete = true;
	 for( register int c = Width() - 1 ; c >= 0 ; --c ) 
		{
	    ASSERT( l > 0 );
		 ASSERT( c >= 0 );
		 if( m_Board[l][c] == m_clrBackground ) 
         {
			 bLineComplete = false;
			 break;
			}
		}
	 if( bLineComplete )
		{
       {// show animated annihilation of that line
		  UINT * low = guBoomArray;
		  UINT * high = ENDVEC(guBoomArray);
		  CClientDC cdc(this);
		  int nWidth = Width();
		  m_SndLineComplete.Play();
		  while( low <= high ) 
			{
		    HICON hIcon = AfxGetApp()->LoadIcon(*low);
			 if( ! hIcon )
				break;
			 for( register int c1 = nWidth - 1; c1 >= 0; --c1 )
			   ::DrawIconEx(cdc.GetSafeHdc(), c1 *m_nSquareWidth, l *m_nSquareHeight, hIcon,
								 m_nSquareWidth, m_nSquareHeight, 0, 0, DI_NORMAL);
			 ::Sleep(100);
			 ++low;
			}// while
       }
		 // remove that line from the board
		 for( register int l1 = l ; l1 > 0 ; --l1 ) 
			{
		    for( register int c1 = Width() - 1 ; c1 >= 0 ; --c1 ) 
				{
			    ASSERT( l1 > 0 ) ;
				 ASSERT( c1 >= 0 ) ;
				 m_Board[l1][c1] = m_Board[l1-1][c1] ;
				}
         }
		 ++l ;	// try same line again ...
		 OnLineComplete();
		 m_SndPlace.Play();
		 Paint();
		}// if( bLineComplete )
	}// for( register int l ... )
}

void CGameBoard :: FixPiece() 
  {
	ASSERT( m_pCurPiece != 0 ) ;

	m_SndPlace.Play();

	register const int nCols = m_pCurPiece->GetColumns() ;
	register const int nLines = m_pCurPiece->GetLines() ;

	for( register int l = nLines - 1 ; l >= 0 ; l-- ) 
     {
		for( register int c = 0 ; c < nCols ; c++ )
        {
			if( m_pCurPiece->IsSquare( l, c ) ) 
           {
				int nL = m_nCurLine - ((nLines-1) & l) ;
				int nC = m_nCurCol + c ;
				if( nL >= 0 ) 
              {
					ASSERT( nL < Height() ) ;
					ASSERT( nC >= 0 ) ;
					ASSERT( nC < Width() ) ;
					m_Board[nL][nC] = m_clrCurPiece;
              }
           }
        }
     }
	m_uPoints += UINT(m_pCurPiece->GetPoints()) + m_usLevel + (m_bExFigures ? 10 : 0);
}

void CGameBoard::OnLineComplete()
  {
	++m_ulCompleteLines;
	m_uPoints += m_bExFigures ? 20 : 10;
	if( (m_ulCompleteLines % 10) == 0 ) 
     {
		m_SndLevelWarp.Play();
		++m_usLevel;
		m_uPoints += m_bExFigures ? 20 : 10;
		if( m_usLevel >= 2 && m_bShowGrid )
			m_bShowGrid = FALSE;

		ResetTimer();
     }
	NotifyParent();
  }

void CGameBoard::SetLevel(USHORT usLevel) 
  {
	m_usLevel = usLevel;

	if( !m_uTimer )
		// if we're not already in a game, we have to
		// remember, that the user preselected the level.
		m_bLevelSelected = TRUE;
	else
		// otherwise we have to make sure the new level
		// will change game behavior now.
		ResetTimer();
	
	// Show the player his/her selection
	NotifyParent();
  }

void CGameBoard::StartGame()
  {
	InitBoard();
	ResetTimer();
	if( m_pMusicPlayer )
		m_pMusicPlayer->StartMusic();
  }

void CGameBoard::StopGame()
  {
	KillTimer(m_uTimer);
	m_uTimer = 0;
	if( m_pMusicPlayer )
		m_pMusicPlayer->StopMusic();
  }

void CGameBoard::ResumeGame()
  {
	ResetTimer();
	if( m_pMusicPlayer )
		m_pMusicPlayer->ResumeMusic();
  }

void CGameBoard::PauseGame()
  {
	KillTimer(m_uTimer);
	if( m_pMusicPlayer )
		m_pMusicPlayer->PauseMusic();
  }

void CGameBoard :: OnNewPiece()
  {
	++m_ulPieces;
	NotifyParent();
	ResetTimer();
  }

void CGameBoard :: OnGameOver()
  {
	StopGame();
	CWnd *pParent = GetParent();
	ASSERT( pParent != 0 );

	m_BoardNotifier.hdr.hwndFrom = GetSafeHwnd();
	m_BoardNotifier.hdr.idFrom = UINT( ::GetWindowLong(GetSafeHwnd(), GWL_ID) );
	m_BoardNotifier.hdr.code = NMB_GAMEOVER;

	m_SndGameOver.Play();

	pParent->SendMessage( WM_NOTIFY, WPARAM(m_BoardNotifier.hdr.idFrom),
		                   LPARAM(&m_BoardNotifier.hdr) );
  }

void CGameBoard::OnTimer(UINT nIDEvent) 
  {
	if( m_pNextPiece == 0 ) 
     {
	   m_pNextPiece = SelectPiece();
	   NotifyParent(FALSE);
     }

	if( m_pCurPiece == 0 ) 
     {
	   m_pCurPiece = m_pNextPiece;
	   m_pNextPiece = 0;
		
	   do { m_clrCurPiece = RGB(rand()%255, rand()%255, rand()%255);
         } while( m_clrCurPiece == m_clrBackground );

		m_nCurLine = 1;
		if( m_usLevel >= 4 )
			// random startpoint ...
			m_nCurCol = rand() % (Width()-m_pCurPiece->GetColumns()) ;
		else
			// fixed (centered) startpoint ...
			m_nCurCol = (Width() - m_pCurPiece->GetColumns()) / 2 ;

		if( !CanPlace( m_nCurLine, m_nCurCol ) ) 
			{
			 OnGameOver();
			 return ;
			}
		OnNewPiece();
     }// 
	else
     {
		if( !CanPlace( m_nCurLine+1, m_nCurCol ) )
        {
			FixPiece() ;
			delete m_pCurPiece ;
			m_pCurPiece = 0 ;
			CheckBoard() ;
        }
		else
			m_nCurLine++ ;
     }
	Paint() ;
}

LRESULT CALLBACK GameBoardWndProc( HWND hWnd, UINT uiMsg, 
                                   WPARAM wParam, LPARAM lParam )
  {
	switch (uiMsg)	// Dispatch on message type
     {
	   case WM_NCCREATE:	// On WM_NCCREATE we create a C++ object and attach it to the control
        {
			CGameBoard *pCtl = new CGameBoard();	// Create an instance of the class
			ASSERT( pCtl );	// Better not fail!
			BOOL b = pCtl->SubclassWindow(hWnd);	// Attach the window handle to the new object
			ASSERT( b );		// Better not fail!
			return b;			// Return result to continue/abort window creation
			break;
        }
	   default:			// All other messages go through default window processor
		        return ::DefWindowProc(hWnd, uiMsg, wParam, lParam);
     }
  }

void CGameBoard::OnNcDestroy() 
  {
	CWnd::OnNcDestroy();

	// Make sure the window was destroyed
	ASSERT( NULL == m_hWnd );

	// Destroy this object since it won't be destroyed otherwise
	delete this;
  }

int CGameBoard::OnCreate(LPCREATESTRUCT lpCreateStruct) 
  {
	if( CWnd::OnCreate(lpCreateStruct) == -1 )
		return -1;

	// Set the styles for the parent control
	ModifyStyleEx(0, WS_EX_CLIENTEDGE | WS_EX_NOPARENTNOTIFY);

	m_SndKey.Create(IDR_SndKey);
	m_SndPlace.Create(IDR_SndPlace);
	m_SndLevelWarp.Create(IDR_SndLevelWarp);
	m_SndGameOver.Create(IDR_SndGameOver);
	m_SndLineComplete.Create(IDR_SndLineComplete);

	return 0;
  }

BOOL CGameBoard::OnEraseBkgnd(CDC* pDC) 
  { return TRUE; }

void CGameBoard :: NotifyParent(BOOL bStatistics /* = TRUE */)
  {
	CWnd *pParent = GetParent();
	ASSERT(pParent != 0);

	NMHDR & hdr = bStatistics ? m_BoardNotifier.hdr : m_PreviewNotifier.hdr;

	hdr.hwndFrom = GetSafeHwnd();
	hdr.idFrom = UINT(::GetWindowLong(GetSafeHwnd(), GWL_ID));
	hdr.code = bStatistics ? NMB_STATISTICS : NMB_PREVIEW;

	if( bStatistics ) 
     {
		m_BoardNotifier.level	= UINT(m_usLevel);
		m_BoardNotifier.lines	= UINT(m_ulCompleteLines);
		m_BoardNotifier.pieces	= UINT(m_ulPieces);
		m_BoardNotifier.points	= UINT(m_uPoints);
     }
	else 
     {
	   ASSERT(m_pNextPiece != 0);
	   m_PreviewNotifier.piece = m_pNextPiece;
     }

	pParent->SendMessage( WM_NOTIFY, WPARAM(hdr.idFrom), 
		                   bStatistics ? LPARAM(&m_BoardNotifier) 
											  : LPARAM(&m_PreviewNotifier) );
  }

CPiece *CGameBoard::SelectPiece()
  {
	CPiece *pPiece = 0;

	switch( rand() % (m_bExFigures ? 11 : 7) )
     {
		case 0:
			pPiece = new CLongPiece();
			break;
		case 1:
			pPiece = new CSquarePiece();
			break;
		case 2:
			pPiece = new CRevLShapePiece();
			break;
		case 3:
			pPiece = new CLShapePiece();
			break;
		case 4:
			pPiece = new CTeeShapePiece();
			break;
		case 5:
			pPiece = new CSShapePiece();
			break;
		case 6:
			pPiece = new CRevSShapePiece();
			break;
		case 7:
			pPiece = new CCrossShapePiece();
			break;
		case 8:
			pPiece = new CUShapePiece();
			break;
		case 9:
			pPiece = new CZShapePiece();
			break;
		case 10:
			pPiece = new CRevZShapePiece();
			break;
     }

	ASSERT( pPiece != 0 );
	return pPiece;
 }

void CGameBoard::ResetTimer(BOOL bSpeed)
  {
	if( m_uTimer )
		KillTimer(m_uTimer);
	srand(time(0));
	UINT uElaps = (m_usLevel < 20 && ! bSpeed) ? 500-(m_usLevel*25) : 50 ;
	m_uTimer = SetTimer(2, uElaps, 0);
  }

void CGameBoard::EnableSound(BOOL bEnable) 
  {
	m_SndKey.EnableSound(bEnable);
	m_SndPlace.EnableSound(bEnable);
	m_SndLevelWarp.EnableSound(bEnable);
	m_SndGameOver.EnableSound(bEnable);
	m_SndLineComplete.EnableSound(bEnable);
  }

void CGameBoard::EnableMusic(BOOL bEnable) 
	{
	 if(m_pMusicPlayer)
		 m_pMusicPlayer->EnableMusic(bEnable?true:false);
	}


void CGameBoard::SetMusicType(UINT uResource)
  {
   /* if( uResource == IDM_FromFile )
		   EnableMusic(FALSE);	// a call to SetMusicFile() will come soon

	if( m_pMusic ) {
		m_pMusic->Create(uResource, this);
		m_pMusic->SetVolume(m_dwVolume);
	}*/

	if(m_pMusicPlayer)
		m_pMusicPlayer->Set(uResource);
  }

void CGameBoard::SetMusicSequence(BOOL bSet) 
	{
	 if(m_pMusicPlayer)
	   m_pMusicPlayer->SetSequence(bSet?true:false);
	}

void CGameBoard::OnMouseMove(UINT nFlags, CPoint point) 
  {
	::SetCursor(0);
	CWnd::OnMouseMove(nFlags, point);
  }


void CGameBoard::SetVolume(DWORD dwPercent) 
  {
	ASSERT( dwPercent <= 100 );
	//m_dwVolume = dwPercent;
	if( m_pMusicPlayer )
		m_pMusicPlayer->SetVolume( dwPercent );
  }


void CGameBoard::SetMusicFile(const CString & strFile) 
  {
	if(m_pMusicPlayer) 
     {
		TCHAR chName[_MAX_PATH];
		::GetModuleFileName(0, chName, _MAX_PATH);
		TCHAR chDrive[_MAX_DRIVE];
		TCHAR chDir[_MAX_PATH];
		::_tsplitpath(chName, chDrive, chDir, 0, 0);
		m_strMusicFile = chDrive;
		m_strMusicFile += chDir + strFile + TEXT(".mid");

		m_pMusicPlayer->Set(m_strMusicFile);
     }
  }

void CGameBoard::OnSysColorChange() 
  {
	m_clrTopLeft = ::GetSysColor(COLOR_BTNHILIGHT);
	m_clrBottomRight = ::GetSysColor(COLOR_BTNSHADOW);
	CWnd::OnSysColorChange();
  }
