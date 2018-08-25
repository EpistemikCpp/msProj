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


// MusicPlayer.h: interface for the CMusicPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUSICPLAYER_H__87550DB2_92B8_11D2_A7EA_000000000000__INCLUDED_)
#define AFX_MUSICPLAYER_H__87550DB2_92B8_11D2_A7EA_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "MidiFile.h"
#include <vector>

class CMusicPlayer : public CWnd {
	DECLARE_DYNAMIC(CMusicPlayer);

	struct node {
		UINT uResource;
		CString strFile;

		node() : uResource(0)
		{
		}
		node(const node & ln)
			: uResource(ln.uResource)
			, strFile(ln.strFile)
		{
		}
		node(UINT uRes)
			: uResource(uRes)
		{
		}
		node(const CString & str)
			: uResource(0)
			, strFile(str)
		{
		}
	};

	typedef std::vector<node>	container_t;

	public:
		CMusicPlayer();
		virtual ~CMusicPlayer();

	public:
		BOOL			Create();
		void			EnableMusic(bool bEnable = true);
		void			StartMusic();
		void			StopMusic();
		void			PauseMusic();
		void			ResumeMusic();
		CMusicPlayer &	Set(UINT uResource);
		CMusicPlayer &	Set(const CString & file);
		CMusicPlayer &	SetVolume(DWORD dwPercent);
		DWORD			GetVolume() const { return m_dwVolume; }
		void			SetSequence(bool bSet = true);

	private:
		CMIDI *		m_pMusic;
		bool			m_bEnabled;
		DWORD			m_dwVolume;
		bool			m_bSequence;
		container_t	            m_All;
		container_t::size_type	m_At;

	protected:
	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CGameBoard)
		//}}AFX_VIRTUAL

	protected:
		// Generated message map functions
		//{{AFX_MSG(CGameBoard)
		//}}AFX_MSG

		afx_msg LONG	OnVolumeChanged(WPARAM, LPARAM);
		afx_msg LONG	OnMusicPlayedOff(WPARAM, LPARAM);

		DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_MUSICPLAYER_H__87550DB2_92B8_11D2_A7EA_000000000000__INCLUDED_)
