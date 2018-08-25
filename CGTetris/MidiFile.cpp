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


// MidiFile.cpp: implementation of the CMidiFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MidiFile.h"


#include <io.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMidiFile::CMidiFile(): m_hFile(0), m_hMem(0), m_pData(0)
  { }


CMidiFile::~CMidiFile()
  { FreeMusicFile(); }


BOOL CMidiFile::Create(const CString & strFile, CWnd * pWnd) 
  {
	// free a previously mapped music file
	FreeMusicFile();

	if( ::_taccess(strFile, 0) == 0 ) 
     {
		// load the file
		m_hFile = ::CreateFile( strFile, GENERIC_READ, FILE_SHARE_READ,
				                  0, OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS, 0 );
		if( m_hFile != INVALID_HANDLE_VALUE ) 
        {
			DWORD dwSize = ::GetFileSize( m_hFile, 0 );
			m_hMem = ::CreateFileMapping( m_hFile, 0, PAGE_READONLY, 0, dwSize, 0 );
			if( m_hMem != 0 ) 
           {
				m_pData = ::MapViewOfFile( m_hMem, FILE_MAP_READ, 0, 0, 0 );
				if( m_pData ) 
              {
					// OK - now we can create the MIDI object
					BOOL bRet = CMIDI::Create(m_pData, dwSize, pWnd);
					if( bRet )
					  m_strMusicFile = strFile;
					return bRet;
              }
           }
        }
     }
   return FALSE;
  }


void CMidiFile::FreeMusicFile() 
  {
	if( m_pData )
     ::UnmapViewOfFile( m_pData );
	m_pData = 0;
	if( m_hMem )
     ::CloseHandle( m_hMem );
	m_hMem = 0;
	if( m_hFile )
     ::CloseHandle( m_hFile );
	m_hFile = 0;
}
