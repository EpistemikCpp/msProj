; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=Square
LastTemplate=CButton
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "minesweeper.h"
LastPage=0

ClassCount=8
Class1=CAboutDlg
Class2=BestTimes
Class3=CChildView
Class4=CustomMines
Class5=FastestTime
Class6=CMainFrame
Class7=CMineSweeperApp

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDD_DIALOG_BestScores
Resource3=IDD_DIALOG_Custom_Mines
Resource4=IDR_MAINFRAME
Class8=Square
Resource5=IDD_DIALOG_FastestTime

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=AboutDlg.h
ImplementationFile=AboutDlg.cpp

[CLS:BestTimes]
Type=0
BaseClass=CDialog
HeaderFile=BestTimes.h
ImplementationFile=BestTimes.cpp
LastObject=ID_ResetScores
Filter=D
VirtualFilter=dWC

[CLS:CChildView]
Type=0
BaseClass=CWnd 
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=W
VirtualFilter=WC
LastObject=CChildView

[CLS:CustomMines]
Type=0
BaseClass=CDialog
HeaderFile=CustomMines.h
ImplementationFile=CustomMines.cpp

[CLS:FastestTime]
Type=0
BaseClass=CDialog
HeaderFile=FastestTime.h
ImplementationFile=FastestTime.cpp
LastObject=FastestTime
Filter=D
VirtualFilter=dWC

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CMineSweeperApp]
Type=0
BaseClass=CWinApp
HeaderFile=MineSweeper.h
ImplementationFile=MineSweeper.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_BestScores]
Type=1
Class=BestTimes
ControlCount=14
Control1=IDOK,button,1342242817
Control2=ID_ResetScores,button,1342242816
Control3=IDC_STATIC,static,1342177280
Control4=IDC_EDIT_TimeBeginner,edit,1342179328
Control5=IDC_STATIC,static,1342177280
Control6=IDC_EDIT_TimeIntermediate,edit,1342244864
Control7=IDC_STATIC,static,1342177280
Control8=IDC_EDIT_TimeExpert,edit,1342244864
Control9=IDC_EDIT_NameBeginner,edit,1342244864
Control10=IDC_EDIT_NameIntermediate,edit,1342244864
Control11=IDC_EDIT_NameExpert,edit,1342244864
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_Custom_Mines]
Type=1
Class=CustomMines
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342177280
Control4=IDC_EDIT_Height,edit,1350631552
Control5=IDC_STATIC,static,1342177280
Control6=IDC_EDIT_Width,edit,1350631552
Control7=IDC_STATIC,static,1342177280
Control8=IDC_EDIT_Mines,edit,1350631552

[DLG:IDD_DIALOG_FastestTime]
Type=1
Class=FastestTime
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_EDIT_Name,edit,1350631552
Control3=IDC_EDIT_Message1,edit,1342179328
Control4=IDC_EDIT_Message2,edit,1342179328
Control5=IDC_EDIT_Message3,edit,1342179328

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_GAME_NEW
Command2=ID_GAME_BEGINNER
Command3=ID_GAME_INTERMEDIATE
Command4=ID_GAME_EXPERT
Command5=ID_GAME_CUSTOM
Command6=ID_GAME_MARKS
Command7=ID_GAME_COLOR
Command8=ID_GAME_SOUND
Command9=ID_GAME_BEST_TIMES
Command10=ID_APP_EXIT
Command11=ID_HELP_CONTENT
Command12=ID_HELP_INDEX
Command13=ID_HELP_SEARCH
Command14=ID_HELP_USING
Command15=ID_APP_ABOUT
CommandCount=15

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_DEFAULT_HELP
Command2=ID_CONTEXT_HELP
Command3=ID_GAME_NEW
CommandCount=3

[CLS:Square]
Type=0
HeaderFile=Square.h
ImplementationFile=Square.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC
LastObject=Square

