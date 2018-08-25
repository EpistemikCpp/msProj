// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__0C440B51_37E5_40F0_9555_2EA69550070F__INCLUDED_)
#define AFX_CHILDVIEW_H__0C440B51_37E5_40F0_9555_2EA69550070F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChildView window

typedef enum Color;

class CMineSweeperApp;
class CMainFrame;

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:
	CMainFrame*			m_pCFrameWnd;
	CMineSweeperApp*	m_pCWinApp;

	UINT				m_WindowTop;
	UINT				m_WindowLeft;

	UINT				m_GameLevel;

	UINT				m_CustomX;
	UINT				m_CustomY;
	UINT				m_CustomM;

	UINT				m_GameMarks;
	UINT				m_GameColor;
	UINT				m_GameSound;

	UINT				m_TimeBeginner;
	UINT				m_TimeIntermediate;
	UINT				m_TimeExpert;

	CString				m_NameBeginner;
	CString				m_NameIntermediate;
	CString				m_NameExpert;

	bool				m_bTimeRecorded;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL DestroyWindow();
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DisplayLedNum(RECT& rect, int num);
	virtual ~CChildView();

	HDC		My_hDisp (void);

	void	GetProfileParams(void);
	void	SetProfileParams(void);
	void	TurnTimerOnOff(bool bOn);
	void	SoundTimer(void);
	void	SoundLose(void);
	void	SoundWin(void);
	void	SetBoardWindow(void);
	void	DisplayBoard(bool bRedrawSquares = false);
	void	StartGame(void);
	void	MarkAllSquaresDirty(void);
	void	Display_square (int x, int y);
	void	ResetGame(void);
	int		SetBoardDimAndNumMines(void);
	void	CountBoardInfo(void);
	void	ClearBoard(void);
	void	SetupMines(int nMines);
	HICON	LoadIcon( LPCTSTR lpszResourceName, bool bMonochrome, int cx = 0, int cy = 0 ) const;
	HICON	LoadIcon( UINT nIDResource, bool bMonochrome, int cx = 0, int cy = 0) const;
	void	DrawButton(RECT& b, UINT nIdIcon, bool bSqPress  = false, int upWidth = 2, int pressWidth = -1);
	void	DrawShade (RECT& b, int width = 2, bool bOutSideIn = true);
	void	Draw_squares(void);
	void	UnPressAllSquaresExcept(int x, int y);
	void	Do_all(void);
	void	ShowMines(bool bWin);
	bool	Open_square(int x, int y, bool bOpenMine);
	void	Open_near_squares(int x, int y, bool bPressOnly = false);
	void	DisplayMineCount(bool bDirty);
	void	DisplayTime(void);
	void	DisplayStatus(bool bDirty);
	void	UpdateBestTime(void);
	void	MouseSetRange(void);
	void	mouse_reset(void);
	void	mouse_horizontal_range(int xmin, int xmax);
	void	mouse_vertical_range(int ymin, int ymax);
	void	setcolor(Color color);
	void	setfillstyle(int style, Color color);
	void	bar(int xl, int yt, int xr, int yb);
	void	line(int xl,int yt, int xr, int yb);
	void	fillellipse(int xl, int yl, int Ex, int Ey);
	void	settextjustify(int p1, int p2);
	void	outtextxy(int x, int y, char* txt);
	void	randomize(void);
	int		random(int maxRet);

	// Generated message map functions
protected:
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnGameNew();
	afx_msg void OnGameBeginner();
	afx_msg void OnGameIntermediate();
	afx_msg void OnGameExpert();
	afx_msg void OnGameCustom();
	afx_msg void OnGameMarks();
	afx_msg void OnGameColor();
	afx_msg void OnGameSound();
	afx_msg void OnGameBestTimes();
	afx_msg void OnUpdateGameBeginner(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGameIntermediate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGameExpert(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGameMarks(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGameColor(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGameSound(CCmdUI* pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__0C440B51_37E5_40F0_9555_2EA69550070F__INCLUDED_)
