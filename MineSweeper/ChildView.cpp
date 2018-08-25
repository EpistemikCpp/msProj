// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "MineSweeper.h"
#include "MainFrm.h"
#include "ChildView.h"
#include "CustomMines.h"
#include "BestTimes.h"
#include "FastestTime.h"
#include "Sound.h"


#include "ColorsRGB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

COLORREF colorRef[] = {
	RGB_WHITE,
	RGB_BLACK,
	RGB_GRAY_Lt,
	RGB_GRAY_Dk,
	RGB_RED_Lt,
	RGB_RED,
	RGB_GREEN_Lt,
	RGB_GREEN,
	RGB_GREEN_Dk,
	RGB_GREEN_Dkr,
	RGB_BLUE_Lt,
	RGB_BLUE,
	RGB_BLUE_Dk,
	RGB_YELLOW,
	RGB_MAGENTA_Lt,
	RGB_BROWN_Red,
	RGB_CYAN
};

#define NumberOfColorRefs (sizeof(colorRef) / sizeof(colorRef[0]))

enum Color {
	Color_White,
	Color_Black,
	Color_LtGray,
	Color_DkGray,
	Color_LtRed,
	Color_Red,
	Color_LtGreen,
	Color_Green,
	Color_DkGreen,
	Color_DkrGreen,
	Color_LtBlue,
	Color_Blue,
	Color_DkBlue,
	Color_Yellow,
	Color_LtMagenta,
	Color_BrownRed,
	Color_Cyan,
	NumberOfColors		// Must be last line in enum Color
};


Color	currentTxtColor;
Color	currentBkColor;

Color	currentFillColor;
int		currentFillStyle;

HBRUSH  colorBrush [NumberOfColors];

enum sqMineMark{
	sqMineMarkNone,
	sqMineMarkHard,
	sqMineMarkSoft,
	sqMineMarkShow
};
#define MINE (unsigned int)(255-'0')	/* So that when it prints, it prints char 0xff */

typedef unsigned int uint;

typedef struct stsquare {
			uint sqValue;	/* MINE or Number of mines in the surround squares */
   sqMineMark	 sqMark;	/* Square mine mark 0, 1, 2 */
			bool sqOpen;	/* Square is open */
			bool sqPress;	/* Square is pressed */
			bool sqDirty;	/* Square Changed since last displayed */
			bool sqVisited;	/* Square Visited by Open_square */
}STSQUARE;

STSQUARE *psquare = NULL;
STSQUARE DummySquare = {0,sqMineMarkNone,false,false,false,true};

int nSqMines		= 0;
int	nSqMinesOpen	= 0;
int nSqMarkHard		= 0;
int nSqMarkSoft		= 0;
int nSqOpen			= 0;
int nSqPress		= 0;
int nSqDirty		= 0;

#define sqInited			(psquare!=NULL)
#define bValidX(x)			(x>=0&&x<nSqWide)
#define bValidY(y)			(y>=0&&y<nSqHigh)
#define bValidXY(x,y)		(bValidX(x)&&bValidY(y))
#define OffsetToPixelX(x)	(OffsetToLeftSq+SqWidth*x)
#define OffsetToPixelY(y)	(OffsetToTopSq+SqHeight*y)

#define mx			(1)
#define SqWidth		(16*mx)	/* square pixels Wide */
#define SqHeight	(16*mx)	/* square pixels High */

int	OffsetToLeftSq = 11;	/* Offset of first pixel X */
int OffsetToTopSq  = 53;	/* Offset of first pixel Y */

int	nSqWide		= 0;	/* Number of squares side to side   on playing field */
int	nSqHigh		= 0;	/* Number of squares top  to bottom on playing field */
int	nInitMines	= 0;	/* Number of initial mines */

long timeStart	= 0;
long timeElapse = 0;

bool bGameStarted	= false;
bool bGameOver		= false;
bool bWin			= false;

int		displayWindowWidth  = 0;
int		displayWindowHeight = 0;

RECT	playField;
#define playFieldWidth  (playField.right  - playField.left)
#define playFieldHeight (playField.bottom - playField.top)

RECT	ledMines;
RECT	ledTimer;
RECT	ledSmile;

int ledOffset	= (6*mx);
int ledWidth	= (13*mx);
int ledHeight	= (23*mx);
int faceWidth	= (26*mx);
int faceHeight	= (26*mx);
int iConTop		= (OffsetToTopSq/2 - faceHeight/2);



/*************************************************************************
*                                                                        *
*                           P R O T O T Y P E S                          *
*                                                                        *
*************************************************************************/


#define SOLID_FILL	1

#define LEFT_TEXT	1
#define CENTER_TEXT 2

int mouse_status;
int mouse_x;
int mouse_y;
int	mouse_horizontal_range_min;
int	mouse_horizontal_range_max;
int	mouse_vertical_range_min;
int	mouse_vertical_range_max;


HDC CChildView::My_hDisp (void)
{
	static HDC hDisp = NULL;
	if (hDisp == NULL)
		hDisp = CChildView::GetDC()->m_hDC;

	return hDisp;
}
#define hDisp (My_hDisp())


/*************************************************************************
*                                                                        *
*                           F U N C T I O N S                            *
*                                                                        *
*************************************************************************/

char debugBuff[200];

STSQUARE* sqPtr(int x, int y)
{
	if (!bValidXY(x,y))
	{
		sprintf(debugBuff, "sqPtr(%d, %d)", x, y);
		MessageBox(0, debugBuff, "", MB_OK);
		return &DummySquare;
	}
	STSQUARE* ps;
	if(!sqInited)
		ps = &DummySquare;
	else
		ps = psquare+(x)*nSqHigh+(y);
	return ps;
}

uint& sqValue(int x, int y)
{
	if (!bValidXY(x,y))
	{
		sprintf(debugBuff, "sqValue(%d, %d)", x, y);
		MessageBox(0, debugBuff, "", MB_OK);
	}
	STSQUARE *ps = sqPtr(x,y);
	return ps->sqValue;
}
sqMineMark& sqMark(int x, int y)
{
	if (!bValidXY(x,y))
	{
		sprintf(debugBuff, "sqMark(%d, %d)", x, y);
		MessageBox(0, debugBuff, "", MB_OK);
	}
	STSQUARE *ps = sqPtr(x,y);
	return ps->sqMark;
}

bool& sqOpen(int x, int y)
{
	if (!bValidXY(x,y))
	{
		sprintf(debugBuff, "sqOpen(%d, %d)", x, y);
		MessageBox(0, debugBuff, "", MB_OK);
	}
	STSQUARE *ps = sqPtr(x,y);
	return ps->sqOpen;
}
bool& sqPress(int x, int y)
{
	if (!bValidXY(x,y))
	{
		sprintf(debugBuff, "sqPress(%d, %d)", x, y);
		MessageBox(0, debugBuff, "", MB_OK);
	}
	STSQUARE *ps = sqPtr(x,y);
	return ps->sqPress;
}
bool& sqDirty(int x, int y)
{
	if (!bValidXY(x,y))
	{
		sprintf(debugBuff, "sqDirty(%d, %d)", x, y);
		MessageBox(0, debugBuff, "", MB_OK);
	}
	STSQUARE *ps = sqPtr(x,y);
	return ps->sqDirty;
}
bool& sqVisited(int x, int y)
{
	if (!bValidXY(x,y))
	{
		sprintf(debugBuff, "sqVisited(%d, %d)", x, y);
		MessageBox(0, debugBuff, "", MB_OK);
	}
	STSQUARE *ps = sqPtr(x,y);
	return ps->sqVisited;
}

/*----------------------------------------------------------------------*/


void CChildView::randomize()
{
   srand( (unsigned)time( NULL ) );
}

int CChildView::random(int maxRet)
{
	int randGen;
	int randRet;
	randGen = rand();
	randRet = randGen % (maxRet);
	return randRet;
}

void CChildView::MouseSetRange(void)
{
   mouse_horizontal_range(OffsetToLeftSq, OffsetToLeftSq+SqWidth*nSqWide-3);
   mouse_vertical_range(OffsetToTopSq, OffsetToTopSq+SqHeight*nSqHigh-3);
}

void  CChildView::mouse_reset(void)
{
	mouse_status &= ~MOUSEEVENTF_RIGHTUP;
	mouse_status &= ~MOUSEEVENTF_LEFTUP;
}
void CChildView::mouse_horizontal_range(int xmin, int xmax)
{
	mouse_horizontal_range_min = xmin;
	mouse_horizontal_range_max = xmax;
}
void CChildView::mouse_vertical_range(int ymin, int ymax)
{
	mouse_vertical_range_min = ymin;
	mouse_vertical_range_max = ymax;
}

void CChildView::setcolor(Color color)
{
	currentTxtColor = color;
}
void CChildView::setfillstyle(int style, Color color)
{
	currentFillStyle = style;
	currentFillColor = color;
}
void CChildView::bar(int xl, int yt, int xr, int yb)
{
	if (hDisp)
	{
		
		SelectObject(hDisp, colorBrush[currentFillColor]);
		PatBlt(hDisp, xl, yt, xr-xl+1, yb-yt+1, PATCOPY);
	}
}
void CChildView::line(int xl,int yt, int xr, int yb)
{
	int xExt = max(xr-xl+1,1);
	int yExt = max(yb-yt+1,1);

	if (hDisp)
	{
		SelectObject(hDisp ,colorBrush[currentFillColor]);

	//  MoveToEx(hDisp, xl, yt, NULL);
	//  LineTo(hDisp, xr, yb);
		PatBlt(hDisp ,xl, yt, xExt, yExt, PATCOPY);
	}
}
 
void CChildView::fillellipse(int xl, int yt, int Ex, int Ey)
{
	if (hDisp)
	{
		SelectObject(hDisp, colorBrush[currentFillColor]);
		Ellipse(hDisp, xl, yt, xl+Ex, yt+Ey);
	}
}
void CChildView::settextjustify(int p1, int p2)
{
}
void CChildView::outtextxy(int x, int y, char* txt)
{
	if (hDisp)
	{
		SetTextColor(hDisp, colorRef[currentTxtColor]);
		TextOut(hDisp, x, y, txt, strlen(txt));
	}
}


/*----------------------------------------------------------------------*/


/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
	m_pCWinApp = NULL;
	m_pCFrameWnd = NULL;
}

CChildView::~CChildView()
{
	if(psquare != NULL)
		free(psquare);
	psquare = NULL;
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_TIMER()
	ON_COMMAND(ID_GAME_NEW, OnGameNew)
	ON_COMMAND(ID_GAME_BEGINNER, OnGameBeginner)
	ON_COMMAND(ID_GAME_INTERMEDIATE, OnGameIntermediate)
	ON_COMMAND(ID_GAME_EXPERT, OnGameExpert)
	ON_COMMAND(ID_GAME_CUSTOM, OnGameCustom)
	ON_COMMAND(ID_GAME_MARKS, OnGameMarks)
	ON_COMMAND(ID_GAME_COLOR, OnGameColor)
	ON_COMMAND(ID_GAME_SOUND, OnGameSound)
	ON_COMMAND(ID_GAME_BEST_TIMES, OnGameBestTimes)
	ON_UPDATE_COMMAND_UI(ID_GAME_BEGINNER, OnUpdateGameBeginner)
	ON_UPDATE_COMMAND_UI(ID_GAME_INTERMEDIATE, OnUpdateGameIntermediate)
	ON_UPDATE_COMMAND_UI(ID_GAME_EXPERT, OnUpdateGameExpert)
	ON_UPDATE_COMMAND_UI(ID_GAME_MARKS, OnUpdateGameMarks)
	ON_UPDATE_COMMAND_UI(ID_GAME_COLOR, OnUpdateGameColor)
	ON_UPDATE_COMMAND_UI(ID_GAME_SOUND, OnUpdateGameSound)
	ON_WM_MOUSEMOVE()
	ON_WM_MOVE()
	ON_WM_RBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

unsigned short IconTable[] = {
	IDI_Sq_0,
	IDI_Sq_1,
	IDI_Sq_2,
	IDI_Sq_3,
	IDI_Sq_4,
	IDI_Sq_5,
	IDI_Sq_6,
	IDI_Sq_7,
	IDI_Sq_8,
	IDI_Sq_Flag,
	IDI_Sq_Question,
	IDI_Sq_Mine,
	IDI_Sq_Mine_Red,
	IDI_Sq_Mine_Wrong
};

HICON CChildView::LoadIcon( LPCTSTR lpszResourceName, bool bMonochrome, int cx, int cy ) const
{
	HICON hIcon = 0;
	return hIcon;
}

HICON CChildView::LoadIcon( UINT nIDResource, bool bMonochrome, int cx, int cy) const
{
static	HICON hIcon = NULL;
#if 1
	UINT fuLoad = LR_DEFAULTCOLOR;
	if(hIcon != NULL)
		DestroyIcon(hIcon);

   	if (bMonochrome)
		fuLoad = LR_MONOCHROME;
	else
		fuLoad = LR_DEFAULTCOLOR;

	hIcon  = (HICON)::LoadImage(AfxGetApp()->m_hInstance,
						MAKEINTRESOURCE(nIDResource),
                        IMAGE_ICON,
                        0, 0, fuLoad);
#else
	hIcon = AfxGetApp()->LoadIcon(nIDResource);
#endif
	return hIcon;
}


void CChildView::DrawButton(RECT& b, UINT nIdIcon, bool bSqPress, int upWidth, int pressWidth)
{
	int iconWidth = b.right - b.left + 1;
	int iconHeight = b.bottom - b.top + 1;

	SetBkColor(hDisp, colorRef[Color_LtGray]);

	HICON hIcon;
	if (!m_GameColor)
	{
		UINT nIdBackGrnd;
		if (iconWidth == SqWidth)
		{
			if (bSqPress)
				nIdBackGrnd = IDI_Sq_0;
			else
				nIdBackGrnd = IDI_Sq_Mono;
		}
		else
		{
			nIdBackGrnd = IDI_IcoFace_Mono;
		}

		hIcon = LoadIcon(nIdBackGrnd, !m_GameColor, iconWidth, iconHeight);
		DrawIcon(hDisp, b.left, b.top , hIcon);
	}
	else
	{
		setfillstyle(SOLID_FILL, Color_LtGray);
		bar(b.left, b.top, b.right, b.bottom);
	}

	if (bSqPress)
	{
		int ii;
		int lWidth = __max(0,pressWidth>0?pressWidth:upWidth);
		int rWidth = __max(0,lWidth-1);
		setfillstyle(SOLID_FILL,Color_DkGray);
		for (ii = 0; ii < lWidth; ++ii) // Draw Dark Gray on left and top of window
		{
			line(b.left+ii, b.top+ii, b.left +ii, b.bottom+ii); // Left
			line(b.left+ii, b.top+ii, b.right+ii, b.top   +ii); // Top
		}
		setfillstyle(SOLID_FILL,Color_DkGray);
		for (ii = 0; ii < rWidth; ++ii) // Draw Dark Gray on right and bottom of window
		{
			line(b.right-ii, b.top   +ii, b.right-ii, b.bottom-ii); // Right
			line(b.left +ii, b.bottom-ii, b.right-ii, b.bottom-ii); // Bottom
		}
	}
	else
	{
		DrawShade(b, upWidth, !bSqPress);
	}
	if (nIdIcon)
	{
		HICON hIcon = LoadIcon(nIdIcon, !m_GameColor, iconWidth, iconHeight);
		DrawIcon(hDisp, b.left, b.top , hIcon);
	}
}

void CChildView::DrawShade(RECT& b, int width, bool bOutSideIn)
{
	static int busy = -1;
	if (!++busy)
	{
		int ii;
		if (bOutSideIn)
		{
			setfillstyle(SOLID_FILL,Color_White);
			for (ii = 0; ii < width; ++ii) // Draw White on left and top of window
			{
				line(b.left+ii, b.top+ii, b.left +ii, b.bottom-ii-1); // Left
				line(b.left+ii, b.top+ii, b.right-ii-1, b.top   +ii); // Top
			}
			setfillstyle(SOLID_FILL,Color_DkGray);
			for (ii = 0; ii < width; ++ii) // Draw Dark Gray on right and bottom of window
			{
				line(b.right-ii, b.top   +ii, b.right-ii, b.bottom-ii); // Right
				line(b.left +ii, b.bottom-ii, b.right-ii, b.bottom-ii); // Bottom
			}
		}
		else // InSideOut
		{
			setfillstyle(SOLID_FILL,Color_DkGray);
			for (ii = 1; ii <= width; ++ii) // Draw Dark Gray on left and top of window
			{
				line(b.left-ii, b.top-ii, b.left -ii, b.bottom+ii); // Left
				line(b.left-ii, b.top-ii, b.right+ii, b.top   -ii); // Top
			}
			setfillstyle(SOLID_FILL,Color_White);
			for (ii = 1; ii <= width; ++ii) // Draw White on right and bottom of window
			{
				line(b.right+ii, b.top   -ii, b.right+ii, b.bottom+ii); // Right
				line(b.left -ii, b.bottom+ii, b.right+ii, b.bottom+ii); // Bottom
			}
		}
	}
	--busy;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	RECT rect;           // rectangle
	CBrush cBrush;

	cBrush.CreateSolidBrush(colorRef[Color_LtGray]);

	rect.left		= 0;
	rect.top		= 0;
	rect.right		= displayWindowWidth;
	rect.bottom		= displayWindowHeight;

	dc.FillRect(&rect, &cBrush);

	DrawShade(rect, 3);
	DrawShade(playField, 3, false);
	
	int d1 = 6;
	int d2 = 5;
	RECT rect2 = {ledMines.left - d1, ledMines.top - d2, ledTimer.right + d1, ledTimer.bottom + d2};
	DrawShade(rect2, 2, false);

	DrawShade(ledMines, 1, false);
	DrawShade(ledTimer, 1, false);


	DisplayBoard(true);

	// Do not call CWnd::OnPaint() for painting messages
}




/*----------------------------------------------------------------------*/

void CChildView::ResetGame(void)
{
	COLORREF colorRGB;

	ASSERT(NumberOfColorRefs==NumberOfColors);

	for (int ii = 0; ii < NumberOfColors; ii++)
	{
		colorRGB = colorRef[ii];
		colorBrush [ii] = CreateSolidBrush(colorRGB);
	}

	SetBoardDimAndNumMines();
	randomize();

	ClearBoard();
	MouseSetRange();
	mouse_status = 0;

	bGameStarted = false;
	bGameOver = false;
	bWin = false;

	timeStart = 0;
	timeElapse = 0;
	m_bTimeRecorded = false;
	PostMessage(WM_TIMER);
}
/*----------------------------------------------------------------------*/

int CChildView::SetBoardDimAndNumMines(void)
{
	GetProfileParams();
	switch(m_GameLevel)
	{
	case	ID_GAME_BEGINNER:
			nSqWide = 9;
			nSqHigh = 9;
			nInitMines = 10;
		break;
	case	ID_GAME_INTERMEDIATE:
			nSqWide = 16;
			nSqHigh = 16;
			nInitMines = 40;
		break;
	case	ID_GAME_EXPERT:
			nSqWide = 30;
			nSqHigh = 16;
			nInitMines = 99;
		break;
	case	ID_GAME_CUSTOM:
			nSqWide = m_CustomX;
			nSqHigh = m_CustomY;
			nInitMines = m_CustomM;
		break;
	default:
			nSqWide = 18;
			nSqHigh = 18;
			nInitMines = nSqWide*nSqHigh/10;
		break;
	}

	if(psquare != NULL)
		free(psquare);

	psquare = (STSQUARE *)calloc(nSqWide*nSqHigh, sizeof(STSQUARE));

   if (psquare==NULL)
   {
      MessageBox("ERROR: Not enought memory");
      return(3);
   }
   SetBoardWindow();
   return(0);
}

/*----------------------------------------------------------------------*/

void CChildView::CountBoardInfo(void)
{
	nSqMines = 0;
	nSqMinesOpen = 0;
   	nSqMarkHard = 0;
   	nSqMarkSoft = 0;
	nSqOpen = 0;
	nSqPress = 0;
	nSqDirty = 0;

	for (int x = 0; bValidX(x); x++) for (int y = 0; bValidY(y); y++)
	{
		STSQUARE *p = sqPtr(x,y);
		if (p->sqValue == MINE)
		{
			nSqMines++;
			if (p->sqOpen)
				nSqMinesOpen++;
		}
		if (p->sqMark == sqMineMarkHard)
   			nSqMarkHard++;
		if (p->sqMark == sqMineMarkSoft)
   			nSqMarkSoft++;

		if (p->sqOpen)
			nSqOpen++;
		if (p->sqPress)
			nSqPress++;
		if (p->sqDirty)
			nSqDirty++;
	}
	if( (nSqOpen + nSqMines) == nSqWide*nSqHigh )
	{
		bGameOver = true;
		bWin = true;
	}
	if (nSqMinesOpen > 0)
	{
		bGameOver = true;
		bWin = false;
	}
}

void CChildView::ClearBoard(void)
{
	for (int x = 0; bValidX(x); x++) for (int y = 0; bValidY(y); y++)
	{
		STSQUARE *p = sqPtr(x,y);
		p->sqValue	= 0;
		p->sqMark	= sqMineMarkNone;
		p->sqOpen	= false;
		p->sqPress	= false;
		p->sqDirty	= true;
		p->sqVisited= false;
	}
}

void CChildView::SetupMines(int nMines)
{
   int x, y;
   int a, b;
   int i;

	for (i=nMines; i>0; i--)
	{
		do
		{
			x = random(nSqWide);
			y = random(nSqHigh);
		}
      while ( sqPress(x,y) || (sqValue(x,y) == MINE) );
			
      sqValue(x,y)=MINE;
	}

   for (x=nSqWide-1; x>=0; x--)
   {
      for (y=nSqHigh-1; y>=0; y--)
	  {
		if (sqValue(x,y) == MINE)
			continue;
		for (a = x-1; a <= x+1; a++) for (b = y-1; b <= y+1; b++)
		{
			if (bValidXY(a,b))
				sqValue(x,y) += (sqValue(a,b) == MINE);
		}
	  }
   }
}

/*----------------------------------------------------------------------*/

void CChildView::Display_square(int x, int y)
{
	if (! sqDirty(x,y))
		return;

	if (hDisp == NULL)
		return;

	int	xl = OffsetToPixelX(x);
	int	xr = xl+SqWidth-1;
	int	yt = OffsetToPixelY(y);
	int	yb = yt+SqHeight-1;
	RECT b = {xl,yt,xr,yb};

	if (sqOpen(x,y))
	{
		if (sqMark(x,y)==sqMineMarkShow)
		{
			DrawButton(b, IDI_Sq_Mine, sqOpen(x,y)||sqPress(x,y), 2, 1);
		}
		else if (sqValue(x,y) == MINE)
		{
			if (m_GameColor)
				DrawButton(b, IDI_Sq_Mine_Red, sqOpen(x,y)||sqPress(x,y), 2, 1);
			else
				DrawButton(b, IDI_Sq_Mine_Red_Mono, sqOpen(x,y)||sqPress(x,y), 2, 1);
		}
		else if (sqMark(x,y)==sqMineMarkHard)
		{
			if (m_GameColor)
				DrawButton(b, IDI_Sq_Mine_Wrong, sqOpen(x,y)||sqPress(x,y), 2, 1);
			else
				DrawButton(b, IDI_Sq_Mine_Wrong_Mono, sqOpen(x,y)||sqPress(x,y), 2, 1);
		}
		else	if (sqValue(x,y) != 0)
		{
			DrawButton(b, IconTable[sqValue(x,y)], sqOpen(x,y)||sqPress(x,y), 2, 1);
		}
		else
		{
			DrawButton(b, 0, sqOpen(x,y)||sqPress(x,y), 2, 1);
		}
	}
	else // NOT Open yet
	{
		if (sqMark(x,y) != sqMineMarkNone)
		{
			switch (sqMark(x,y))
			{
				case sqMineMarkHard :
						DrawButton(b, IDI_Sq_Flag, sqOpen(x,y)||sqPress(x,y), 2, 1);
					break;
				case sqMineMarkSoft :
						DrawButton(b, IDI_Sq_Question, sqOpen(x,y)||sqPress(x,y), 2, 1);
					break;
				default:
					break;
			}
		}
		else
		{
			DrawButton(b, 0, sqOpen(x,y)||sqPress(x,y), 2, 1);
		}
	}

	sqDirty(x,y) = false;
	sqVisited(x,y) = false;
}


/*----------------------------------------------------------------------*/

void CChildView::Draw_squares(void)
{
	int x, y;

	for (x=0; x < nSqWide; x++)
	{
		for (y=0; y < nSqHigh; y++)
		{
			Display_square(x,y);
		}
	}
}

/*----------------------------------------------------------------------*/

void CChildView::UnPressAllSquaresExcept(int xPress, int yPress)
{
	int x, y;

	for (x=0; x < nSqWide; x++)
	{
		for (y=0; y < nSqHigh; y++)
		{
			if (! (x == xPress && y == yPress) )
			{
				if ( sqPress(x,y) )
				{
					sqPress(x,y) = false;
					sqDirty(x,y) = true;
				}
			}
		}
	}
}

/*----------------------------------------------------------------------*/

/*
   Here we do all the job
*/
void CChildView::Do_all(void)
{
	static int busy = -1;

	if (++busy)
	{
		--busy;
		return;
	}

	if (	mouse_x > ledSmile.left
		&&	mouse_x < ledSmile.right
		&&	mouse_y > ledSmile.top
		&&	mouse_y < ledSmile.bottom
		)
	{
		if (mouse_status==MOUSEEVENTF_LEFTDOWN)
		{
			if (hDisp!=NULL)
			{
				DrawButton(ledSmile, IDI_IcoFacePressed, true);
			}
		}

		if (mouse_status==MOUSEEVENTF_LEFTUP)
		{
			PostMessage(WM_COMMAND, ID_GAME_NEW,0);
		}
		--busy;
		return;
	}

	if (	mouse_x < mouse_horizontal_range_min
		||	mouse_x > mouse_horizontal_range_max
		||	mouse_y < mouse_vertical_range_min
		||	mouse_y > mouse_vertical_range_max
		)
	{
		--busy;
		return;
	}

	if (bGameOver)
	{
		--busy;
		return;
	}

	static int bMarkOk = true;

	int x=(mouse_x-OffsetToLeftSq)/SqWidth;
	int y=(mouse_y-OffsetToTopSq)/SqHeight;

	UnPressAllSquaresExcept(x,y);

	if (sqOpen(x,y))
	{
		if (mouse_status==(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_RIGHTDOWN))
		{	/* Open near squares */
			Open_near_squares(x, y, true);
		}
		else if (mouse_status==(MOUSEEVENTF_LEFTUP|MOUSEEVENTF_RIGHTUP))
		{	/* Open near squares */
			Open_near_squares(x, y);
		}
	}
	else if (	(mouse_status == MOUSEEVENTF_RIGHTDOWN)
			&& (bMarkOk)
		)
	{						
		sqMark(x,y)=(sqMineMark)((sqMark(x,y)+1) % m_GameMarks);
		sqPress(x,y) = false;
		sqDirty(x,y) = true;
		bMarkOk = false;
	}
	else if (mouse_status == MOUSEEVENTF_RIGHTUP)
	{
		bMarkOk = true;
	}
	else if (mouse_status==MOUSEEVENTF_LEFTDOWN
			&&sqMark(x,y)!=sqMineMarkHard
			)
	{
		sqPress(x,y)= true;
		sqDirty(x,y) = true;
	}
	else if (mouse_status==MOUSEEVENTF_LEFTUP
			&& sqPress(x,y)
			&& sqMark(x,y)!=sqMineMarkHard
			)
	{    	/* Open the square */
		StartGame();
		Open_square(x,y,false);
	}
	DisplayBoard();

	--busy;
	return;
}


/*----------------------------------------------------------------------*/

void CChildView::ShowMines(bool bWin)
{
   int x, y;

   for (x=0; x<nSqWide; x++)
   {
      for (y=0; y<nSqHigh; y++)
	  {
			if (sqValue(x,y) == MINE)
			{
				if (!sqOpen(x,y) && sqMark(x,y)!=sqMineMarkHard)
				{
					if (bWin)
					{
						sqMark(x,y) = sqMineMarkHard;
					}
					else
					{
						sqMark(x,y) = sqMineMarkShow;
						sqOpen(x,y) = true;
					}
					sqDirty(x,y)= true;
				}
			}
			else if (sqMark(x,y)==sqMineMarkHard)
			{
				sqOpen(x,y) = true;
				sqDirty(x,y)= true;
			}
      }
   }
}


/*----------------------------------------------------------------------*/
// returns false if explosion
// returns true  if OK
/*----------------------------------------------------------------------*/

bool CChildView::Open_square(int x, int y, bool bOpenMine)
{
	bool bRc = true;
	int x1;
	int y1;

	if (!bValidXY(x,y))
		return bRc;
	if (sqVisited(x,y))
		return bRc;

	sqVisited(x,y) = true;

	if (sqOpen(x,y) || sqMark(x,y) == sqMineMarkHard)
		return bRc;
	if (! bOpenMine && !sqPress(x,y) && sqValue(x,y) == MINE)
		return bRc;

	sqDirty(x,y)= true;
	sqOpen(x,y)	= true;
	sqPress(x,y)= false;

	if (sqValue(x,y) == MINE)
		return false;

	if (sqValue(x,y) != 0)
		return true;


	for (x1 = x-1; x1 <= x+1; ++ x1)
	{
		for (y1 = y-1; y1 <= y+1; ++ y1)
		{
			if (!bValidXY(x,y))
				continue;

			if (x1 == x && y1 == y)	// skip orignal square
				continue;

			bRc = Open_square(x1, y1, bOpenMine);
			if (! bRc)
				return bRc;
		}
	}
	return bRc;
}	/* Open_square */

/*----------------------------------------------------------------------*/


/*
   Open the sorrounded squares
*/
void CChildView::Open_near_squares(int x, int y, bool bPressOnly)
{
	int a, b;
	uint	suma = 0;

	for (a = x-1; a <= x+1; a++) for (b = y-1; b <= y+1; b++)
	{
		if (bValidXY(a,b) && sqMark(a,b)==sqMineMarkHard)
			suma++;
	}
	if (suma == sqValue(x,y))
	{
		for (a = x-1; a <= x+1; a++) for (b = y-1; b <= y+1; b++)
		{
			if (bValidXY(a,b) && !sqOpen(a,b) && sqMark(a,b)!=sqMineMarkHard)
			{
				if (bPressOnly)
				{
					sqPress(a,b) = true;
					sqDirty(a,b) = true;
				}
				else
				{
					Open_square(a,b, true);
				}
			}
		}
	}
}

void CChildView::MarkAllSquaresDirty()
{
	static busy = -1;
	if(!++busy)
	{
		int x;
		int	y;
		for (x=0; x < nSqWide; x++)
			for (y=0; y < nSqHigh; y++)
				sqDirty(x,y) = true;
	}
	--busy;
}

void CChildView::StartGame()
{
	if (!bGameStarted)
	{
		timeElapse = 0;
		bGameStarted = true;
		time(&timeStart);
//		SetTimer( 1, 1000, NULL);
		SetupMines(nInitMines);
		CountBoardInfo();
		PostMessage(WM_TIMER);
	}
}

unsigned short LedTable[] = {
	IDI_LED_0,
	IDI_LED_1,
	IDI_LED_2,
	IDI_LED_3,
	IDI_LED_4,
	IDI_LED_5,
	IDI_LED_6,
	IDI_LED_7,
	IDI_LED_8,
	IDI_LED_9
};

void CChildView::DisplayLedNum(RECT &rect, int num)
{
	static int busy = -1;
	HICON hIcon;
	if (!++busy)
	{
		if (hDisp!=NULL)
		{
			int d100 = num / 100;
			int d10	= (num - d100*100) / 10;
			int d1 = num - d100*100 - d10*10;
			int left = rect.left;
			int top	= rect.top;

			if (num > 999)
				num = 999;

			if (num < 0)
				num = 0;
			if (m_GameColor)
				setfillstyle(SOLID_FILL, Color_Red);
			else
				setfillstyle(SOLID_FILL, Color_White);
				
			bar(rect.left, rect.top, rect.right, rect.bottom);

			hIcon = LoadIcon(LedTable[d100], !m_GameColor, ledWidth, ledHeight);
			DrawIcon(hDisp, left, top , hIcon);
//			FreeResource(hIcon);
			left += ledWidth;
			hIcon = LoadIcon(LedTable[d10], !m_GameColor, ledWidth, ledHeight);
			DrawIcon(hDisp, left, top , hIcon);
//			FreeResource(hIcon);
			left += ledWidth;
			hIcon = LoadIcon(LedTable[d1], !m_GameColor, ledWidth, ledHeight);
			DrawIcon(hDisp, left, top , hIcon);
//			FreeResource(hIcon);
		}
	}
	--busy;
}

void CChildView::DisplayMineCount(bool bDirty) 
{
	static busy = -1;
	if (!++busy)
	{
		static int prevMineCount = 0;
		int		nDispMines;
		if (bGameOver && bWin)
			nDispMines = 0;
		else
			nDispMines = nInitMines - nSqMarkHard;
		if (bDirty || prevMineCount != nDispMines)
			DisplayLedNum(ledMines, nDispMines);
		prevMineCount = nDispMines;
	}
	--busy;
}

void CChildView::DisplayTime(void) 
{
	static busy = -1;
	if (!++busy)
	{
#if 0
		long	timeCurrent;
		if (bGameStarted && !bGameOver)
		{
			time(&timeCurrent);
			timeElapse = timeCurrent - timeStart;
		}
#endif
		if (timeElapse > 999)
			timeElapse = 999;

		DisplayLedNum(ledTimer, timeElapse);
	}
	--busy;
}

void CChildView::DisplayStatus(bool bDirty) 
{
	if (!bDirty)
		return;

	static busy = -1;
	if (!++busy)
	{
		if (hDisp!=NULL)
		{
			if(bGameOver)
			{
				if(bWin)
					DrawButton(ledSmile, (UINT)IDI_IcoFaceCool);
				else
					DrawButton(ledSmile, (UINT)IDI_IcoFaceDead);
			}
			else
			{
				if (nSqPress)
					DrawButton(ledSmile, (UINT)IDI_IcoFaceOooo);
				else
					DrawButton(ledSmile, (UINT)IDI_IcoFaceSmile);
			}
		}
		if(bGameOver)
		{
			if(bWin)
				SoundWin();
			else
				SoundLose();
		}

	}
	--busy;
}

void CChildView::UpdateBestTime(void) 
{
	static busy = -1;
	if ( m_bTimeRecorded || ! bGameOver || ! bWin )
		return;

	if (!++busy)
	{
		UINT*		pBestTime = NULL;
		CString*	pBestName = NULL;
		CString		BestLevel;
		m_bTimeRecorded = true;

		switch(m_GameLevel)
		{
		case	ID_GAME_BEGINNER:
				pBestTime = & m_TimeBeginner;
				pBestName = & m_NameBeginner;
				BestLevel = "Beginner";
			break;
		case	ID_GAME_INTERMEDIATE:
				pBestTime = & m_TimeIntermediate;
				pBestName = & m_NameIntermediate;
				BestLevel = "Intermediate";
			break;
		case	ID_GAME_EXPERT:
				pBestTime = & m_TimeExpert;
				pBestName = & m_NameExpert;
				BestLevel = "Expert";
			break;
		}
		if (pBestTime != NULL && (UINT)timeElapse < *pBestTime)
		{
			FastestTime FastestTimeDlg;
			FastestTimeDlg.m_Message1 = "You have the fastest time";
			FastestTimeDlg.m_Message2 = "for " + BestLevel + " level.";
			FastestTimeDlg.m_Message3 = "Please enter your name.";

			FastestTimeDlg.m_Name = *pBestName;
			int rc = FastestTimeDlg.DoModal();

			if (rc == 1)
			{
				*pBestName = FastestTimeDlg.m_Name;
				*pBestTime = timeElapse;
				SetProfileParams();
			}
		}
	}
	--busy;
}

void CChildView::DisplayBoard(bool bRedrawSquares)
{
	static busy = -1;

	if (!++busy)
	{
		if (hDisp != NULL)
		{
			if (bRedrawSquares)
				MarkAllSquaresDirty();
 			CountBoardInfo();
			if (bGameOver)
				ShowMines(bWin);
			Draw_squares();
			DisplayMineCount(bRedrawSquares);
			DisplayStatus(nSqDirty!=0);
			if (bRedrawSquares)
				DisplayTime();
			UpdateBestTime();
		}
	}
	--busy;
}


/*----------------------------------------------------------------------*/


BOOL CChildView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pCFrameWnd = (CMainFrame *)pParentWnd;
	m_pCWinApp = m_pCFrameWnd->m_pCWinApp;
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

BOOL CChildView::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd ::DestroyWindow();
}

void CChildView::SetBoardWindow()
{
	int nWidth;
	int nHeight;
	int nBorderWidth;
	int nTopBorderHeight;
	RECT Rect;
	POINT Point;

	m_pCFrameWnd->GetWindowRect( &Rect );

	Point.x = 0;
	Point.y = 0;
	ClientToScreen( &Point );
	nTopBorderHeight = Point.y - Rect.top;
	nBorderWidth = Point.x - Rect.left
		;
	nWidth = OffsetToLeftSq*2+nSqWide*SqWidth+2*nBorderWidth;
	nHeight = OffsetToTopSq+OffsetToLeftSq+nSqHigh*SqHeight + nTopBorderHeight + nBorderWidth;

	m_pCFrameWnd->MoveWindow( m_WindowLeft, m_WindowTop, nWidth, nHeight );

	displayWindowWidth  = nWidth  - nBorderWidth*2;
	displayWindowHeight = nHeight - nBorderWidth;

	playField.left	= OffsetToLeftSq;
	playField.right	= playField.left + nSqWide*SqWidth;
	playField.top	= OffsetToTopSq;
	playField.bottom= playField.top + nSqHigh*SqHeight;


	ledMines.left	= OffsetToLeftSq + ledOffset;
	ledMines.top	= iConTop;
	ledMines.right	= ledMines.left + (ledWidth*3);
	ledMines.bottom	= ledMines.top  + (ledHeight);
	
	ledTimer.left	= playField.right - ledWidth*3 - ledOffset;
	ledTimer.top	= iConTop;
	ledTimer.right	= ledTimer.left + (ledWidth*3);
	ledTimer.bottom	= ledMines.bottom;


	ledSmile.left	= OffsetToLeftSq + (nSqWide*SqWidth)/2 - (faceWidth/2);
	ledSmile.top	= iConTop-1;
	ledSmile.right	= ledSmile.left + faceWidth;
	ledSmile.bottom	= ledSmile.top  + faceHeight;

}

void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd ::OnChar(nChar, nRepCnt, nFlags);
}

#if 0
#define MOUSEEVENTF_MOVE        0x0001 /* mouse move */
#define MOUSEEVENTF_LEFTDOWN    0x0002 /* left button down */
#define MOUSEEVENTF_LEFTUP      0x0004 /* left button up */
#define MOUSEEVENTF_RIGHTDOWN   0x0008 /* right button down */
#define MOUSEEVENTF_RIGHTUP     0x0010 /* right button up */
#define MOUSEEVENTF_MIDDLEDOWN  0x0020 /* middle button down */
#define MOUSEEVENTF_MIDDLEUP    0x0040 /* middle button up */
#define MOUSEEVENTF_WHEEL       0x0800 /* wheel button rolled */
#define MOUSEEVENTF_ABSOLUTE    0x8000 /* absolute move */

UINT nFlags::::
MK_CONTROL   Set if the CTRL key is down.
MK_LBUTTON   Set if the left mouse button is down.
MK_MBUTTON   Set if the middle mouse button is down.
MK_RBUTTON   Set if the right mouse button is down.
MK_SHIFT   Set if the SHIFT key is down. 

#endif

void CChildView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	mouse_x = point.x;
	mouse_y = point.y;

	mouse_status &= ~MOUSEEVENTF_LEFTUP;
	mouse_status |= MOUSEEVENTF_LEFTDOWN;

	if (nFlags & MK_RBUTTON)
	{
		mouse_status &= ~MOUSEEVENTF_RIGHTUP;
		mouse_status |= MOUSEEVENTF_RIGHTDOWN;
	}

	Do_all();
	mouse_reset();
	
	CWnd ::OnLButtonDown(nFlags, point);
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	mouse_x = point.x;
	mouse_y = point.y;

	mouse_status &= ~MOUSEEVENTF_LEFTDOWN;
	mouse_status |= MOUSEEVENTF_LEFTUP;

	if(mouse_status & MOUSEEVENTF_RIGHTDOWN)
	{
		mouse_status &= ~MOUSEEVENTF_RIGHTDOWN;
		mouse_status |= MOUSEEVENTF_RIGHTUP;
	}

	Do_all();
	mouse_reset();

	CWnd ::OnLButtonUp(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	mouse_x = point.x;
	mouse_y = point.y;

	mouse_status &= ~MOUSEEVENTF_RIGHTUP;
	mouse_status |= MOUSEEVENTF_RIGHTDOWN;

	if (nFlags & MK_LBUTTON)
	{
		mouse_status &= ~MOUSEEVENTF_LEFTUP;
		mouse_status |= MOUSEEVENTF_LEFTDOWN;
	}

	Do_all();
	mouse_reset();

	CWnd ::OnRButtonDown(nFlags, point);
}


void CChildView::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	OnRButtonDown(nFlags, point);
	CWnd ::OnRButtonDblClk(nFlags, point);
}

void CChildView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	mouse_x = point.x;
	mouse_y = point.y;

	mouse_status &= ~MOUSEEVENTF_RIGHTDOWN;
	mouse_status |= MOUSEEVENTF_RIGHTUP;

	if(mouse_status & MOUSEEVENTF_LEFTDOWN)
	{
		mouse_status &= ~MOUSEEVENTF_LEFTDOWN;
		mouse_status |= MOUSEEVENTF_LEFTUP;
	}

	Do_all();
	mouse_reset();

	CWnd ::OnRButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point) 
{
//	if ( mouse_x != point.x && 	mouse_y != point.y)
//		mouse_status &= ~MOUSEEVENTF_RIGHTDOWN;

	mouse_x = point.x;
	mouse_y = point.y;

	Do_all();
	mouse_reset();

	CWnd ::OnMouseMove(nFlags, point);
}

void CChildView::SoundTimer(void)
{
	static int busy = -1;

	if (!++busy)
	{
		if (this->m_GameSound)
			PlaySound1(IDR_SOUND_Tock);
	}
	--busy;
}

void CChildView::SoundLose(void)
{
	static int busy = -1;

	if (!++busy)
	{
		if (this->m_GameSound)
			PlaySound1(IDR_SOUND_Lose);
	}
	--busy;
}

void CChildView::SoundWin(void)
{
	static int busy = -1;

	if (!++busy)
	{
		if (this->m_GameSound)
			PlaySound1(IDR_SOUND_Win);
	}
	--busy;
}

void CChildView::TurnTimerOnOff(bool bOn)
{
	static int busy = -1;
	static bTimerSet = false;

	if (!++busy)
	{
		if (bOn)
		{
			if (!bTimerSet)
			{
				SetTimer(1, 1000, NULL);
				bTimerSet = true;
			}
		}
		else
		{
			if (bTimerSet)
			{
				KillTimer(1);
				bTimerSet = false;
			}
		}
	}
	--busy;
}


void CChildView::OnTimer(UINT nIDEvent) 
{
	static busy = -1;
	if (!++busy)
	{
		if(bGameOver || !bGameStarted)
		{
			TurnTimerOnOff(false);
			DisplayTime();
		}
		else
		{
			TurnTimerOnOff(true);
			timeElapse++;
			DisplayTime();
			SoundTimer();
		}
	}
	--busy;
	CWnd ::OnTimer(nIDEvent);
}


void CChildView::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd ::OnSetFocus(pOldWnd);
	static bFirstTime = true;
	
	if (bFirstTime)
	{
		bFirstTime = false;
		ResetGame();
	}
}

void CChildView::OnKillFocus(CWnd* pNewWnd) 
{
	CWnd ::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
}

void CChildView::OnGameNew() 
{
	ResetGame();
	PostMessage(WM_PAINT);
}

void CChildView::GetProfileParams(void) 
{
	if(m_pCWinApp == NULL)
		return;

	m_WindowLeft = m_pCWinApp->GetProfileInt( "Window", "Left", 0 );
	m_WindowTop  = m_pCWinApp->GetProfileInt( "Window", "Top",  0 );

	m_GameLevel	= m_pCWinApp->GetProfileInt( "Game", "Level", ID_GAME_BEGINNER );
	m_GameMarks	= m_pCWinApp->GetProfileInt( "Game", "Marks", 3);
	m_GameColor	= m_pCWinApp->GetProfileInt( "Game", "Color", 1);
	m_GameSound	= m_pCWinApp->GetProfileInt( "Game", "Sound", 0);

	m_TimeBeginner		= m_pCWinApp->GetProfileInt( "Best", "TimeBeginner", 999);
	m_TimeIntermediate	= m_pCWinApp->GetProfileInt( "Best", "TimeIntermediate", 999 );
	m_TimeExpert		= m_pCWinApp->GetProfileInt( "Best", "TimeExpert", 999 );

	m_NameBeginner		= m_pCWinApp->GetProfileString( "Best", "NameBeginner",		"Anonymous" );
	m_NameIntermediate	= m_pCWinApp->GetProfileString( "Best", "NameIntermediate",	"Anonymous" );
	m_NameExpert		= m_pCWinApp->GetProfileString( "Best", "NameExpert",		"Anonymous" );

	m_CustomX	= m_pCWinApp->GetProfileInt( "Custom", "Width",  20 );
	m_CustomY	= m_pCWinApp->GetProfileInt( "Custom", "Height", 20 );
	m_CustomM	= m_pCWinApp->GetProfileInt( "Custom", "Mines",  20 );
}

void CChildView::SetProfileParams(void) 
{
	m_pCWinApp->WriteProfileInt( "Window", "Left", m_WindowLeft );
	m_pCWinApp->WriteProfileInt( "Window", "Top",  m_WindowTop );

	m_pCWinApp->WriteProfileInt( "Game", "Level", m_GameLevel );
	m_pCWinApp->WriteProfileInt( "Game", "Marks", m_GameMarks );
	m_pCWinApp->WriteProfileInt( "Game", "Color", m_GameColor );
	m_pCWinApp->WriteProfileInt( "Game", "Sound", m_GameSound );

	m_pCWinApp->WriteProfileInt( "Best", "TimeBeginner",		m_TimeBeginner);
	m_pCWinApp->WriteProfileInt( "Best", "TimeIntermediate",	m_TimeIntermediate );
	m_pCWinApp->WriteProfileInt( "Best", "TimeExpert",			m_TimeExpert );

	m_pCWinApp->WriteProfileString( "Best", "NameBeginner",		m_NameBeginner);
	m_pCWinApp->WriteProfileString( "Best", "NameIntermediate",	m_NameIntermediate );
	m_pCWinApp->WriteProfileString( "Best", "NameExpert",		m_NameExpert );

	m_pCWinApp->WriteProfileInt( "Custom", "Width",  m_CustomX );
	m_pCWinApp->WriteProfileInt( "Custom", "Height", m_CustomY );
	m_pCWinApp->WriteProfileInt( "Custom", "Mines",  m_CustomM );
}

void CChildView::OnGameBeginner() 
{
	m_GameLevel = ID_GAME_BEGINNER;
	SetProfileParams();
	PostMessage(WM_COMMAND, ID_GAME_NEW,0);
}
void CChildView::OnGameIntermediate() 
{
	m_GameLevel = ID_GAME_INTERMEDIATE;
	SetProfileParams();
	PostMessage(WM_COMMAND, ID_GAME_NEW,0);
}
void CChildView::OnGameExpert() 
{
	m_GameLevel = ID_GAME_EXPERT;
	SetProfileParams();
	PostMessage(WM_COMMAND, ID_GAME_NEW,0);
}
void CChildView::OnGameCustom() 
{
	m_GameLevel = ID_GAME_CUSTOM;

	CustomMines customMinesDlg;

	customMinesDlg.m_Width	= m_CustomX;
	customMinesDlg.m_Height	= m_CustomY;
	customMinesDlg.m_Mines	= m_CustomM;

	int rc = customMinesDlg.DoModal();

	if (rc == 1)
	{
		m_CustomX = customMinesDlg.m_Width;
		m_CustomY = customMinesDlg.m_Height;
		m_CustomM = customMinesDlg.m_Mines;

		SetProfileParams();
		PostMessage(WM_COMMAND, ID_GAME_NEW,0);
	}
}


void CChildView::OnGameMarks() 
{
	if (++m_GameMarks > 3)
		m_GameMarks = 2;
	SetProfileParams();
}
void CChildView::OnGameColor() 
{
	m_GameColor = !m_GameColor;
	SetProfileParams();
}
void CChildView::OnGameSound() 
{
	m_GameSound = !m_GameSound;
	SetProfileParams();
}

void CChildView::OnGameBestTimes() 
{
	BestTimes BestTimesDlg;

	BestTimesDlg.m_NameBeginner		= m_NameBeginner;
	BestTimesDlg.m_NameIntermediate	= m_NameIntermediate;
	BestTimesDlg.m_NameExpert		= m_NameExpert;

	BestTimesDlg.m_TimeBeginner		= m_TimeBeginner;
	BestTimesDlg.m_TimeIntermediate	= m_TimeIntermediate;
	BestTimesDlg.m_TimeExpert		= m_TimeExpert;

	int rc = BestTimesDlg.DoModal();

	m_NameBeginner		= BestTimesDlg.m_NameBeginner;
	m_NameIntermediate	= BestTimesDlg.m_NameIntermediate;
	m_NameExpert		= BestTimesDlg.m_NameExpert;

	m_TimeBeginner		= BestTimesDlg.m_TimeBeginner;
	m_TimeIntermediate	= BestTimesDlg.m_TimeIntermediate;
	m_TimeExpert		= BestTimesDlg.m_TimeExpert;

	SetProfileParams();
}

void CChildView::OnUpdateGameBeginner(CCmdUI* pCmdUI) 
{
	bool	bChecked = (m_GameLevel == ID_GAME_BEGINNER);
	pCmdUI->SetCheck(bChecked);
}


void CChildView::OnUpdateGameIntermediate(CCmdUI* pCmdUI) 
{
	bool	bChecked = (m_GameLevel == ID_GAME_INTERMEDIATE);
	pCmdUI->SetCheck(bChecked);
}

void CChildView::OnUpdateGameExpert(CCmdUI* pCmdUI) 
{
	bool	bChecked = (m_GameLevel == ID_GAME_EXPERT);
	pCmdUI->SetCheck(bChecked);
}

void CChildView::OnUpdateGameMarks(CCmdUI* pCmdUI) 
{
	bool	bChecked = (m_GameMarks > 2);
	pCmdUI->SetCheck(bChecked);
}

void CChildView::OnUpdateGameColor(CCmdUI* pCmdUI) 
{
	bool	bChecked = (m_GameColor != 0);

	pCmdUI->SetCheck(bChecked);
//	pCmdUI->Enable(false);
}

void CChildView::OnUpdateGameSound(CCmdUI* pCmdUI) 
{
	bool	bChecked = (m_GameSound != 0);
	pCmdUI->SetCheck(bChecked);
}

