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

// MusicPlayer.cpp: implementation of the CMusicPlayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MusicPlayer.h"
#include "resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CMusicPlayer, CWnd);


CMusicPlayer::CMusicPlayer()
	: m_pMusic(0)
	, m_bEnabled(true)
	, m_dwVolume(100)		// 100% by default
	, m_bSequence(false)
	, m_At(0)
{
}


CMusicPlayer::~CMusicPlayer()
{
	delete m_pMusic;
}


BOOL CMusicPlayer::Create() {
	BOOL bRet = CWnd::CreateEx(
					0,
					AfxRegisterWndClass(CS_CLASSDC), 
					_T("MusicNotifier"), WS_POPUP, 0, 0, 
					0, 0, 0, 0
				);
	if(bRet) {
		ShowWindow(SW_HIDE);
		UpdateWindow();
	}
	return bRet;
}


void CMusicPlayer::EnableMusic(bool bEnable) {
	if(!bEnable) {
		if(m_pMusic)
			m_pMusic->Stop();
	} else if(!m_bEnabled)
		if(m_pMusic)
			m_pMusic->Play(!m_bSequence);
	m_bEnabled = bEnable;
}


void CMusicPlayer::StartMusic() {
	if(m_bEnabled && m_pMusic)
		m_pMusic->Play(!m_bSequence);
}


void CMusicPlayer::StopMusic() {
	if(m_pMusic)
		m_pMusic->Stop();
}


void CMusicPlayer::PauseMusic() {
	if(m_pMusic)
		m_pMusic->Pause();
}


void CMusicPlayer::ResumeMusic() {
	if(m_pMusic)
		m_pMusic->Continue();
}


CMusicPlayer & CMusicPlayer::SetVolume(DWORD dwPercent) {
	ASSERT(dwPercent <= 100);
	m_dwVolume = dwPercent;
	if(m_pMusic)
		m_pMusic->SetVolume(m_dwVolume);

	return * this;
}


CMusicPlayer & CMusicPlayer::Set(UINT uResource) {
	if(m_pMusic)
		delete m_pMusic;

	m_pMusic = new CMIDI();

	if( m_pMusic ) {
		m_pMusic->Create(uResource, this);
		m_pMusic->SetVolume(m_dwVolume);
	}

	return * this;
}


CMusicPlayer & CMusicPlayer::Set(const CString & strFile) {
	if(m_pMusic)
		delete m_pMusic;

	CMidiFile * pMusic = new CMidiFile();

	if( pMusic ) {
		pMusic->Create(strFile, this);
		pMusic->SetVolume(m_dwVolume);
	}

	m_pMusic = pMusic;

	return * this;
}


void CMusicPlayer::SetSequence(bool bSet) {
	m_bSequence = bSet;
	m_At = 0;

	if(bSet) {
		if(m_All.empty()) {
			// Add the builtin music files
			m_All.push_back(node(IDM_Fairy));
			m_All.push_back(node(IDM_Kalinka));
			m_All.push_back(node(IDM_WindOfChange));

			// Add external music files
			TCHAR chName[_MAX_PATH];
			::GetModuleFileName(0, chName, _MAX_PATH);
			TCHAR chDrive[_MAX_DRIVE];
			TCHAR chPath[_MAX_PATH];
			TCHAR chFullPath[_MAX_PATH];
			_tsplitpath(chName, chDrive, chPath, 0, 0);
			_tcscpy(chFullPath, chDrive);
			_tcscat(chFullPath, chPath);
			_tcscat(chFullPath, TEXT("*.mid"));

			CFileFind finder;
			BOOL bFound = finder.FindFile(chFullPath);
			while(bFound) {
				bFound = finder.FindNextFile();
				m_All.push_back(node(finder.GetFilePath()));
				TRACE1("File added: <%s>\n", LPCTSTR(finder.GetFilePath()));
			}
		}

		container_t::reference node = m_All[0];

		if(node.uResource)
			Set(node.uResource);
		else
			Set(node.strFile);

		//StartMusic();

		++m_At;
	} else
		StopMusic();
}


BEGIN_MESSAGE_MAP(CMusicPlayer, CWnd)
	//{{AFX_MSG_MAP(CMusicPlayer)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MIDI_VOLUMECHANGED, OnVolumeChanged)
	ON_MESSAGE(WM_MIDI_OUTDONE, OnMusicPlayedOff)
END_MESSAGE_MAP()


LONG CMusicPlayer::OnVolumeChanged(WPARAM wParam, LPARAM lParam) {
	ASSERT(m_pMusic != 0);
	if(m_pMusic == (CMIDI *)wParam)
		// Volume of music changed during playback.
		// Reset the volume to what we want it to be.
		m_pMusic->SetChannelVolume(LOWORD(lParam), m_dwVolume);
	return 0;
}


LONG CMusicPlayer::OnMusicPlayedOff(WPARAM wParam, LPARAM) {
	ASSERT(m_pMusic != 0);
	ASSERT(m_pMusic == (CMIDI *)wParam);

	// if we're playing a sequence, switch to the next midi object
	if(m_bSequence) {
		if(m_At >= m_All.size())
			// loop to the first midi object
			m_At = 0;

		container_t::reference node = m_All[m_At];

		if(node.uResource)
			Set(node.uResource);
		else
			Set(node.strFile);

		StartMusic();

		++m_At;
	}

	return 0;
}
