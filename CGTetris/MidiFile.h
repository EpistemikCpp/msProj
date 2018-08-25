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


// MidiFile.h: interface for the CMidiFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSOUNDFILE_H__87550DB0_92B8_11D2_A7EA_000000000000__INCLUDED_)
#define AFX_DSOUNDFILE_H__87550DB0_92B8_11D2_A7EA_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MIDI.h"

class CMidiFile : public CMIDI
  {
	public:
		CMidiFile();
		virtual ~CMidiFile();

	public:
		BOOL	Create(const CString & filename, CWnd *pWnd = 0);

	protected:
		void	FreeMusicFile();

	protected:
		CString	m_strMusicFile;	// music comes from this MIDI file
		HANDLE	m_hFile;		// handle to external music file
		HANDLE	m_hMem;		// handle to memory mapped file
		LPVOID	m_pData;		// beginning of music data
  };

#endif // !defined(AFX_DSOUNDFILE_H__87550DB0_92B8_11D2_A7EA_000000000000__INCLUDED_)
